#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/HUDColorUpdateSource.hpp"

namespace Internal::Events
{
	class HUDColorUpdateHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<HUDColorUpdateEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "HUDColorUpdateArgs">;

	public:
		HUDColorUpdateHandler(const ScriptReceivers::ScriptReceiver& a_receiver);
		~HUDColorUpdateHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const HUDColorUpdateEvent& a_event, RE::BSTEventSource<HUDColorUpdateEvent>*) override;

		void Register() override;
		void Unregister() override;
	};
}
