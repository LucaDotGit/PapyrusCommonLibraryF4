#pragma once

namespace Internal::IniSettings
{
	void Setup();

	[[nodiscard]] std::shared_mutex& GetMutex() noexcept;

	[[nodiscard]] std::vector<std::string_view> GetSections();
	[[nodiscard]] std::vector<std::string_view> GetKeys(std::string_view a_section);

	[[nodiscard]] bool ContainsSetting(std::string_view a_section, std::string_view a_key);
	[[nodiscard]] bool ContainsSection(std::string_view a_section);
	[[nodiscard]] bool ContainsKey(std::string_view a_section, std::string_view a_key);

	[[nodiscard]] RE::Setting* GetSetting(std::string_view a_section, std::string_view a_key);
	bool SaveSetting(std::string_view a_section, std::string_view a_key);
}
