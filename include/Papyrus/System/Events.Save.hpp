#pragma once

#include "Internal/Events/Handlers/DeleteGameHandler.hpp"
#include "Internal/Events/Handlers/PostLoadGameHandler.hpp"
#include "Internal/Events/Handlers/PostSaveGameHandler.hpp"
#include "Internal/Events/Handlers/PreSaveGameHandler.hpp"

namespace System::Events::Save
{
	static bool IsRegisteredForDeleteGame(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::DeleteGameHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForDeleteGame(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return RegisterImpl<::Internal::Events::DeleteGameHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool UnregisterForDeleteGame(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::DeleteGameHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForPreSaveGame(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::PreSaveGameHandler>(a_vm, a_stackID, a_receiver);
	}

	bool RegisterForPreSaveGame(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return RegisterImpl<::Internal::Events::PreSaveGameHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool UnregisterForPreSaveGame(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::PreSaveGameHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForPostLoadGame(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::PostLoadGameHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForPostLoadGame(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return RegisterImpl<::Internal::Events::PostLoadGameHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool UnregisterForPostLoadGame(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::PostLoadGameHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForPostSaveGame(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::PostSaveGameHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForPostSaveGame(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return RegisterImpl<::Internal::Events::PostSaveGameHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool UnregisterForPostSaveGame(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::PostSaveGameHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForDeleteGame);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForDeleteGame);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForDeleteGame);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForPostLoadGame);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForPostLoadGame);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForPostLoadGame);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForPostSaveGame);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForPostSaveGame);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForPostSaveGame);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForPreSaveGame);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForPreSaveGame);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForPreSaveGame);

		return true;
	}
}
