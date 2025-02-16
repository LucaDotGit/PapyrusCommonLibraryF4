#include "Internal/Events/Patches/TriggerLeavePatch.hpp"

#include "Internal/Events/Patches/VTables.hpp"
#include "Internal/Events/Sources/TriggerEnterLeaveSource.hpp"

namespace Internal::Events::TriggerLeavePatch
{
	static auto _ProcessEvent = REL::Relocation<decltype(&RE::BSTEventSink<RE::TESTriggerLeaveEvent>::ProcessEvent)>();

	static RE::BSEventNotifyControl ProcessEvent(RE::BSTEventSink<RE::TESTriggerLeaveEvent>* a_this,
		const RE::TESTriggerLeaveEvent& a_event, RE::BSTEventSource<RE::TESTriggerLeaveEvent>* a_source)
	{
		TriggerEnterLeaveSource::GetEventSource()->Notify({ a_event.ref.get(), a_event.triggerRef.get(), false });
		return _ProcessEvent(a_this, a_event, a_source);
	}

	void Install() noexcept
	{
		auto vtable = REL::Relocation<std::uintptr_t>{ VTables::BasicEventHandler_TESTriggerLeaveEvent };
		_ProcessEvent = vtable.write_vfunc(0x1, ProcessEvent);
	}
}
