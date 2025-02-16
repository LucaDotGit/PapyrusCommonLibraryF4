#pragma once

namespace System::Array
{
	static constexpr auto SCRIPT_NAME = "System:Array"sv;
}

#include "Papyrus/System/Array.Creation.hpp"
#include "Papyrus/System/Array.Manipulation.hpp"
#include "Papyrus/System/Array.Search.hpp"

namespace System::Array
{
	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		return Creation::RegisterFunctions(a_vm) &&
			   Manipulation::RegisterFunctions(a_vm) &&
			   Search::RegisterFunctions(a_vm);
	}
}
