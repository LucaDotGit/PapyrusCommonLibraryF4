#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class PowerArmorLightChangeHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::PowerArmorLightData>
	{
	public:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "PowerArmorLightChangeArgs">;

	public:
		PowerArmorLightChangeHandler(const ScriptReceivers::ScriptReceiver& a_receiver);
		~PowerArmorLightChangeHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::PowerArmorLightData& a_event, RE::BSTEventSource<RE::PowerArmorLightData>*) override;

		void Register() override;
		void Unregister() override;
	};
}
