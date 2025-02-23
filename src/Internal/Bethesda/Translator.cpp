#include "Internal/Bethesda/Translator.hpp"

#include "Internal/Bethesda/Encoder.hpp"
#include "Internal/Bethesda/IniSettings.hpp"

namespace Internal::Translator
{
	static auto Mutex = std::shared_mutex();

	std::string_view GetLanguageCode()
	{
		static const auto LANGUAGE = []() -> std::string {
			const auto lock = std::shared_lock{ IniSettings::GetMutex() };

			const auto* setting = IniSettings::GetSetting("General"sv, "sLanguage"sv);
			if (!setting) {
				assert(false);
				return {};
			}

			if (setting->GetType() != RE::Setting::SETTING_TYPE::kString) {
				assert(false);
				return {};
			}

			return std::string(setting->GetString());
		}();

		return LANGUAGE;
	}

	RE::BSTranslator* GetTranslator()
	{
		static auto* TRANSLATOR = []() -> RE::BSTranslator* {
			auto* scaleformManager = RE::BSScaleformManager::GetSingleton();
			if (!scaleformManager) {
				assert(false);
				return nullptr;
			}

			auto* translator = reinterpret_cast<RE::Scaleform::GFx::Translator*>(
				scaleformManager->loader->GetStateAddRef(RE::Scaleform::GFx::State::StateType::kTranslator));
			if (!translator) {
				assert(false);
				return nullptr;
			}

			auto* scaleformTranslator = RE::fallout_cast<RE::BSScaleformTranslator*>(translator);
			if (!scaleformTranslator) {
				assert(false);
				return nullptr;
			}

			return &scaleformTranslator->translator;
		}();

		return TRANSLATOR;
	}

	bool Contains(std::string_view a_key)
	{
		const auto key = Encoder::FromUTF8ToUTF16(a_key);
		if (!key.has_value()) {
			return false;
		}

		return Contains(key.value());
	}

	bool Contains(std::wstring_view a_key)
	{
		const auto key = RE::BSFixedStringWCS(a_key);
		return Contains(key);
	}

	bool Contains(const RE::BSFixedStringWCS& a_key)
	{
		const auto lock = std::shared_lock{ Mutex };

		const auto* translator = GetTranslator();
		if (!translator) {
			return false;
		}

		return translator->translationMap.contains(a_key);
	}

	std::optional<std::string> GetString(std::string_view a_key)
	{
		const auto key = Encoder::FromUTF8ToUTF16(a_key);
		if (!key.has_value()) {
			return std::nullopt;
		}

		const auto value = GetWString(key.value());
		if (!value.has_value()) {
			return std::nullopt;
		}

		return Encoder::FromUTF16ToUTF8(value.value());
	}

	std::optional<std::wstring> GetWString(std::wstring_view a_key)
	{
		const auto key = RE::BSFixedStringWCS(a_key);
		const auto value = GetBSString(key);

		if (!value.has_value()) {
			return std::nullopt;
		}

		return std::wstring{ value.value().data(), value.value().size() };
	}

	std::optional<RE::BSFixedStringWCS> GetBSString(const RE::BSFixedStringWCS& a_key)
	{
		const auto lock = std::shared_lock{ Mutex };

		const auto* translator = GetTranslator();
		if (!translator) {
			return std::nullopt;
		}

		const auto& translationMap = translator->translationMap;

		const auto keyIt = translationMap.find(a_key);
		if (keyIt == translationMap.end()) {
			return std::nullopt;
		}

		return keyIt->second;
	}

	bool SetString(std::string_view a_key, std::string_view a_value)
	{
		const auto key = Encoder::FromUTF8ToUTF16(a_key);
		if (!key.has_value()) {
			return false;
		}

		const auto value = Encoder::FromUTF8ToUTF16(a_value);
		if (!value.has_value()) {
			return false;
		}

		return SetString(key.value(), value.value());
	}

	bool SetString(std::wstring_view a_key, std::wstring_view a_value)
	{
		const auto key = RE::BSFixedStringWCS(a_key);
		const auto value = RE::BSFixedStringWCS(a_value);

		return SetString(key, value);
	}

	bool SetString(const RE::BSFixedStringWCS& a_key, const RE::BSFixedStringWCS& a_value)
	{
		if (a_key.size() <= sizeof(KEY_PREFIX) || a_key[0] != KEY_PREFIX) {
			return false;
		}

		const auto lock = std::unique_lock{ Mutex };

		auto* translator = GetTranslator();
		if (!translator) {
			return false;
		}

		auto& translationMap = translator->translationMap;
		auto&& [it, hasInserted] = translationMap.emplace(a_key, a_value);

		if (!hasInserted) {
			it->second = a_value;
		}

		return true;
	}

	bool Add(std::string_view a_key, std::string_view a_value)
	{
		const auto key = Encoder::FromUTF8ToUTF16(a_key);
		if (!key.has_value()) {
			return false;
		}

		const auto value = Encoder::FromUTF8ToUTF16(a_value);
		if (!value.has_value()) {
			return false;
		}

		return Add(key.value(), value.value());
	}

	bool Add(std::wstring_view a_key, std::wstring_view a_value)
	{
		const auto key = RE::BSFixedStringWCS(a_key);
		const auto value = RE::BSFixedStringWCS(a_value);

		return Add(key, value);
	}

	bool Add(const RE::BSFixedStringWCS& a_key, const RE::BSFixedStringWCS& a_value)
	{
		if (a_key.size() <= sizeof(KEY_PREFIX) || a_key[0] != KEY_PREFIX) {
			return false;
		}

		auto lock = std::unique_lock{ Mutex };

		auto* translator = GetTranslator();
		if (!translator) {
			return false;
		}

		auto& translationMap = translator->translationMap;
		auto&& [_, hasInserted] = translationMap.emplace(a_key, a_value);
		return hasInserted;
	}

	bool Remove(std::string_view a_key)
	{
		const auto key = Encoder::FromUTF8ToUTF16(a_key);
		if (!key.has_value()) {
			return false;
		}

		return Remove(key.value());
	}

	bool Remove(std::wstring_view a_key)
	{
		const auto key = RE::BSFixedStringWCS(a_key);
		return Remove(key);
	}

	bool Remove(const RE::BSFixedStringWCS& a_key)
	{
		auto lock = std::unique_lock{ Mutex };

		auto* translator = GetTranslator();
		if (!translator) {
			return false;
		}

		auto& translationMap = translator->translationMap;
		auto keyIt = translationMap.find(a_key);

		if (keyIt == translationMap.end()) {
			return false;
		}

		translationMap.erase(keyIt);
		return true;
	}
}
