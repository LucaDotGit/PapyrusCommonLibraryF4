#include "Internal/Events/Patches/CombatStateChangePatch.hpp"

#include "Internal/Events/Patches/VTables.hpp"
#include "Internal/Events/Sources/CombatStateChangeSource.hpp"

namespace Internal::Events::CombatStateChangePatch
{
	static auto _ProcessEvent = REL::Relocation<decltype(&RE::BSTEventSink<RE::TESCombatEvent>::ProcessEvent)>();

	static RE::BSEventNotifyControl ProcessEvent(RE::BSTEventSink<RE::TESCombatEvent>* a_this,
		const RE::TESCombatEvent& a_event, RE::BSTEventSource<RE::TESCombatEvent>* a_source)
	{
		const auto& sourceActor = a_event.actor;
		const auto& targetActor = a_event.targetActor;

		if (sourceActor && targetActor) {
			CombatStateChangeSource::GetEventSource()->Notify(
				{ sourceActor->As<RE::Actor>(), targetActor->As<RE::Actor>(), a_event.setState.get() });
		}

		return _ProcessEvent(a_this, a_event, a_source);
	}

	void Install() noexcept
	{
		auto vtable = REL::Relocation<std::uintptr_t>{ VTables::BasicEventHandler_TESCombatEvent };
		_ProcessEvent = vtable.write_vfunc(0x1, ProcessEvent);
	}
}
