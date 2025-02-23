#pragma once

namespace Internal::Converter
{
	inline const auto NONE = "None"s;
	inline const auto TRUE = "True"s;
	inline const auto FALSE = "False"s;

	bool ToBool(std::string_view a_value) noexcept;
	std::string ToString(bool a_value) noexcept;

	std::optional<std::int32_t> ToInt32(std::string_view a_value, std::int32_t a_base = 10) noexcept;
	std::string ToString(std::int32_t a_value) noexcept;

	std::optional<std::uint32_t> ToUInt32(std::string_view a_value, std::int32_t a_base = 10) noexcept;
	std::string ToString(std::uint32_t a_value) noexcept;

	std::optional<float> ToFloat(std::string_view a_value, std::chars_format a_format = std::chars_format::general) noexcept;
	std::string ToString(float a_value) noexcept;

	std::string ToString(std::string_view a_value) noexcept;
	std::string ToString(const RE::BSFixedString& a_value) noexcept;

	std::string ToString(const RE::BSTSmartPointer<RE::BSScript::Object>& a_value);
	std::string ToString(const RE::BSTSmartPointer<RE::BSScript::Struct>& a_value);
	std::string ToString(const RE::BSTSmartPointer<RE::BSScript::Array>& a_value);

	std::string ToString(const RE::BSScript::Variable* a_value);
	std::string ToString(const RE::TESForm* a_value);
}
