#pragma once

#include "Internal/Events/Handlers/ActorDeathHandler.hpp"
#include "Internal/Events/Handlers/CombatStateChangeHandler.hpp"
#include "Internal/Events/Handlers/FurnitureEnterExitHandler.hpp"
#include "Internal/Events/Handlers/ItemEquipUnequipHandler.hpp"
#include "Internal/Events/Handlers/LifeStateChangeHandler.hpp"
#include "Internal/Events/Handlers/LimbCrippleHandler.hpp"
#include "Internal/Events/Handlers/LocationEnterExitHandler.hpp"

namespace System::Events::Actor
{
	static bool IsRegisteredForActorDeath(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::ActorDeathHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForActorDeath(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedSources,
		std::vector<const RE::BSScript::Variable*> a_excludedSources,
		std::vector<const RE::BSScript::Variable*> a_includedTargets,
		std::vector<const RE::BSScript::Variable*> a_excludedTargets)
	{
		return RegisterImpl<::Internal::Events::ActorDeathHandler>(a_vm, a_stackID, a_receiver,
			a_includedSources, a_excludedSources,
			a_includedTargets, a_excludedTargets);
	}

	static bool UnregisterForActorDeath(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::ActorDeathHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForCombatStateChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::CombatStateChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForCombatStateChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedSources,
		std::vector<const RE::BSScript::Variable*> a_excludedSources,
		std::vector<const RE::BSScript::Variable*> a_includedTargets,
		std::vector<const RE::BSScript::Variable*> a_excludedTargets,
		std::vector<RE::ACTOR_COMBAT_STATE> a_includeStates,
		std::vector<RE::ACTOR_COMBAT_STATE> a_excludedStates)
	{
		return RegisterImpl<::Internal::Events::CombatStateChangeHandler>(a_vm, a_stackID, a_receiver,
			a_includedSources, a_excludedSources,
			a_includedTargets, a_excludedTargets,
			a_includeStates, a_excludedStates);
	}

	static bool UnregisterForCombatStateChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::CombatStateChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForFurnitureEnterExit(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::FurnitureEnterExitHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForFurnitureEnterExit(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedSources,
		std::vector<const RE::BSScript::Variable*> a_excludedSources,
		std::vector<const RE::BSScript::Variable*> a_includedTargets,
		std::vector<const RE::BSScript::Variable*> a_excludedTargets)
	{
		return RegisterImpl<::Internal::Events::FurnitureEnterExitHandler>(a_vm, a_stackID, a_receiver,
			a_includedSources, a_excludedSources,
			a_includedTargets, a_excludedTargets);
	}

	static bool UnregisterForFurnitureEnterExit(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::FurnitureEnterExitHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForItemEquipUnequip(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::ItemEquipUnequipHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForItemEquipUnequip(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedSources,
		std::vector<const RE::BSScript::Variable*> a_excludedSources,
		std::vector<const RE::BSScript::Variable*> a_includedTargets,
		std::vector<const RE::BSScript::Variable*> a_excludedTargets)
	{
		return RegisterImpl<::Internal::Events::ItemEquipUnequipHandler>(a_vm, a_stackID, a_receiver,
			a_includedSources, a_excludedSources,
			a_includedTargets, a_excludedTargets);
	}

	static bool UnregisterForItemEquipUnequip(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::ItemEquipUnequipHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForLifeStateChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::LifeStateChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForLifeStateChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedSources,
		std::vector<const RE::BSScript::Variable*> a_excludedSources,
		std::vector<RE::ACTOR_LIFE_STATE> a_includedOldStates,
		std::vector<RE::ACTOR_LIFE_STATE> a_excludedOldStates,
		std::vector<RE::ACTOR_LIFE_STATE> a_includedNewStates,
		std::vector<RE::ACTOR_LIFE_STATE> a_excludedNewStates)
	{
		return RegisterImpl<::Internal::Events::LifeStateChangeHandler>(a_vm, a_stackID, a_receiver,
			a_includedSources, a_excludedSources,
			a_includedOldStates, a_excludedOldStates,
			a_includedNewStates, a_excludedNewStates);
	}

	static bool UnregisterForLifeStateChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::LifeStateChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForLimbCripple(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::LimbCrippleHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForLimbCripple(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedSources,
		std::vector<const RE::BSScript::Variable*> a_excludedSources,
		std::vector<const RE::BSScript::Variable*> a_includedLimbs,
		std::vector<const RE::BSScript::Variable*> a_excludedLimbs)
	{
		return RegisterImpl<::Internal::Events::LimbCrippleHandler>(a_vm, a_stackID, a_receiver,
			a_includedSources, a_excludedSources,
			a_includedLimbs, a_excludedLimbs);
	}

	static bool UnregisterForLimbCripple(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::LimbCrippleHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForLocationEnterExit(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::LocationEnterExitHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForLocationEnterExit(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedSources,
		std::vector<const RE::BSScript::Variable*> a_excludedSources,
		std::vector<const RE::BSScript::Variable*> a_includedOldLocations,
		std::vector<const RE::BSScript::Variable*> a_excludedOldLocations,
		std::vector<const RE::BSScript::Variable*> a_includedNewLocations,
		std::vector<const RE::BSScript::Variable*> a_excludedNewLocations)
	{
		return RegisterImpl<::Internal::Events::LocationEnterExitHandler>(a_vm, a_stackID, a_receiver,
			a_includedSources, a_excludedSources,
			a_includedOldLocations, a_excludedOldLocations,
			a_includedNewLocations, a_excludedNewLocations);
	}

	static bool UnregisterForLocationEnterExit(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::LocationEnterExitHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForActorDeath);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForActorDeath);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForActorDeath);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForCombatStateChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForCombatStateChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForCombatStateChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForFurnitureEnterExit);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForFurnitureEnterExit);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForFurnitureEnterExit);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForItemEquipUnequip);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForItemEquipUnequip);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForItemEquipUnequip);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForLifeStateChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForLifeStateChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForLifeStateChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForLimbCripple);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForLimbCripple);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForLimbCripple);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForLocationEnterExit);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForLocationEnterExit);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForLocationEnterExit);

		return true;
	}
}
