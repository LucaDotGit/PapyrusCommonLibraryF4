#pragma once

namespace System::Regex
{
	static constexpr auto SCRIPT_NAME = "System:Regex"sv;

	static constexpr auto FLAGS = boost::regex::normal |
								  boost::regex::icase |
								  boost::regex::no_empty_expressions;

	static const auto ESCAPE_PATTERN = boost::regex{ R"([.*+?^${}()|[\]\\])"s, FLAGS };
	static constexpr auto ESCAPE_REPLACEMENT = R"(\\$&)"sv;

	static const auto UNESCAPE_PATTERN = boost::regex{ R"(\\([.*+?^${}()|[\]\\]))"s, FLAGS };
	static constexpr auto UNESCAPE_REPLACEMENT = R"($1)"sv;

	[[nodiscard]] static constexpr std::uint32_t GetFlags(std::string_view a_flags) noexcept
	{
		auto flags = FLAGS;

		for (const auto character : a_flags) {
			switch (character) {
				case 'm':
				case 'M':
					flags |= boost::regex_constants::match_not_dot_newline;
					break;
				case 's':
				case 'S':
					flags |= boost::regex_constants::match_single_line;
					break;
				default:
					break;
			}
		}

		return flags;
	}

	static bool IsValid(std::monostate,
		std::string_view a_pattern,
		std::string_view a_flags)
	{
		try {
			boost::regex(a_pattern.begin(), a_pattern.end(), GetFlags(a_flags));
			return true;
		}
		catch (const std::exception&) {
			return false;
		}
	}

	static bool IsMatch(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_string,
		std::string_view a_pattern,
		std::string_view a_flags)
	{
		try {
			const auto regex = boost::regex(a_pattern.begin(), a_pattern.end(), GetFlags(a_flags));
			return boost::regex_search(a_string.begin(), a_string.end(), regex);
		}
		catch (const std::exception& a_error) {
			a_vm.PostError(a_error.what(), a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}
	}

	static std::string Escape(std::monostate,
		std::string a_string)
	{
		try {
			return boost::regex_replace(a_string, ESCAPE_PATTERN, ESCAPE_REPLACEMENT);
		}
		catch (const std::exception&) {
			return a_string;
		}
	}

	static std::string Unescape(std::monostate,
		std::string a_string)
	{
		try {
			return boost::regex_replace(a_string, UNESCAPE_PATTERN, UNESCAPE_REPLACEMENT);
		}
		catch (const std::exception&) {
			return a_string;
		}
	}

	static std::string Match(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string a_string,
		std::string_view a_pattern,
		std::string_view a_flags)
	{
		try {
			const auto regex = boost::regex(a_pattern.begin(), a_pattern.end(), GetFlags(a_flags));
			auto match = boost::smatch();

			return boost::regex_match(a_string, match, regex) ? match.str() : ""s;
		}
		catch (const std::exception& a_error) {
			a_vm.PostError(a_error.what(), a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}
	}

	static std::vector<std::string> Matches(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string a_string,
		std::string_view a_pattern,
		std::string_view a_flags)
	{
		try {
			const auto regex = boost::regex(a_pattern.begin(), a_pattern.end(), GetFlags(a_flags));
			const auto begin = boost::sregex_iterator(a_string.begin(), a_string.end(), regex);
			const auto end = boost::sregex_iterator();

			auto matches = std::vector<std::string>();
			matches.reserve(std::distance(begin, end));

			for (auto it = begin; it != end; it++) {
				const auto& match = *it;

				for (auto i = 0ui32; i < match.size(); i++) {
					matches.emplace_back(match[i].str());
				}
			}

			return matches;
		}
		catch (const std::exception& a_error) {
			a_vm.PostError(a_error.what(), a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}
	}

	static std::int32_t Search(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string a_string,
		std::string_view a_pattern,
		std::string_view a_flags)
	{
		try {
			const auto regex = boost::regex(a_pattern.begin(), a_pattern.end(), GetFlags(a_flags));
			auto match = boost::smatch();

			return boost::regex_search(a_string, match, regex) ? static_cast<std::int32_t>(match.position()) : -1;
		}
		catch (const std::exception& a_error) {
			a_vm.PostError(a_error.what(), a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return -1;
		}
	}

	static std::string Replace(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string a_string,
		std::string_view a_pattern,
		std::string a_replacement,
		std::string_view a_flags)
	{
		try {
			const auto regex = boost::regex(a_pattern.begin(), a_pattern.end(), GetFlags(a_flags));
			return boost::regex_replace(a_string, regex, a_replacement, boost::regex_constants::format_first_only);
		}
		catch (const std::exception& a_error) {
			a_vm.PostError(a_error.what(), a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}
	}

	static std::string ReplaceAll(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string a_string,
		std::string_view a_pattern,
		std::string a_replacement,
		std::string_view a_flags)
	{
		try {
			const auto regex = boost::regex(a_pattern.begin(), a_pattern.end(), GetFlags(a_flags));
			return boost::regex_replace(a_string, regex, a_replacement);
		}
		catch (const std::exception& a_error) {
			a_vm.PostError(a_error.what(), a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}
	}

	static std::vector<std::string> Split(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string a_string,
		std::string_view a_pattern,
		std::int32_t a_count,
		std::string_view a_flags)
	{
		constexpr auto SUBMATCH_ALL = -1;

		try {
			const auto regex = boost::regex(a_pattern.begin(), a_pattern.end(), GetFlags(a_flags));
			const auto begin = boost::sregex_token_iterator(a_string.begin(), a_string.end(), regex, SUBMATCH_ALL);
			const auto end = boost::sregex_token_iterator{};

			auto tokens = std::vector<std::string>();
			tokens.reserve(std::distance(begin, end));

			for (auto it = begin; it != end && a_count > 0; it++, a_count--) {
				tokens.emplace_back(it->str());
			}

			return tokens;
		}
		catch (const std::exception& a_error) {
			a_vm.PostError(a_error.what(), a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsValid);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsMatch);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Escape);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Unescape);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Match);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Matches);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Search);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Replace);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ReplaceAll);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Split);

		return true;
	}
}
