#include "Internal/Events/Patches/ObjectOpenClosePatch.hpp"

#include "Internal/Events/Patches/VTables.hpp"
#include "Internal/Events/Sources/ObjectOpenCloseSource.hpp"

namespace Internal::Events::ObjectOpenClosePatch
{
	static auto _ProcessEvent = REL::Relocation<decltype(&RE::BSTEventSink<RE::TESOpenCloseEvent>::ProcessEvent)>();

	static RE::BSEventNotifyControl ProcessEvent(RE::BSTEventSink<RE::TESOpenCloseEvent>* a_this,
		const RE::TESOpenCloseEvent& a_event, RE::BSTEventSource<RE::TESOpenCloseEvent>* a_source)
	{
		ObjectOpenCloseSource::GetEventSource()->Notify({ a_event.activeRef.get(), a_event.ref.get(), a_event.opened });
		return _ProcessEvent(a_this, a_event, a_source);
	}

	void Install() noexcept
	{
		auto vtable = REL::Relocation<std::uintptr_t>{ VTables::BasicEventHandler_TESOpenCloseEvent };
		_ProcessEvent = vtable.write_vfunc(0x1, ProcessEvent);
	}
}
