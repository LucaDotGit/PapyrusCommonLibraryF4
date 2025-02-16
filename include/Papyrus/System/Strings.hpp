#pragma once

namespace System::Strings
{
	static constexpr auto SCRIPT_NAME = "System:Strings"sv;
}

#include "Papyrus/System/Strings.Manipulation.hpp"
#include "Papyrus/System/Strings.Search.hpp"

namespace System::Strings
{
	static RE::BSFixedString Rehash(std::monostate,
		std::string_view a_string)
	{
		return RE::BSFixedString(a_string);
	}

	static std::string_view Empty(std::monostate)
	{
		return {};
	}

	static bool IsEmpty(std::monostate,
		std::string_view a_string)
	{
		return a_string.empty();
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Rehash);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Empty);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsEmpty);

		return Search::RegisterFunctions(a_vm) &&
			   Manipulation::RegisterFunctions(a_vm);
	}
}
