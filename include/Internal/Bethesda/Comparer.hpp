#pragma once

namespace Internal::Comparer
{
	[[nodiscard]] std::strong_ordering Compare(
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right);

	[[nodiscard]] bool Equals(
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right);
	[[nodiscard]] bool IsLessThan(
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right);
	[[nodiscard]] bool IsLessThanOrEqual(
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right);
	[[nodiscard]] bool IsGreaterThan(
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right);
	[[nodiscard]] bool IsGreaterThanOrEqual(
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right);
	[[nodiscard]] bool IsInRange(
		const RE::BSScript::Variable* a_value,
		const RE::BSScript::Variable* a_min,
		const RE::BSScript::Variable* a_max);

	template <typename T>
		requires std::is_trivially_copyable_v<std::remove_cvref_t<T>>
	[[nodiscard]] std::strong_ordering CompareValue(T&& a_left, T&& a_right) noexcept
	{
		if (a_left < a_right) {
			return std::strong_ordering::less;
		}

		if (a_left > a_right) {
			return std::strong_ordering::greater;
		}

		return std::strong_ordering::equal;
	}

	template <typename TLeft, typename TRight>
		requires std::same_as<typename TLeft::value_type, typename TRight::value_type> &&
				 (std::same_as<typename TLeft::value_type, char> || std::same_as<typename TLeft::value_type, wchar_t>)
	[[nodiscard]] std::strong_ordering CompareString(const TLeft& a_left, const TRight& a_right) noexcept
	{
		const auto leftSize = a_left.size();
		const auto rightSize = a_right.size();

		if (leftSize != rightSize) {
			return CompareValue(leftSize, rightSize);
		}

		if constexpr (std::same_as<typename TLeft::value_type, char>) {
			return _strnicmp(a_left.data(), a_right.data(), leftSize) <=> 0;
		}
		else {
			return _wcsnicmp(a_left.data(), a_right.data(), leftSize) <=> 0;
		}
	}

	[[nodiscard]] std::strong_ordering CompareForm(
		const RE::TESForm* a_left,
		const RE::TESForm* a_right) noexcept;
	[[nodiscard]] std::strong_ordering CompareObject(
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_left,
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_right) noexcept;
	[[nodiscard]] std::strong_ordering CompareStruct(
		const RE::BSTSmartPointer<RE::BSScript::Struct>& a_left,
		const RE::BSTSmartPointer<RE::BSScript::Struct>& a_right);
	[[nodiscard]] std::strong_ordering CompareArray(
		const RE::BSTSmartPointer<RE::BSScript::Array>& a_left,
		const RE::BSTSmartPointer<RE::BSScript::Array>& a_right);

	[[nodiscard]] bool RefEquals(
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right);

	[[nodiscard]] bool TypeEquals(
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right);
	[[nodiscard]] bool TypeEquals(
		const RE::BSScript::TypeInfo& a_left,
		const RE::BSScript::TypeInfo& a_right);

	[[nodiscard]] RE::BSScript::TypeInfo::RawType GetRawType(const RE::BSScript::Variable* a_var);
}
