#include "Internal/Events/Patches/HUDColorUpdatePatch.hpp"

#include "Internal/Bethesda/IniSettings.hpp"
#include "Internal/Events/Sources/HUDColorUpdateSource.hpp"

namespace Internal::Events::HUDColorUpdatePatch
{
	static auto _ProcessEvent = REL::Relocation<decltype(&RE::BSTEventSink<RE::ApplyColorUpdateEvent>::ProcessEvent)>();

	static RE::BSEventNotifyControl ProcessEvent(RE::BSTEventSink<RE::ApplyColorUpdateEvent>* a_this,
		const RE::ApplyColorUpdateEvent& a_event, RE::BSTEventSource<RE::ApplyColorUpdateEvent>* a_source)
	{
		const auto lock = std::shared_lock{ IniSettings::GetMutex() };

		const auto red = static_cast<std::uint8_t>(IniSettings::GetSetting("Interface"sv, "iHUDColorR"sv)->GetInt());
		const auto green = static_cast<std::uint8_t>(IniSettings::GetSetting("Interface"sv, "iHUDColorG"sv)->GetInt());
		const auto blue = static_cast<std::uint8_t>(IniSettings::GetSetting("Interface"sv, "iHUDColorB"sv)->GetInt());

		HUDColorUpdateSource::GetEventSource()->Notify({ red, green, blue });
		return _ProcessEvent(a_this, a_event, a_source);
	}

	void Install() noexcept
	{
		auto vtable = REL::Relocation<std::uintptr_t>{ RE::GameUIModel::VTABLE[0] };
		_ProcessEvent = vtable.write_vfunc(0x1, ProcessEvent);
	}
}
