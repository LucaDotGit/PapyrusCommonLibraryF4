#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class PipBoyLightChangeHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::PipboyLightEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "PipBoyLightChangeArgs">;

	public:
		PipBoyLightChangeHandler(const ScriptReceivers::ScriptReceiver& a_receiver);
		~PipBoyLightChangeHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::PipboyLightEvent& a_event, RE::BSTEventSource<RE::PipboyLightEvent>*) override;

		void Register() override;
		void Unregister() override;
	};
}
