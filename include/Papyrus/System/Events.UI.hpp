#pragma once

#include "Internal/Events/Handlers/CrosshairRefChangeHandler.hpp"
#include "Internal/Events/Handlers/HUDColorUpdateHandler.hpp"
#include "Internal/Events/Handlers/MenuModeEnterExitHandler.hpp"
#include "Internal/Events/Handlers/MenuOpenCloseHandler.hpp"
#include "Internal/Events/Handlers/TutorialTriggerHandler.hpp"

namespace System::Events::UI
{
	static bool IsRegisteredForCrosshairRefChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::CrosshairRefChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForCrosshairRefChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects)
	{
		return RegisterImpl<::Internal::Events::CrosshairRefChangeHandler>(a_vm, a_stackID, a_receiver,
			a_includedObjects, a_excludedObjects);
	}

	static bool UnregisterForCrosshairRefChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::CrosshairRefChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForHUDColorUpdate(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::HUDColorUpdateHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForHUDColorUpdate(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return RegisterImpl<::Internal::Events::HUDColorUpdateHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool UnregisterForHUDColorUpdate(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::HUDColorUpdateHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForMenuModeEnterExit(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::MenuModeEnterExitHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForMenuModeEnterExit(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<RE::BSFixedString> a_includedMenuNames,
		std::vector<RE::BSFixedString> a_excludedMenuNames)
	{
		return RegisterImpl<::Internal::Events::MenuModeEnterExitHandler>(a_vm, a_stackID, a_receiver,
			a_includedMenuNames, a_excludedMenuNames);
	}

	static bool UnregisterForMenuModeEnterExit(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::MenuModeEnterExitHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForMenuOpenClose(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::MenuOpenCloseHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForMenuOpenClose(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<RE::BSFixedString> a_includedMenuNames,
		std::vector<RE::BSFixedString> a_excludedMenuNames)
	{
		return RegisterImpl<::Internal::Events::MenuOpenCloseHandler>(a_vm, a_stackID, a_receiver,
			a_includedMenuNames, a_excludedMenuNames);
	}

	static bool UnregisterForMenuOpenClose(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::MenuOpenCloseHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForTutorialTrigger(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::TutorialTriggerHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForTutorialTrigger(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<RE::BSFixedString> a_includedEventNames,
		std::vector<RE::BSFixedString> a_excludedEventNames)
	{
		return RegisterImpl<::Internal::Events::TutorialTriggerHandler>(a_vm, a_stackID, a_receiver,
			a_includedEventNames, a_excludedEventNames);
	}

	static bool UnregisterForTutorialTrigger(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::TutorialTriggerHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForCrosshairRefChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForCrosshairRefChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForCrosshairRefChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForHUDColorUpdate);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForHUDColorUpdate);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForHUDColorUpdate);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForMenuModeEnterExit);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForMenuModeEnterExit);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForMenuModeEnterExit);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForMenuOpenClose);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForMenuOpenClose);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForMenuOpenClose);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForTutorialTrigger);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForTutorialTrigger);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForTutorialTrigger);

		return true;
	}
}
