#pragma once

namespace System::Char
{
	static constexpr auto SCRIPT_NAME = "System:Char"sv;

	static char Min(std::monostate)
	{
		return std::numeric_limits<char>::min();
	}

	static char Max(std::monostate)
	{
		return std::numeric_limits<char>::max();
	}

	static char TryParse(std::monostate,
		std::string_view a_string,
		char a_default)
	{
		return a_string.size() == 1 ? a_string[0] : a_default;
	}

	static std::string ToString(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		char a_char,
		std::string_view a_format)
	{
		if (a_format.empty()) {
			return std::string{ a_char };
		}

		try {
			return fmt::format(fmt::runtime(a_format), a_char);
		}
		catch (const fmt::format_error& a_error) {
			a_vm.PostError(a_error.what(), a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Min);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Max);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, TryParse);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ToString);

		return true;
	}
}
