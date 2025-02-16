#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/PerkPointIncreaseSource.hpp"

namespace Internal::Events
{
	class PerkPointIncreaseHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<PerkPointIncreaseEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "PerkPointIncreaseArgs">;

	public:
		PerkPointIncreaseHandler(const ScriptReceivers::ScriptReceiver& a_receiver);
		~PerkPointIncreaseHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const PerkPointIncreaseEvent& a_event, RE::BSTEventSource<PerkPointIncreaseEvent>*) override;

		void Register() override;
		void Unregister() override;
	};
}
