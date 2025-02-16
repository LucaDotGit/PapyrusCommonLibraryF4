#include "Internal/Runners/TranslationRunner.hpp"

#include "Internal/Bethesda/Encoder.hpp"
#include "Internal/Bethesda/Translator.hpp"

namespace Internal::TranslationRunner
{
	using json_t = nlohmann::json;
	using translation_t = std::map<std::string, std::vector<std::pair<RE::BSFixedStringWCS, RE::BSFixedStringWCS>>>;

	static const auto PATH = std::filesystem::path(L"Data\\PCL\\Translations"s);
	static const auto EXTENSION = std::filesystem::path(L".json"s);

	static constexpr auto LANG_SEPARATOR = '_';
	static constexpr auto LANG_DEFAULT = "Default"sv;
	static constexpr auto LANG_OVERRIDE = "Override"sv;

	static constexpr auto ALLOW_EXCEPTIONS = true;
	static constexpr auto IGNORE_COMMENTS = true;
	static const auto JSON_CALLBACK = json_t::parser_callback_t();

	static auto DefaultTranslations = translation_t();
	static auto StandardTranslations = translation_t();
	static auto OverrideTranslations = translation_t();

	static void Dispose()
	{
		logger::debug("Translation Runner: Dispose"sv);

		DefaultTranslations.clear();
		StandardTranslations.clear();
		OverrideTranslations.clear();
	}

	void Setup()
	{
		logger::debug("Translation Runner: Setup"sv);

		constexpr auto DIR_OPTIONS = std::filesystem::directory_options::skip_permission_denied;
		const auto langCode = Translator::GetLanguageCode();

		auto entryError = std::error_code();
		for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(PATH, DIR_OPTIONS, entryError)) {
			const auto& filePath = dirEntry.path();
			if (filePath.extension() != EXTENSION) {
				continue;
			}

			auto isFileError = std::error_code();
			if (!dirEntry.is_regular_file(isFileError)) {
				continue;
			}

			const auto fileName = filePath.stem().string();
			const auto langIt = fileName.find_last_of(LANG_SEPARATOR);

			if (langIt == std::string::npos) {
				logger::warn("Translation Runner: No language separator (\"{}\") found in file \"{}\""sv,
					LANG_SEPARATOR, filePath.string());
				continue;
			}

			const auto fileLang = std::string_view{ fileName.data() + langIt + 1, fileName.size() - langIt - 1 };
			const auto isDefault = fileLang == LANG_DEFAULT;
			const auto isOverride = fileLang == LANG_OVERRIDE;

			if (fileLang != langCode && !isDefault && !isOverride) {
				continue;
			}

			auto json = json_t();

			try {
				auto reader = std::ifstream(filePath);
				reader.exceptions(Internal::Errors::IO_FLAGS);
				json = json_t::parse(reader, JSON_CALLBACK, ALLOW_EXCEPTIONS, IGNORE_COMMENTS);
			}
			catch (const std::exception& a_error) {
				logger::warn("Translation Runner: Error in file \"{}\": {}"sv,
					filePath.string(), a_error.what());
				continue;
			}

			for (const auto& [nodeKey, node] : json.items()) {
				if (!node.is_string()) {
					logger::warn("Translation Runner: Error in file \"{}\": Value is not a string: \"{}\""sv,
						filePath.string(), nodeKey);
					continue;
				}

				if (nodeKey.size() <= sizeof(Translator::KEY_PREFIX) || !nodeKey.starts_with(Translator::KEY_PREFIX)) {
					logger::warn("Translation Runner: Error in file \"{}\": Key is empty or doesn't start with \"{}\": \"{}\""sv,
						filePath.string(), Translator::KEY_PREFIX, nodeKey);
					continue;
				}

				const auto nodeValue = node.get<std::string>();

				const auto u16Key = Encoder::FromUTF8ToUTF16(nodeKey);
				if (!u16Key.has_value()) {
					logger::warn("Translation Runner: Error in file \"{}\": Failed to convert key to UTF-16 LE: \"{}\""sv,
						filePath.string(), nodeKey);
					continue;
				}

				const auto u16Value = Encoder::FromUTF8ToUTF16(nodeValue);
				if (!u16Value.has_value()) {
					logger::warn("Translation Runner: Error in file \"{}\": Failed to convert value to UTF-16 LE: \"{}\""sv,
						filePath.string(), nodeValue);
					continue;
				}

				const auto& key = u16Key.value();
				const auto& value = u16Value.value();

				if (isDefault) {
					DefaultTranslations[fileName].emplace_back(key, value);
				}
				else if (isOverride) {
					OverrideTranslations[fileName].emplace_back(key, value);
				}
				else {
					StandardTranslations[fileName].emplace_back(key, value);
				}

				logger::debug("Translation Runner: Added translation from file \"{}\": \"{}\" -> \"{}\""sv,
					filePath.string(), nodeKey, nodeValue);
			}
		}
	}

	void Run()
	{
		logger::debug("Translation Runner: Run"sv);

		const auto callback = [&](const translation_t& a_translations) {
			for (const auto& [file, pairs] : a_translations) {
				logger::debug("Translation Runner: Running translations from file \"{}\""sv, file);

				for (const auto& [key, value] : pairs) {
					if (!Translator::SetString(key, value)) {
						assert(false);
					}
				}
			}
		};

		callback(DefaultTranslations);
		callback(StandardTranslations);
		callback(OverrideTranslations);

		Dispose();
	}
}
