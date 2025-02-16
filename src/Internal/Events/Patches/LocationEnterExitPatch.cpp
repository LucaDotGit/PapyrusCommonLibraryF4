#include "Internal/Events/Patches/LocationEnterExitPatch.hpp"

#include "Internal/Events/Patches/VTables.hpp"
#include "Internal/Events/Sources/LocationEnterExitSource.hpp"

namespace Internal::Events::LocationEnterExitPatch
{
	static auto _ProcessEvent = REL::Relocation<decltype(&RE::BSTEventSink<RE::TESActorLocationChangeEvent>::ProcessEvent)>();

	static RE::BSEventNotifyControl ProcessEvent(RE::BSTEventSink<RE::TESActorLocationChangeEvent>* a_this,
		const RE::TESActorLocationChangeEvent& a_event, RE::BSTEventSource<RE::TESActorLocationChangeEvent>* a_source)
	{
		const auto& ref = a_event.ref;
		if (ref) {
			LocationEnterExitSource::GetEventSource()->Notify({ ref->As<RE::Actor>(), a_event.oldLoc, a_event.newLoc });
		}

		return _ProcessEvent(a_this, a_event, a_source);
	}

	void Install() noexcept
	{
		auto vtable = REL::Relocation<std::uintptr_t>{ VTables::BasicEventHandler_TESActorLocationChangeEvent };
		_ProcessEvent = vtable.write_vfunc(0x1, ProcessEvent);
	}
}
