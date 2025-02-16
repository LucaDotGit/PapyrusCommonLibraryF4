#pragma once

namespace Internal::Types
{
	template <typename T>
	concept is_string_v = std::convertible_to<T, std::basic_string_view<typename T::value_type>>;

	template <typename T>
	concept is_form_v = std::is_pointer_v<T> && RE::BSScript::detail::object<std::remove_pointer_t<T>>;

	struct StringHasher final
	{
		template <is_string_v T>
		[[nodiscard]] std::size_t operator()(const T& a_string) const noexcept
		{
			constexpr auto PRIME_NUMBER = 31ui64;

			auto hash = 17ui64;
			for (const auto character : std::basic_string_view<typename T::value_type>{ a_string }) {
				hash = (hash * PRIME_NUMBER) + std::tolower(character);
			}

			return hash;
		}
	};

	struct StringSorter final
	{
		template <is_string_v T>
		[[nodiscard]] bool operator()(const T& a_left, const T& a_right) const noexcept
		{
			return Comparer::CompareString(a_left, a_right) < 0;
		}
	};

	struct StringComparer final
	{
		template <is_string_v T>
		[[nodiscard]] bool operator()(const T& a_left, const T& a_right) const noexcept
		{
			return Comparer::CompareString(a_left, a_right) == std::strong_ordering::equal;
		}
	};

	struct FormHasher final
	{
		[[nodiscard]] std::size_t operator()(const RE::TESForm* a_form) const noexcept
		{
			const auto formID = a_form ? a_form->formID : 0;
			return std::hash<std::uint32_t>()(formID);
		}
	};

	struct FormSorter final
	{
		[[nodiscard]] bool operator()(const RE::TESForm* a_left, const RE::TESForm* a_right) const noexcept
		{
			return Comparer::CompareForm(a_left, a_right) < 0;
		}
	};

	struct FormComparer final
	{
		[[nodiscard]] bool operator()(const RE::TESForm* a_left, const RE::TESForm* a_right) const noexcept
		{
			return Comparer::CompareForm(a_left, a_right) == std::strong_ordering::equal;
		}
	};

	template <is_string_v TKey, typename TValue, class TComparer = StringSorter,
		class TAllocator = std::allocator<std::pair<const TKey, TValue>>>
	using json_map = std::map<TKey, TValue, StringSorter, TAllocator>;

	template <is_string_v TKey, typename TValue>
	using string_map = std::map<TKey, TValue, StringSorter>;

	template <is_string_v TKey, typename TValue>
	using unordered_string_map = std::unordered_map<TKey, TValue, StringHasher, StringComparer>;

	template <is_string_v TKey>
	using string_set = std::set<TKey, StringSorter>;

	template <is_string_v TKey>
	using unordered_string_set = std::unordered_set<TKey, StringHasher, StringComparer>;

	template <is_form_v TKey>
	using form_set = std::set<TKey, FormSorter>;

	template <is_form_v TKey>
	using unordered_form_set = std::unordered_set<TKey, FormHasher, FormComparer>;

	template <is_form_v TKey, typename TValue>
	using form_map = std::map<TKey, TValue, FormSorter>;

	template <is_form_v TKey, typename TValue>
	using unordered_form_map = std::unordered_map<TKey, TValue, FormHasher, FormComparer>;
}
