#pragma once

#include "Internal/Bethesda/Converter.hpp"

#include <fmt/args.h>

namespace System::Strings::Manipulation
{
	static std::string Substring(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_string,
		std::int32_t a_startIndex,
		std::int32_t a_count)
	{
		const auto size = static_cast<std::int32_t>(a_string.size());
		if (a_startIndex < 0 || a_startIndex >= size) {
			a_vm.PostError(fmt::format(::Internal::Errors::START_INDEX_OUT_OF_RANGE, a_startIndex, 0, size),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		if (a_count == 0) {
			return {};
		}

		return std::string{ a_string.substr(a_startIndex, a_count) };
	}

	static std::string Remove(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string a_string,
		std::int32_t a_startIndex,
		std::int32_t a_count)
	{
		const auto size = static_cast<std::int32_t>(a_string.size());
		if (a_startIndex < 0 || a_startIndex >= size) {
			a_vm.PostError(fmt::format(::Internal::Errors::START_INDEX_OUT_OF_RANGE, a_startIndex, 0, size),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		if (a_count == 0) {
			return a_string;
		}

		return a_string.erase(a_startIndex, a_count);
	}

	static std::string Insert(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string a_string,
		std::int32_t a_index,
		std::string_view a_substring)
	{
		const auto size = static_cast<std::int32_t>(a_string.size());
		if (a_index < 0 || a_index >= size) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_index, 0, size),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		if (a_substring.empty()) {
			return a_string;
		}

		return a_string.insert(a_index, a_substring);
	}

	static std::string ReplaceAt(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string a_string,
		std::int32_t a_index,
		std::string_view a_replacement)
	{
		if (a_index < 0 || a_index >= static_cast<std::int32_t>(a_string.size())) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_index, 0, a_string.size()),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		if (a_replacement.empty()) {
			return a_string;
		}

		return a_string.replace(a_index, a_replacement.size(), a_replacement);
	}

	static std::string Replace(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string a_string,
		std::string_view a_substring,
		std::string_view a_replacement,
		std::int32_t a_count)
	{
		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		if (a_count == 0 || a_substring.empty()) {
			return a_string;
		}

		const auto comparer = [](char a_left, char a_right) noexcept {
			return std::tolower(a_left) == std::tolower(a_right);
		};

		auto i = 0ui64;

		for (; a_count > 0; a_count--) {
			const auto it = std::search(a_string.begin() + i, a_string.end(), a_substring.begin(), a_substring.end(), comparer);
			if (it == a_string.end()) {
				break;
			}

			const auto position = std::distance(a_string.begin(), it);
			a_string.replace(position, a_substring.size(), a_replacement);
			i = position + a_replacement.size();
		}

		return a_string;
	}

	static std::vector<std::string> Split(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_string,
		std::string_view a_separator,
		std::int32_t a_count)
	{
		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		if (a_count == 0 || a_separator.empty()) {
			return { std::string(a_string) };
		}

		auto i = 0ui64;
		auto result = std::vector<std::string>();

		for (; a_count > 1; a_count--) {
			const auto it = std::search(a_string.begin() + i, a_string.end(), a_separator.begin(), a_separator.end());
			if (it == a_string.end()) {
				break;
			}

			const auto position = std::distance(a_string.begin(), it);
			result.emplace_back(a_string.substr(i, position - i));
			i = position + a_separator.size();
		}

		result.emplace_back(a_string.substr(i));
		return result;
	}

	static std::string Join(std::monostate,
		std::vector<std::string_view> a_strings,
		std::string_view a_separator)
	{
		auto result = std::string();
		for (auto it = a_strings.begin(); it != a_strings.end(); it++) {
			result += *it;
			if (it != a_strings.end() - 1) {
				result += a_separator;
			}
		}

		return result;
	}

	static std::string Concat(std::monostate,
		std::vector<std::string_view> a_strings)
	{
		auto result = std::string();
		for (const auto& string : a_strings) {
			result += string;
		}

		return result;
	}

	static std::string Repeat(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_string,
		std::int32_t a_count)
	{
		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		if (a_count == 0) {
			return {};
		}

		auto result = std::string();
		result.reserve(a_string.size() * a_count);

		for (auto i = 0; i < a_count; i++) {
			result += a_string;
		}

		return result;
	}

	static std::string Reverse(std::monostate,
		std::string a_string)
	{
		std::ranges::reverse(a_string);
		return a_string;
	}

	static std::string ToLower(std::monostate,
		std::string a_string)
	{
		std::ranges::transform(a_string, a_string.begin(), ::tolower);
		return a_string;
	}

	static std::string ToUpper(std::monostate,
		std::string a_string)
	{
		std::ranges::transform(a_string, a_string.begin(), ::toupper);
		return a_string;
	}

	static std::string Trim(std::monostate,
		std::string_view a_string,
		std::string_view a_trimString)
	{
		if (a_trimString.empty()) {
			return std::string(a_string);
		}

		const auto filter = [=](char a_left) noexcept {
			return std::ranges::any_of(a_trimString, [=](char a_right) noexcept {
				return std::tolower(a_left) == std::tolower(a_right);
			});
		};

		const auto begin = std::ranges::find_if_not(a_string, filter);
		const auto end = std::ranges::find_if_not(a_string | std::ranges::views::reverse, filter);

		return { begin, end.base() };
	}

	static std::string TrimStart(std::monostate,
		std::string_view a_string,
		std::string_view a_trimString)
	{
		if (a_trimString.empty()) {
			return std::string(a_string);
		}

		const auto begin = std::ranges::find_if_not(a_string, [=](char a_left) noexcept {
			return std::ranges::any_of(a_trimString, [=](char a_right) noexcept {
				return std::tolower(a_left) == std::tolower(a_right);
			});
		});

		return { begin, a_string.end() };
	}

	static std::string TrimEnd(std::monostate,
		std::string_view a_string,
		std::string_view a_trimString)
	{
		if (a_trimString.empty()) {
			return std::string(a_string);
		}

		const auto end = std::ranges::find_if_not(a_string | std::ranges::views::reverse, [=](char a_left) noexcept {
			return std::ranges::any_of(a_trimString, [=](char a_right) noexcept {
				return std::tolower(a_left) == std::tolower(a_right);
			});
		});

		return { a_string.begin(), end.base() };
	}

	static std::string PadLeft(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string a_string,
		std::int32_t a_totalSize,
		std::string_view a_padString)
	{
		if (a_totalSize < 0) {
			a_vm.PostError(::Internal::Errors::TOTAL_SIZE_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		if (a_padString.empty()) {
			return a_string;
		}

		const auto padSize = a_totalSize - a_string.size();
		if (padSize <= 0) {
			return a_string;
		}

		const auto padCount = padSize / a_padString.size();
		const auto padRemainder = padSize % a_padString.size();

		auto padding = std::string();
		padding.reserve(padSize);

		for (auto i = 0ui32; i < padCount; i++) {
			padding += a_padString;
		}

		padding += a_padString.substr(0, padRemainder);
		return padding + a_string;
	}

	static std::string PadRight(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string a_string,
		std::int32_t a_totalSize,
		std::string_view a_padString)
	{
		if (a_totalSize < 0) {
			a_vm.PostError(::Internal::Errors::TOTAL_SIZE_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		if (a_padString.empty()) {
			return a_string;
		}

		const auto padSize = a_totalSize - a_string.size();
		if (padSize <= 0) {
			return a_string;
		}

		const auto padCount = padSize / a_padString.size();
		const auto padRemainder = padSize % a_padString.size();

		auto padding = std::string();
		padding.reserve(padSize);

		for (auto i = 0ui32; i < padCount; i++) {
			padding += a_padString;
		}

		padding += a_padString.substr(0, padRemainder);
		return a_string + padding;
	}

	static std::string Truncate(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string a_string,
		std::int32_t a_totalSize,
		std::string_view a_suffix)
	{
		if (a_totalSize < 0) {
			a_vm.PostError(::Internal::Errors::TOTAL_SIZE_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		if (a_suffix.empty()) {
			return a_string;
		}

		const auto size = static_cast<std::int32_t>(a_string.size());
		if (size <= a_totalSize) {
			return a_string;
		}

		auto result = a_string.substr(0, a_totalSize);
		return result += a_suffix;
	}

	static std::string Format(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_format,
		std::vector<const RE::BSScript::Variable*> a_args)
	{
		if (a_format.empty() || a_args.empty()) {
			return std::string(a_format);
		}

		auto args = fmt::dynamic_format_arg_store<fmt::format_context>();
		args.reserve(a_args.size(), 0);

		for (const auto* arg : a_args) {
			if (!arg) {
				args.push_back(::Internal::Converter::NONE);
				continue;
			}

			switch (arg->GetType().GetRawType()) {
				case RE::BSScript::TypeInfo::RawType::kBool: {
					const auto value = RE::BSScript::get<bool>(*arg);
					args.push_back(value);
					break;
				}
				case RE::BSScript::TypeInfo::RawType::kInt: {
					const auto value = RE::BSScript::get<std::int32_t>(*arg);
					args.push_back(value);
					break;
				}
				case RE::BSScript::TypeInfo::RawType::kFloat: {
					const auto value = RE::BSScript::get<float>(*arg);
					args.push_back(value);
					break;
				}
				case RE::BSScript::TypeInfo::RawType::kString: {
					const auto value = RE::BSScript::detail::UnpackVariable<std::string_view>(*arg);
					args.push_back(value);
					break;
				}
				default: {
					const auto value = ::Internal::Converter::ToString(arg);
					args.push_back(value);
					break;
				}
			}
		}

		try {
			return fmt::vformat(a_format, args);
		}
		catch (const fmt::format_error& a_error) {
			a_vm.PostError(a_error.what(), a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Substring);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Remove);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Insert);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ReplaceAt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Replace);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Split);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Join);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Concat);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Repeat);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Reverse);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ToLower);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ToUpper);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Trim);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, TrimStart);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, TrimEnd);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, PadLeft);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, PadRight);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Truncate);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Format);

		return true;
	}
}
