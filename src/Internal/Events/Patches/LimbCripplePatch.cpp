#include "Internal/Events/Patches/LimbCripplePatch.hpp"

#include "Internal/Events/Patches/VTables.hpp"
#include "Internal/Events/Sources/LimbCrippleSource.hpp"

namespace Internal::Events::LimbCripplePatch
{
	static auto _ProcessEvent = REL::Relocation<decltype(&RE::BSTEventSink<RE::TESLimbCrippleEvent>::ProcessEvent)>();

	static RE::BSEventNotifyControl ProcessEvent(RE::BSTEventSink<RE::TESLimbCrippleEvent>* a_this,
		const RE::TESLimbCrippleEvent& a_event, RE::BSTEventSource<RE::TESLimbCrippleEvent>* a_source)
	{
		const auto& ref = a_event.actor;
		if (ref) {
			LimbCrippleSource::GetEventSource()->Notify({ ref->As<RE::Actor>(), a_event.limb, a_event.crippled });
		}

		return _ProcessEvent(a_this, a_event, a_source);
	}

	void Install() noexcept
	{
		auto vtable = REL::Relocation<std::uintptr_t>{ VTables::BasicEventHandler_TESLimbCrippleEvent };
		_ProcessEvent = vtable.write_vfunc(0x1, ProcessEvent);
	}
}
