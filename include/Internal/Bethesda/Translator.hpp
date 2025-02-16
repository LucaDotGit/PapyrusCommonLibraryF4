#pragma once

namespace Internal::Translator
{
	inline constexpr auto KEY_PREFIX = '$';

	[[nodiscard]] std::string_view GetLanguageCode();
	[[nodiscard]] RE::BSTranslator* GetTranslator();

	[[nodiscard]] bool Contains(std::string_view a_key);
	[[nodiscard]] bool Contains(std::wstring_view a_key);
	[[nodiscard]] bool Contains(const RE::BSFixedStringWCS& a_key);

	[[nodiscard]] std::optional<std::string> GetString(std::string_view a_key);
	[[nodiscard]] std::optional<std::wstring> GetWString(std::wstring_view a_key);
	[[nodiscard]] std::optional<RE::BSFixedStringWCS> GetBSString(const RE::BSFixedStringWCS& a_key);

	bool SetString(std::string_view a_key, std::string_view a_value);
	bool SetString(std::wstring_view a_key, std::wstring_view a_value);
	bool SetString(const RE::BSFixedStringWCS& a_key, const RE::BSFixedStringWCS& a_value);

	bool Add(std::string_view a_key, std::string_view a_value);
	bool Add(std::wstring_view a_key, std::wstring_view a_value);
	bool Add(const RE::BSFixedStringWCS& a_key, const RE::BSFixedStringWCS& a_value);

	bool Remove(std::string_view a_key);
	bool Remove(std::wstring_view a_key);
	bool Remove(const RE::BSFixedStringWCS& a_key);
}
