#pragma once

#include "Internal/Bethesda/Converter.hpp"

namespace System::UInt32
{
	static constexpr auto SCRIPT_NAME = "System:UInt32"sv;

	static std::uint32_t Min(std::monostate)
	{
		return std::numeric_limits<std::uint32_t>::min();
	}

	static std::uint32_t Max(std::monostate)
	{
		return std::numeric_limits<std::uint32_t>::max();
	}

	static std::uint32_t TryParse(std::monostate,
		std::string_view a_string,
		std::int32_t a_base,
		std::uint32_t a_default)
	{
		return ::Internal::Converter::ToUInt32(a_string, a_base).value_or(a_default);
	}

	static std::string ToString(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::uint32_t a_uint,
		std::string_view a_format)
	{
		if (a_format.empty()) {
			return ::Internal::Converter::ToString(a_uint);
		}

		try {
			return fmt::format(fmt::runtime(a_format), a_uint);
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
