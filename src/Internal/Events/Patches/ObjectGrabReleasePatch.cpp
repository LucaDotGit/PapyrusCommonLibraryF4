#include "Internal/Events/Patches/ObjectGrabReleasePatch.hpp"

#include "Internal/Events/Patches/VTables.hpp"
#include "Internal/Events/Sources/ObjectGrabReleaseSource.hpp"

namespace Internal::Events::ObjectGrabReleasePatch
{
	static auto _ProcessEvent = REL::Relocation<decltype(&RE::BSTEventSink<RE::TESGrabReleaseEvent>::ProcessEvent)>();

	static RE::BSEventNotifyControl ProcessEvent(RE::BSTEventSink<RE::TESGrabReleaseEvent>* a_this,
		const RE::TESGrabReleaseEvent& a_event, RE::BSTEventSource<RE::TESGrabReleaseEvent>* a_source)
	{
		ObjectGrabReleaseSource::GetEventSource()->Notify({ a_event.ref.get(), a_event.grabbed });
		return _ProcessEvent(a_this, a_event, a_source);
	}

	void Install() noexcept
	{
		auto vtable = REL::Relocation<std::uintptr_t>{ VTables::BasicEventHandler_TESGrabReleaseEvent };
		_ProcessEvent = vtable.write_vfunc(0x1, ProcessEvent);
	}
}
