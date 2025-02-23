#include "Internal/Bethesda/Converter.hpp"

namespace Internal::Converter
{
	static const auto OBJECT_START = "["s;
	static const auto OBJECT_END = "]"s;
	static const auto OBJECT_SEPARATOR = ", "s;

	std::string ToString(bool a_value) noexcept
	{
		return a_value ? TRUE : FALSE;
	}

	bool ToBool(std::string_view a_value) noexcept
	{
		return Comparer::CompareString(a_value, TRUE) == std::strong_ordering::equal;
	}

	std::optional<std::int32_t> ToInt32(std::string_view a_value, std::int32_t a_base) noexcept
	{
		if (a_value.empty()) {
			return std::nullopt;
		}

		auto value = 0;
		auto result = std::from_chars(a_value.data(), a_value.data() + a_value.size(), value, a_base);

		if (result.ec == std::errc()) {
			return value;
		}
		else {
			return std::nullopt;
		}
	}

	std::string ToString(std::int32_t a_value) noexcept
	{
		return std::to_string(a_value);
	}

	std::optional<std::uint32_t> ToUInt32(std::string_view a_value, std::int32_t a_base) noexcept
	{
		if (a_value.empty()) {
			return std::nullopt;
		}

		auto value = 0ui32;
		auto result = std::from_chars(a_value.data(), a_value.data() + a_value.size(), value, a_base);

		if (result.ec == std::errc()) {
			return value;
		}
		else {
			return std::nullopt;
		}
	}

	std::string ToString(std::uint32_t a_value) noexcept
	{
		return std::to_string(a_value);
	}

	std::optional<float> ToFloat(std::string_view a_value, std::chars_format a_format) noexcept
	{
		if (a_value.empty()) {
			return std::nullopt;
		}

		auto value = 0.0f;
		auto result = std::from_chars(a_value.data(), a_value.data() + a_value.size(), value, a_format);

		if (result.ec == std::errc()) {
			return value;
		}
		else {
			return std::nullopt;
		}
	}

	std::string ToString(float a_value) noexcept
	{
		return std::to_string(a_value);
	}

	std::string ToString(std::string_view a_value) noexcept
	{
		return std::string(a_value);
	}

	std::string ToString(const RE::BSFixedString& a_value) noexcept
	{
		return std::string(a_value);
	}

	std::string ToString(const RE::BSTSmartPointer<RE::BSScript::Object>& a_value)
	{
		if (!a_value) {
			return NONE;
		}

		const auto* form = a_value->Resolve<RE::TESForm>();
		if (!form) {
			return NONE;
		}

		return ToString(form);
	}

	std::string ToString(const RE::BSTSmartPointer<RE::BSScript::Struct>& a_value)
	{
		if (!a_value) {
			return NONE;
		}

		const auto lock = RE::BSSpinLock{ a_value->structLock };

		const auto& typeInfo = a_value->type;
		if (!typeInfo) {
			return NONE;
		}

		const auto size = typeInfo->variables.size();
		auto result = OBJECT_START;

		for (auto i = 0ui32; i < size; i++) {
			const auto& var = a_value->variables[i];
			const auto pairIt = std::ranges::find_if(typeInfo->varNameIndexMap, [i](const auto& a_pair) {
				return a_pair.second == i;
			});

			const auto value = ToString(&var);
			result += fmt::format("{} = {}", pairIt->first, value);

			if (i < size - 1) {
				result += OBJECT_SEPARATOR;
			}
		}

		result += OBJECT_END;
		return result;
	}

	std::string ToString(const RE::BSTSmartPointer<RE::BSScript::Array>& a_value)
	{
		if (!a_value) {
			return NONE;
		}

		const auto lock = RE::BSSpinLock{ a_value->elementsLock };
		const auto size = a_value->size();

		auto result = OBJECT_START;

		for (auto i = 0ui32; i < size; i++) {
			result += ToString(&a_value->elements[i]);

			if (i < size - 1) {
				result += OBJECT_SEPARATOR;
			}
		}

		result += OBJECT_END;
		return result;
	}

	std::string ToString(const RE::BSScript::Variable* a_value)
	{
		if (!a_value || !*a_value) {
			return NONE;
		}

		using raw_type_t = RE::BSScript::TypeInfo::RawType;

		switch (a_value->GetType().GetRawType()) {
			case raw_type_t::kBool: {
				const auto value = RE::BSScript::get<bool>(*a_value);
				return ToString(value);
			}
			case raw_type_t::kInt: {
				const auto value = RE::BSScript::get<std::int32_t>(*a_value);
				return ToString(value);
			}
			case raw_type_t::kFloat: {
				const auto value = RE::BSScript::get<float>(*a_value);
				return ToString(value);
			}
			case raw_type_t::kString: {
				const auto value = RE::BSScript::get<RE::BSFixedString>(*a_value);
				return ToString(value);
			}
			case raw_type_t::kObject: {
				const auto value = RE::BSScript::get<RE::BSScript::Object>(*a_value);
				return ToString(value);
			}
			case raw_type_t::kStruct: {
				const auto value = RE::BSScript::get<RE::BSScript::Struct>(*a_value);
				return ToString(value);
			}
			case raw_type_t::kVar: {
				const auto* value = RE::BSScript::get<RE::BSScript::Variable>(*a_value);
				return ToString(value);
			}
			case raw_type_t::kArrayBool:
			case raw_type_t::kArrayInt:
			case raw_type_t::kArrayFloat:
			case raw_type_t::kArrayString:
			case raw_type_t::kArrayObject:
			case raw_type_t::kArrayStruct:
			case raw_type_t::kArrayVar: {
				const auto value = RE::BSScript::get<RE::BSScript::Array>(*a_value);
				return ToString(value);
			}
			default: {
				return NONE;
			}
		}
	}

	std::string ToString(const RE::TESForm* a_value)
	{
		if (!a_value) {
			return NONE;
		}

		return fmt::format("[{} <{} ({:08X})>]", a_value->GetFormTypeString(), a_value->GetFormEditorID(), a_value->GetFormID());
	}
}
