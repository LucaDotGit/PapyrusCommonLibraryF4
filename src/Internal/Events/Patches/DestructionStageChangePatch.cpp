#include "Internal/Events/Patches/DestructionStageChangePatch.hpp"

#include "Internal/Events/Patches/VTables.hpp"
#include "Internal/Events/Sources/DestructionStageChangeSource.hpp"

namespace Internal::Events::DestructionStageChangePatch
{
	static auto _ProcessEvent = REL::Relocation<decltype(&RE::BSTEventSink<RE::TESDestructionStageChangedEvent>::ProcessEvent)>();

	static RE::BSEventNotifyControl ProcessEvent(RE::BSTEventSink<RE::TESDestructionStageChangedEvent>* a_this,
		const RE::TESDestructionStageChangedEvent& a_event, RE::BSTEventSource<RE::TESDestructionStageChangedEvent>* a_source)
	{
		DestructionStageChangeSource::GetEventSource()->Notify({ a_event.ref.get(), a_event.oldStage, a_event.newStage });
		return _ProcessEvent(a_this, a_event, a_source);
	}

	void Install() noexcept
	{
		auto vtable = REL::Relocation<std::uintptr_t>{ VTables::BasicEventHandler_TESDestructionStageChangedEvent };
		_ProcessEvent = vtable.write_vfunc(0x1, ProcessEvent);
	}
}
