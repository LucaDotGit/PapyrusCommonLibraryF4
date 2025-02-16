#include "Internal/Bethesda/IniSettings.hpp"

namespace Internal::IniSettings
{
	static auto Mutex = std::shared_mutex();
	static auto Settings = Types::unordered_string_map<std::string_view, Types::unordered_string_map<std::string_view, RE::Setting*>>();

	void Setup()
	{
		const auto* collection = RE::INISettingCollection::GetSingleton();
		const auto* prefCollection = RE::INIPrefSettingCollection::GetSingleton();

		const auto collectionSize = std::distance(collection->settings.begin(), collection->settings.end());
		const auto prefCollectionSize = std::distance(prefCollection->settings.begin(), prefCollection->settings.end());

		Settings.reserve(collectionSize + prefCollectionSize);

		const auto addSettings = [&](const RE::SettingCollectionList<RE::Setting>* a_collection) {
			for (auto it = a_collection->settings.begin(); it != a_collection->settings.end(); it++) {
				auto* setting = *it;
				if (!setting) {
					continue;
				}

				const auto pair = setting->GetKey();
				const auto index = pair.find(':');

				const auto hasSection = index != std::string::npos;
				const auto isSectionValid = hasSection && std::isupper(pair[index + 1]);

				const auto section = hasSection && isSectionValid ? pair.substr(index + 1) : ""sv;
				const auto key = hasSection ? pair.substr(0, index) : pair;

				Settings[section][key] = setting;
			}
		};

		addSettings(collection);
		addSettings(prefCollection);
	}

	std::shared_mutex& GetMutex() noexcept
	{
		return Mutex;
	}

	std::vector<std::string_view> GetSections()
	{
		auto sections = std::vector<std::string_view>();
		sections.reserve(Settings.size());

		for (const auto& [section, _] : Settings) {
			sections.emplace_back(section);
		}

		return sections;
	}

	std::vector<std::string_view> GetKeys(std::string_view a_section)
	{
		const auto secIt = Settings.find(a_section);
		if (secIt == Settings.end()) {
			return {};
		}

		auto keys = std::vector<std::string_view>();
		keys.reserve(secIt->second.size());

		for (const auto& [key, _] : secIt->second) {
			keys.emplace_back(key);
		}

		return keys;
	}

	bool ContainsSetting(std::string_view a_section, std::string_view a_key)
	{
		const auto secIt = Settings.find(a_section);
		if (secIt == Settings.end()) {
			return false;
		}

		return secIt->second.contains(a_key);
	}

	bool ContainsSection(std::string_view a_section)
	{
		return Settings.contains(a_section);
	}

	bool ContainsKey(std::string_view a_section, std::string_view a_key)
	{
		const auto secIt = Settings.find(a_section);
		if (secIt == Settings.end()) {
			return false;
		}

		return secIt->second.contains(a_key);
	}

	RE::Setting* GetSetting(std::string_view a_section, std::string_view a_key)
	{
		const auto secIt = Settings.find(a_section);
		if (secIt == Settings.end()) {
			return nullptr;
		}

		const auto keyIt = secIt->second.find(a_key);
		if (keyIt == secIt->second.end()) {
			return nullptr;
		}

		return keyIt->second;
	}

	bool SaveSetting(std::string_view a_section, std::string_view a_key)
	{
		auto* setting = GetSetting(a_section, a_key);
		if (!setting) {
			return false;
		}

		auto* collection = RE::INISettingCollection::GetSingleton();
		auto* prefCollection = RE::INIPrefSettingCollection::GetSingleton();

		return prefCollection->WriteSetting(*setting) || collection->WriteSetting(*setting);
	}
}
