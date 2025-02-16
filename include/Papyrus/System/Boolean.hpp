#pragma once

#include "Internal/Bethesda/Converter.hpp"

namespace System::Boolean
{
	static constexpr auto SCRIPT_NAME = "System:Boolean"sv;

	static std::string_view FalseString(std::monostate)
	{
		return ::Internal::Converter::FALSE;
	}

	static std::string_view TrueString(std::monostate)
	{
		return ::Internal::Converter::TRUE;
	}

	static bool TryParse(std::monostate,
		std::string_view a_string)
	{
		return ::Internal::Converter::ToBool(a_string);
	}

	static std::string ToString(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		bool a_bool,
		std::string_view a_format)
	{
		if (a_format.empty()) {
			return ::Internal::Converter::ToString(a_bool);
		}

		try {
			return fmt::format(fmt::runtime(a_format), a_bool);
		}
		catch (const fmt::format_error& a_error) {
			a_vm.PostError(a_error.what(), a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, FalseString);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, TrueString);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, TryParse);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ToString);

		return true;
	}
}
