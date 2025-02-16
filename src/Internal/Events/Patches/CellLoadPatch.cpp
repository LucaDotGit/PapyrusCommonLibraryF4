#include "Internal/Events/Patches/CellLoadPatch.hpp"

#include "Internal/Events/Patches/VTables.hpp"
#include "Internal/Events/Sources/CellLoadSource.hpp"

namespace Internal::Events::CellLoadPatch
{
	static auto _ProcessEvent = REL::Relocation<decltype(&RE::BSTEventSink<RE::TESCellFullyLoadedEvent>::ProcessEvent)>();

	static RE::BSEventNotifyControl ProcessEvent(RE::BSTEventSink<RE::TESCellFullyLoadedEvent>* a_this,
		const RE::TESCellFullyLoadedEvent& a_event, RE::BSTEventSource<RE::TESCellFullyLoadedEvent>* a_source)
	{
		CellLoadSource::GetEventSource()->Notify({ a_event.cell });
		return _ProcessEvent(a_this, a_event, a_source);
	}

	void Install() noexcept
	{
		auto vtable = REL::Relocation<std::uintptr_t>{ VTables::BasicEventHandler_TESCellFullyLoadedEvent };
		_ProcessEvent = vtable.write_vfunc(0x1, ProcessEvent);
	}
}
