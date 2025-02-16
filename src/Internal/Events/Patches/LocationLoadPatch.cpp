#include "Internal/Events/Patches/LocationLoadPatch.hpp"

#include "Internal/Events/Patches/VTables.hpp"
#include "Internal/Events/Sources/LocationLoadSource.hpp"

namespace Internal::Events::LocationLoadPatch
{
	static auto _ProcessEvent = REL::Relocation<decltype(&RE::BSTEventSink<RE::BGSLocationLoadedEvent>::ProcessEvent)>();

	static RE::BSEventNotifyControl ProcessEvent(RE::BSTEventSink<RE::BGSLocationLoadedEvent>* a_this,
		const RE::BGSLocationLoadedEvent& a_event, RE::BSTEventSource<RE::BGSLocationLoadedEvent>* a_source)
	{
		LocationLoadSource::GetEventSource()->Notify({ a_event.location });
		return _ProcessEvent(a_this, a_event, a_source);
	}

	void Install() noexcept
	{
		auto vtable = REL::Relocation<std::uintptr_t>{ VTables::BasicEventHandler_BGSLocationLoadedEvent };
		_ProcessEvent = vtable.write_vfunc(0x1, ProcessEvent);
	}
}
