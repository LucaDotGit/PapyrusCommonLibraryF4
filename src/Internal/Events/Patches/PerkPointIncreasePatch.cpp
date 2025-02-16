#include "Internal/Events/Patches/PerkPointIncreasePatch.hpp"

#include "Internal/Events/Sources/PerkPointIncreaseSource.hpp"

namespace Internal::Events::PerkPointIncreasePatch
{
	static auto _ProcessEvent = REL::Relocation<decltype(&RE::BSTEventSink<RE::PerkPointIncreaseEvent>::ProcessEvent)>();

	static RE::BSEventNotifyControl ProcessEvent(RE::BSTEventSink<RE::PerkPointIncreaseEvent>* a_this,
		const RE::PerkPointIncreaseEvent& a_event, RE::BSTEventSource<RE::PerkPointIncreaseEvent>* a_source)
	{
		PerkPointIncreaseSource::GetEventSource()->Notify({ a_event.perkCount });
		return _ProcessEvent(a_this, a_event, a_source);
	}

	void Install() noexcept
	{
		auto vtable = REL::Relocation<std::uintptr_t>{ RE::PipboyPlayerInfoData::VTABLE[5] };
		_ProcessEvent = vtable.write_vfunc(0x1, ProcessEvent);
	}
}
