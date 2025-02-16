#pragma once

#include "Internal/Events/Handlers/ActorValueChangeHandler.hpp"
#include "Internal/Events/Handlers/AnimationGraphEventHandler.hpp"
#include "Internal/Events/Handlers/ContainerChangeHandler.hpp"
#include "Internal/Events/Handlers/DestructionStageChangeHandler.hpp"
#include "Internal/Events/Handlers/MagicEffectApplyHandler.hpp"
#include "Internal/Events/Handlers/ObjectActivateHandler.hpp"
#include "Internal/Events/Handlers/ObjectGrabReleaseHandler.hpp"
#include "Internal/Events/Handlers/ObjectHitHandler.hpp"
#include "Internal/Events/Handlers/ObjectLoadUnloadHandler.hpp"
#include "Internal/Events/Handlers/ObjectOpenCloseHandler.hpp"
#include "Internal/Events/Handlers/TriggerEnterLeaveHandler.hpp"

namespace System::Events::Object
{
	static bool IsRegisteredForActorValueChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::ActorValueChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForActorValueChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects,
		std::vector<const RE::BSScript::Variable*> a_includedActorValues,
		std::vector<const RE::BSScript::Variable*> a_excludedActorValues)
	{
		return RegisterImpl<::Internal::Events::ActorValueChangeHandler>(a_vm, a_stackID, a_receiver,
			a_includedObjects, a_excludedObjects,
			a_includedActorValues, a_excludedActorValues);
	}

	static bool UnregisterForActorValueChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::ActorValueChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForAnimationGraphEvent(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::AnimationGraphEventHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForAnimationGraphEvent(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects,
		std::vector<RE::BSFixedString> a_includedEventNames,
		std::vector<RE::BSFixedString> a_excludedEventNames,
		std::vector<RE::BSFixedString> a_includedPayloads,
		std::vector<RE::BSFixedString> a_excludedPayloads)
	{
		return RegisterImpl<::Internal::Events::AnimationGraphEventHandler>(a_vm, a_stackID, a_receiver,
			a_includedObjects, a_excludedObjects,
			a_includedEventNames, a_excludedEventNames,
			a_includedPayloads, a_excludedPayloads);
	}

	static bool UnregisterForAnimationGraphEvent(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::AnimationGraphEventHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForContainerChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::ContainerChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForContainerChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedSources,
		std::vector<const RE::BSScript::Variable*> a_excludedSources,
		std::vector<const RE::BSScript::Variable*> a_includedTargets,
		std::vector<const RE::BSScript::Variable*> a_excludedTargets,
		std::vector<const RE::BSScript::Variable*> a_includedItems,
		std::vector<const RE::BSScript::Variable*> a_excludedItems)
	{
		return RegisterImpl<::Internal::Events::ContainerChangeHandler>(a_vm, a_stackID, a_receiver,
			a_includedSources, a_excludedSources,
			a_includedTargets, a_excludedTargets,
			a_includedItems, a_excludedItems);
	}

	static bool UnregisterForContainerChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::ContainerChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForDestructionStageChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::DestructionStageChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForDestructionStageChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects,
		std::vector<std::uint32_t> a_includedOldStages,
		std::vector<std::uint32_t> a_excludedOldStages,
		std::vector<std::uint32_t> a_includedNewStages,
		std::vector<std::uint32_t> a_excludedNewStages)
	{
		return RegisterImpl<::Internal::Events::DestructionStageChangeHandler>(a_vm, a_stackID, a_receiver,
			a_includedObjects, a_excludedObjects,
			a_includedOldStages, a_excludedOldStages,
			a_includedNewStages, a_excludedNewStages);
	}

	static bool UnregisterForDestructionStageChange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::DestructionStageChangeHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForMagicEffectApply(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::MagicEffectApplyHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForMagicEffectApply(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedSources,
		std::vector<const RE::BSScript::Variable*> a_excludedSources,
		std::vector<const RE::BSScript::Variable*> a_includedTargets,
		std::vector<const RE::BSScript::Variable*> a_excludedTargets,
		std::vector<const RE::BSScript::Variable*> a_includedEffects,
		std::vector<const RE::BSScript::Variable*> a_excludedEffects)
	{
		return RegisterImpl<::Internal::Events::MagicEffectApplyHandler>(a_vm, a_stackID, a_receiver,
			a_includedSources, a_excludedSources,
			a_includedTargets, a_excludedTargets,
			a_includedEffects, a_excludedEffects);
	}

	static bool UnregisterForMagicEffectApply(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::MagicEffectApplyHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForObjectActivate(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::ObjectActivateHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForObjectActivate(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedSources,
		std::vector<const RE::BSScript::Variable*> a_excludedSources,
		std::vector<const RE::BSScript::Variable*> a_includedTargets,
		std::vector<const RE::BSScript::Variable*> a_excludedTargets)
	{
		return RegisterImpl<::Internal::Events::ObjectActivateHandler>(a_vm, a_stackID, a_receiver,
			a_includedSources, a_excludedSources,
			a_includedTargets, a_excludedTargets);
	}

	static bool UnregisterForObjectActivate(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::ObjectActivateHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForObjectGrabRelease(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::ObjectGrabReleaseHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForObjectGrabRelease(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects)
	{
		return RegisterImpl<::Internal::Events::ObjectGrabReleaseHandler>(a_vm, a_stackID, a_receiver,
			a_includedObjects, a_excludedObjects);
	}

	static bool UnregisterForObjectGrabRelease(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::ObjectGrabReleaseHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForObjectHit(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::ObjectHitHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForObjectHit(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedSources,
		std::vector<const RE::BSScript::Variable*> a_excludedSources,
		std::vector<const RE::BSScript::Variable*> a_includedTargets,
		std::vector<const RE::BSScript::Variable*> a_excludedTargets,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects,
		std::vector<const RE::BSScript::Variable*> a_includedProjectiles,
		std::vector<const RE::BSScript::Variable*> a_excludedProjectiles,
		std::vector<RE::BSFixedString> a_includedMaterialNames,
		std::vector<RE::BSFixedString> a_excludedMaterialNames,
		RE::HitData::Flags a_includedFlags,
		RE::HitData::Flags a_excludedFlags)
	{
		return RegisterImpl<::Internal::Events::ObjectHitHandler>(a_vm, a_stackID, a_receiver,
			a_includedSources, a_excludedSources,
			a_includedTargets, a_excludedTargets,
			a_includedObjects, a_excludedObjects,
			a_includedProjectiles, a_excludedProjectiles,
			a_includedMaterialNames, a_excludedMaterialNames,
			a_includedFlags, a_excludedFlags);
	}

	static bool UnregisterForObjectHit(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::ObjectHitHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForObjectLoadUnload(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::ObjectLoadUnloadHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForObjectLoadUnload(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects)
	{
		return RegisterImpl<::Internal::Events::ObjectLoadUnloadHandler>(a_vm, a_stackID, a_receiver,
			a_includedObjects, a_excludedObjects);
	}

	static bool UnregisterForObjectLoadUnload(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::ObjectLoadUnloadHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForObjectOpenClose(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::ObjectOpenCloseHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForObjectOpenClose(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedSources,
		std::vector<const RE::BSScript::Variable*> a_excludedSources,
		std::vector<const RE::BSScript::Variable*> a_includedTargets,
		std::vector<const RE::BSScript::Variable*> a_excludedTargets)
	{
		return RegisterImpl<::Internal::Events::ObjectOpenCloseHandler>(a_vm, a_stackID, a_receiver,
			a_includedSources, a_excludedSources,
			a_includedTargets, a_excludedTargets);
	}

	static bool UnregisterForObjectOpenClose(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::ObjectOpenCloseHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool IsRegisteredForTriggerEnterLeave(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return IsRegisteredImpl<::Internal::Events::TriggerEnterLeaveHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterForTriggerEnterLeave(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::vector<const RE::BSScript::Variable*> a_includedSources,
		std::vector<const RE::BSScript::Variable*> a_excludedSources,
		std::vector<const RE::BSScript::Variable*> a_includedTargets,
		std::vector<const RE::BSScript::Variable*> a_excludedTargets)
	{
		return RegisterImpl<::Internal::Events::TriggerEnterLeaveHandler>(a_vm, a_stackID, a_receiver,
			a_includedSources, a_excludedSources,
			a_includedTargets, a_excludedTargets);
	}

	static bool UnregisterForTriggerEnterLeave(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::TriggerEnterLeaveHandler>(a_vm, a_stackID, a_receiver);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForActorValueChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForActorValueChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForActorValueChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForAnimationGraphEvent);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForAnimationGraphEvent);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForAnimationGraphEvent);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForContainerChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForContainerChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForContainerChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForDestructionStageChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForDestructionStageChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForDestructionStageChange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForMagicEffectApply);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForMagicEffectApply);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForMagicEffectApply);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForObjectActivate);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForObjectActivate);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForObjectActivate);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForObjectGrabRelease);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForObjectGrabRelease);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForObjectGrabRelease);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForObjectHit);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForObjectHit);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForObjectHit);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForObjectLoadUnload);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForObjectLoadUnload);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForObjectLoadUnload);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForObjectOpenClose);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForObjectOpenClose);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForObjectOpenClose);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForTriggerEnterLeave);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForTriggerEnterLeave);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForTriggerEnterLeave);

		return true;
	}
}
