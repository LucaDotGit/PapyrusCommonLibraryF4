#pragma once

namespace System::Strings::Search
{
	static bool IsWhitespace(std::monostate,
		std::string_view a_string)
	{
		return std::ranges::all_of(a_string, ::isspace);
	}

	static bool IsBlank(std::monostate,
		std::string_view a_string)
	{
		return std::ranges::all_of(a_string, ::isblank);
	}

	static bool IsDigit(std::monostate,
		std::string_view a_string)
	{
		return std::ranges::all_of(a_string, ::isdigit);
	}

	static bool IsLetter(std::monostate,
		std::string_view a_string)
	{
		return std::ranges::all_of(a_string, ::isalpha);
	}

	static bool IsLetterOrDigit(std::monostate,
		std::string_view a_string)
	{
		return std::ranges::all_of(a_string, ::isalnum);
	}

	static bool IsPunctuation(std::monostate,
		std::string_view a_string)
	{
		return std::ranges::all_of(a_string, ::ispunct);
	}

	static bool IsControl(std::monostate,
		std::string_view a_string)
	{
		return std::ranges::all_of(a_string, ::iscntrl);
	}

	static bool IsGraphic(std::monostate,
		std::string_view a_string)
	{
		return std::ranges::all_of(a_string, ::isgraph);
	}

	static bool IsPrintable(std::monostate,
		std::string_view a_string)
	{
		return std::ranges::all_of(a_string, ::isprint);
	}

	static bool IsLower(std::monostate,
		std::string_view a_string)
	{
		return std::ranges::all_of(a_string, ::islower);
	}

	static bool IsUpper(std::monostate,
		std::string_view a_string)
	{
		return std::ranges::all_of(a_string, ::isupper);
	}

	static bool Contains(std::monostate,
		std::string_view a_string,
		std::string_view a_substring)
	{
		if (a_substring.empty()) {
			return true;
		}

		return std::ranges::contains_subrange(a_string, a_substring, [](char a_left, char a_right) noexcept {
			return std::tolower(a_left) == std::tolower(a_right);
		});
	}

	static bool StartsWith(std::monostate,
		std::string_view a_string,
		std::string_view a_substring)
	{
		if (a_substring.empty()) {
			return true;
		}

		return std::ranges::starts_with(a_string, a_substring, [](char a_left, char a_right) noexcept {
			return std::tolower(a_left) == std::tolower(a_right);
		});
	}

	static bool EndsWith(std::monostate,
		std::string_view a_string,
		std::string_view a_substring)
	{
		if (a_substring.empty()) {
			return true;
		}

		return std::ranges::ends_with(a_string, a_substring, [](char a_left, char a_right) noexcept {
			return std::tolower(a_left) == std::tolower(a_right);
		});
	}

	static bool Any(std::monostate,
		std::string_view a_string,
		std::vector<std::string_view> a_substrings)
	{
		if (a_string.empty() || a_substrings.empty()) {
			return false;
		}

		return std::ranges::any_of(a_substrings, [&](std::string_view a_substring) {
			return std::ranges::contains_subrange(a_string, a_substring, [](char a_left, char a_right) noexcept {
				return std::tolower(a_left) == std::tolower(a_right);
			});
		});
	}

	static bool All(std::monostate,
		std::string_view a_string,
		std::vector<std::string_view> a_substrings)
	{
		if (a_string.empty() || a_substrings.empty()) {
			return false;
		}

		return std::ranges::all_of(a_substrings, [&](std::string_view a_substring) {
			return std::ranges::contains_subrange(a_string, a_substring, [](char a_left, char a_right) noexcept {
				return std::tolower(a_left) == std::tolower(a_right);
			});
		});
	}

	static std::int32_t Size(std::monostate,
		std::string_view a_string)
	{
		return static_cast<std::int32_t>(a_string.size());
	}

	static std::string First(std::monostate,
		std::string_view a_string)
	{
		return std::string{ a_string.front() };
	}

	static std::string Last(std::monostate,
		std::string_view a_string)
	{
		return std::string{ a_string.back() };
	}

