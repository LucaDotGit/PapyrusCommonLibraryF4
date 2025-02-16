#include "Internal/Runners/FunctionRunner.hpp"

#include "Internal/Bethesda/ScriptUtils.hpp"

namespace Internal::FunctionRunner
{
	static const auto PATH = std::filesystem::path(L"Data\\PCL\\Functions"s);
	static const auto EXTENSION = std::filesystem::path(L".ini"s);

	static const auto EVENTS = std::unordered_map<std::string_view, Event>{
		{ "OnGameStart"sv, Event::OnGameStart },
		{ "OnPostGameStart"sv, Event::OnPostGameStart },
		{ "OnGameLoad"sv, Event::OnGameLoad }
	};
	static auto Functions = std::array<std::map<std::string, std::vector<std::pair<RE::BSFixedString, RE::BSFixedString>>>, Event::Count>();

	using Ini = CSimpleIniA;

	void Setup()
	{
		logger::debug("Function Runner: Setup"sv);

		constexpr auto DIR_OPTIONS = std::filesystem::directory_options::skip_permission_denied;
		const auto vm = RE::GameVM::GetSingleton()->GetVM();

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

			auto file = Ini();
			file.SetUnicode();

			auto rc = file.LoadFile(filePath.c_str());
			if (rc != SI_OK) {
				logger::warn("Function Runner: Failed to load file \"{}\""sv, filePath.string());
				continue;
			}

			auto sections = Ini::TNamesDepend();
			file.GetAllSections(sections);

			const auto fileName = filePath.stem().string();

			for (const auto& section : sections) {
				const char* eventName = file.GetValue(section.pItem, "sEventName", nullptr);
				if (!eventName) {
					logger::warn("Function Runner: Error loading file \"{}\": Missing event name in section \"{}\""sv,
						filePath.string(), section.pItem);
					continue;
				}

				const char* scriptName = file.GetValue(section.pItem, "sScriptName", nullptr);
				if (!scriptName) {
					logger::warn("Function Runner: Error in file \"{}\": Missing script name in section \"{}\""sv,
						filePath.string(), section.pItem);
					continue;
				}

				const char* functionName = file.GetValue(section.pItem, "sFunctionName", nullptr);
				if (!functionName) {
					logger::warn("Function Runner: Error in file \"{}\": Missing function name in section \"{}\""sv,
						filePath.string(), section.pItem);
					continue;
				}

				const auto eventIt = EVENTS.find(eventName);
				if (eventIt == EVENTS.end()) {
					logger::warn("Function Runner: Error in file \"{}\": Invalid event name \"{}\" in section \"{}\""sv,
						filePath.string(), eventName, section.pItem);
					continue;
				}

				auto fixedScriptName = RE::BSFixedString(scriptName);
				auto fixedFunctionName = RE::BSFixedString(functionName);

				auto typeInfo = RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo>();
				if (!vm->GetScriptObjectType(fixedScriptName, typeInfo)) {
					logger::warn("Function Runner: Error in file \"{}\": Failed to load script \"{}\" from section \"{}\""sv,
						filePath.string(), scriptName, section.pItem);
					continue;
				}

				Functions.at(eventIt->second)[fileName].emplace_back(std::move(fixedScriptName), std::move(fixedFunctionName));

				logger::debug("Function Runner: Added script from file \"{}\": \"{}\" -> \"{}\" -> \"{}\""sv,
					filePath.string(), eventName, scriptName, functionName);
			}
		}
	}

	void Run(Event a_event)
	{
		logger::debug("Function Runner: Running {}"sv, std::to_underlying(a_event));

		if (a_event >= Event::Count) {
			logger::warn("Function Runner: Invalid event {}"sv, std::to_underlying(a_event));
			assert(false);
			return;
		}

		for (const auto& [file, pairs] : Functions[a_event]) {
			logger::debug("Function Runner: Running scripts from file \"{}\""sv, file);

			for (const auto& [scriptName, functionName] : pairs) {
				ScriptUtils::DispatchStaticCall(scriptName, functionName);
			}
		}
	}
}
