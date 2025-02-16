#include "Internal/Events/Patches/ObjectHitPatch.hpp"

#include "Internal/Events/Patches/VTables.hpp"
#include "Internal/Events/Sources/ObjectHitSource.hpp"

namespace Internal::Events::ObjectHitPatch
{
	static auto _ProcessEvent = REL::Relocation<decltype(&RE::BSTEventSink<RE::TESHitEvent>::ProcessEvent)>();

	static RE::BSEventNotifyControl ProcessEvent(RE::BSTEventSink<RE::TESHitEvent>* a_this,
		const RE::TESHitEvent& a_event, RE::BSTEventSource<RE::TESHitEvent>* a_source)
	{
		ObjectHitSource::GetEventSource()->Notify(a_event);
		return _ProcessEvent(a_this, a_event, a_source);
	}

	void Install() noexcept
	{
		auto vtable = REL::Relocation<std::uintptr_t>{ VTables::CombatEventHandler_TESHitEvent };
		_ProcessEvent = vtable.write_vfunc(0x1, ProcessEvent);
	}
}