	static std::string CharAt(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_string,
		std::int32_t a_index)
	{
		const auto size = static_cast<std::int32_t>(a_string.size());
		if (a_index < 0 || a_index >= size) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_index, 0, size),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		return std::string{ a_string[a_index] };
	}

	static char CharCodeAt(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_string,
		std::int32_t a_index)
	{
		const auto size = static_cast<std::int32_t>(a_string.size());
		if (a_index < 0 || a_index >= size) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_index, 0, size),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return '\0';
		}

		return a_string[a_index];
	}

	static std::vector<std::string> ToCharArray(std::monostate,
		std::string_view a_string)
	{
		auto result = std::vector<std::string>();
		result.reserve(a_string.size());

		for (const auto character : a_string) {
			result.emplace_back(std::string{ character });
		}

		return result;
	}

	static std::int32_t IndexOf(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_string,
		std::string_view a_substring,
		std::int32_t a_startIndex,
		std::int32_t a_count)
	{
		const auto size = static_cast<std::int32_t>(a_string.size());
		if (a_startIndex < 0 || a_startIndex >= size) {
			a_vm.PostError(fmt::format(::Internal::Errors::START_INDEX_OUT_OF_RANGE, a_startIndex, 0, size),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return -1;
		}

		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return -1;
		}

		if (a_substring.empty()) {
			return a_startIndex;
		}

		if (a_count == 0) {
			return -1;
		}

		if (a_count > size) {
			a_count = size;
		}

		const auto begin = a_string.begin() + a_startIndex;
		const auto end = a_string.begin() + std::min(size, a_startIndex + a_count);

		const auto it = std::search(begin, end, a_substring.begin(), a_substring.end(), [](char a_left, char a_right) noexcept {
			return std::tolower(a_left) == std::tolower(a_right);
		});

		return it != end ? static_cast<std::int32_t>(std::distance(a_string.begin(), it)) : -1;
	}

	static std::int32_t IndexOfAny(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_string,
		std::vector<std::string_view> a_substrings,
		std::int32_t a_startIndex,
		std::int32_t a_count)
	{
		const auto size = static_cast<std::int32_t>(a_string.size());
		if (a_startIndex < 0 || a_startIndex >= size) {
			a_vm.PostError(fmt::format(::Internal::Errors::START_INDEX_OUT_OF_RANGE, a_startIndex, 0, size),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return -1;
		}

		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return -1;
		}

		if (a_substrings.empty()) {
			return a_startIndex;
		}

		if (a_count == 0) {
			return -1;
		}

		if (a_count > size) {
			a_count = size;
		}

		const auto begin = a_string.begin() + a_startIndex;
		const auto end = a_string.begin() + std::min(size, a_startIndex + a_count);

		const auto comparer = [](char a_left, char a_right) noexcept {
			return std::tolower(a_left) == std::tolower(a_right);
		};

		for (const auto& substring : a_substrings) {
			const auto it = std::search(begin, end, substring.begin(), substring.end(), comparer);
			if (it != end) {
				return static_cast<std::int32_t>(std::distance(a_string.begin(), it));
			}
		}

		return -1;
	}

	static std::int32_t LastIndexOf(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_string,
		std::string_view a_substring,
		std::int32_t a_startIndex,
		std::int32_t a_count)
	{
		const auto size = static_cast<std::int32_t>(a_string.size());
		if (a_startIndex < 0) {
			a_vm.PostError(::Internal::Errors::START_INDEX_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return -1;
		}

		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return -1;
		}

		if (a_substring.empty()) {
			return size;
		}

		if (a_count == 0) {
			return -1;
		}

		if (a_startIndex >= size) {
			a_startIndex = size - 1;
		}

		if (a_count > size) {
			a_count = size;
		}

		const auto begin = a_string.rbegin() + size - a_startIndex - 1;
		const auto end = a_string.rbegin() + std::min(size, size - a_startIndex - 1 + a_count);

		const auto it = std::search(begin, end, a_substring.rbegin(), a_substring.rend(), [](char a_left, char a_right) noexcept {
			return std::tolower(a_left) == std::tolower(a_right);
		});

		return it != end ? static_cast<std::int32_t>(std::distance(it, a_string.rend()) - a_substring.size()) : -1;
	}

	static std::int32_t LastIndexOfAny(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_string,
		std::vector<std::string_view> a_substrings,
		std::int32_t a_startIndex,
		std::int32_t a_count)
	{
		const auto size = static_cast<std::int32_t>(a_string.size());
		if (a_startIndex < 0) {
			a_vm.PostError(::Internal::Errors::START_INDEX_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return -1;
		}

		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return -1;
		}

		if (a_substrings.empty()) {
			return size;
		}

		if (a_count == 0) {
			return -1;
		}

		if (a_startIndex >= size) {
			a_startIndex = size - 1;
		}

		if (a_count > size) {
			a_count = size;
		}

		const auto begin = a_string.rbegin() + size - a_startIndex - 1;
		const auto end = a_string.rbegin() + std::min(size, size - a_startIndex - 1 + a_count);

		const auto comparer = [](char a_left, char a_right) noexcept {
			return std::tolower(a_left) == std::tolower(a_right);
		};

		for (const auto& substring : a_substrings) {
			const auto it = std::search(begin, end, substring.rbegin(), substring.rend(), comparer);
			if (it != end) {
				return static_cast<std::int32_t>(std::distance(it, a_string.rend()) - substring.size());
			}
		}

		return -1;
	}

	static std::int32_t Count(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_string,
		std::string_view a_substring,
		std::int32_t a_startIndex,
		std::int32_t a_count)
	{
		const auto size = static_cast<std::int32_t>(a_string.size());
		if (a_startIndex < 0 || a_startIndex >= size) {
			a_vm.PostError(fmt::format(::Internal::Errors::START_INDEX_OUT_OF_RANGE, a_startIndex, 0, size),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return -1;
		}

		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return -1;
		}

		if (a_substring.empty()) {
			return a_count;
		}

		if (a_count == 0) {
			return 0;
		}

		if (a_count > size) {
			a_count = size;
		}

		auto begin = a_string.begin() + a_startIndex;
		auto end = a_string.begin() + std::min(size, a_startIndex + a_count);
		auto result = 0;

		const auto comparer = [](char a_left, char a_right) noexcept {
			return std::tolower(a_left) == std::tolower(a_right);
		};

		for (; (begin = std::search(begin, end, a_substring.begin(), a_substring.end(), comparer)) != end; result++) {
			begin += a_substring.size();
		}

		return result;
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsWhitespace);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsBlank);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsDigit);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsLetter);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsLetterOrDigit);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsPunctuation);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsControl);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsGraphic);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsPrintable);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsLower);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsUpper);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Contains);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, StartsWith);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, EndsWith);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Any);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, All);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Size);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, First);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Last);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, CharAt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, CharCodeAt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ToCharArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IndexOf);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IndexOfAny);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, LastIndexOf);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, LastIndexOfAny);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Count);

		return true;
	}
}
