#pragma once

#include "Internal/Events/Handlers/ButtonUpDownHandler.hpp"
#include "Internal/Events/Handlers/CellAttachDetachHandler.hpp"
#include "Internal/Events/Handlers/CellEnterExitHandler.hpp"
#include "Internal/Events/Handlers/CellLoadHandler.hpp"
#include "Internal/Events/Handlers/LocationLoadHandler.hpp"
#include "Internal/Events/Handlers/LockPickHandler.hpp"
#include "Internal/Events/Handlers/PerkPointIncreaseHandler.hpp"
#include "Internal/Events/Handlers/PipBoyLightChangeHandler.hpp"
#include "Internal/Events/Handlers/PowerArmorLightChangeHandler.hpp"
#include "Internal/Events/Handlers/TerminalHackHandler.hpp"

namespace System::Events::Misc
{
	static bool IsRegisteredForButtonUpDown(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::ButtonUpDownHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForButtonUpDown(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<RE::INPUT_DEVICE> a_includedDeviceTypes,
		std::vector<RE::INPUT_DEVICE> a_excludedDeviceTypes,
		std::vector<RE::BS_BUTTON_CODE> a_includedButtonCodes,
		std::vector<RE::BS_BUTTON_CODE> a_excludedButtonCodes,
		std::vector<RE::BSFixedString> a_includedControlNames,
		std::vector<RE::BSFixedString> a_excludedControlNames)
	{
		return RegisterImpl<::Internal::Events::ButtonUpDownHandler>(a_vm, a_stackID, a_receiver,
			a_includedDeviceTypes, a_excludedDeviceTypes,
			a_includedButtonCodes, a_excludedButtonCodes,
			a_includedControlNames, a_excludedControlNames);
	}

	static bool UnregisterForButtonUpDown(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::ButtonUpDownHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForCellAttachDetach(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::CellAttachDetachHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForCellAttachDetach(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects)
	{
		return RegisterImpl<::Internal::Events::CellAttachDetachHandler>(a_vm, a_stackID, a_receiver,
			a_includedObjects, a_excludedObjects);
	}

	static bool UnregisterForCellAttachDetach(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::CellAttachDetachHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForCellEnterExit(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::CellEnterExitHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForCellEnterExit(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects)
	{
		return RegisterImpl<::Internal::Events::CellEnterExitHandler>(a_vm, a_stackID, a_receiver,
			a_includedObjects, a_excludedObjects);
	}

	static bool UnregisterForCellEnterExit(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::CellEnterExitHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForCellLoad(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::CellLoadHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForCellLoad(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects)
	{
		return RegisterImpl<::Internal::Events::CellLoadHandler>(a_vm, a_stackID, a_receiver,
			a_includedObjects, a_excludedObjects);
	}

	static bool UnregisterForCellLoad(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::CellLoadHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForLocationLoad(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::LocationLoadHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForLocationLoad(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects)
	{
		return RegisterImpl<::Internal::Events::LocationLoadHandler>(a_vm, a_stackID, a_receiver,
			a_includedObjects, a_excludedObjects);
	}

	static bool UnregisterForLocationLoad(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::LocationLoadHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForLockPick(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::LockPickHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForLockPick(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects)
	{
		return !REL::Module::IsNG() && RegisterImpl<::Internal::Events::LockPickHandler>(a_vm, a_stackID, a_receiver,
										   a_includedObjects, a_excludedObjects);
	}

	static bool UnregisterForLockPick(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::LockPickHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForPerkPointIncrease(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::PerkPointIncreaseHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForPerkPointIncrease(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return RegisterImpl<::Internal::Events::PerkPointIncreaseHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool UnregisterForPerkPointIncrease(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::PerkPointIncreaseHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForTerminalHack(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::TerminalHackHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForTerminalHack(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects)
	{
		return !REL::Module::IsNG() && RegisterImpl<::Internal::Events::TerminalHackHandler>(a_vm, a_stackID, a_receiver,
										   a_includedObjects, a_excludedObjects);
	}

	static bool UnregisterForTerminalHack(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::TerminalHackHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForPipBoyLightChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::PipBoyLightChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForPipBoyLightChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return RegisterImpl<::Internal::Events::PipBoyLightChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool UnregisterForPipBoyLightChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::PipBoyLightChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForPowerArmorLightChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::PowerArmorLightChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForPowerArmorLightChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return !REL::Module::IsNG() && RegisterImpl<::Internal::Events::PowerArmorLightChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool UnregisterForPowerArmorLightChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::PowerArmorLightChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForButtonUpDown);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForButtonUpDown);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForButtonUpDown);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForCellAttachDetach);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForCellAttachDetach);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForCellAttachDetach);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForCellEnterExit);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForCellEnterExit);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForCellEnterExit);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForCellLoad);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForCellLoad);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForCellLoad);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForLocationLoad);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForLocationLoad);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForLocationLoad);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForLockPick);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForLockPick);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForLockPick);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForPerkPointIncrease);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForPerkPointIncrease);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForPerkPointIncrease);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForTerminalHack);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForTerminalHack);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForTerminalHack);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForPipBoyLightChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForPipBoyLightChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForPipBoyLightChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForPowerArmorLightChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForPowerArmorLightChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForPowerArmorLightChange);

		return true;
	}
}
