#include "Internal/Events/Patches/TriggerEnterPatch.hpp"

#include "Internal/Events/Patches/VTables.hpp"
#include "Internal/Events/Sources/TriggerEnterLeaveSource.hpp"

namespace Internal::Events::TriggerEnterPatch
{
	static auto _ProcessEvent = REL::Relocation<decltype(&RE::BSTEventSink<RE::TESTriggerEnterEvent>::ProcessEvent)>();

	static RE::BSEventNotifyControl ProcessEvent(RE::BSTEventSink<RE::TESTriggerEnterEvent>* a_this,
		const RE::TESTriggerEnterEvent& a_event, RE::BSTEventSource<RE::TESTriggerEnterEvent>* a_source)
	{
		TriggerEnterLeaveSource::GetEventSource()->Notify({ a_event.ref.get(), a_event.triggerRef.get(), true });
		return _ProcessEvent(a_this, a_event, a_source);
	}

	void Install() noexcept
	{
		auto vtable = REL::Relocation<std::uintptr_t>{ VTables::BasicEventHandler_TESTriggerEnterEvent };
		_ProcessEvent = vtable.write_vfunc(0x1, ProcessEvent);
	}
}
