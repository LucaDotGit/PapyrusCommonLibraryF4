#include "Internal/Events/Handlers/PerkPointIncreaseHandler.hpp"

namespace Internal::Events
{
	PerkPointIncreaseHandler::PerkPointIncreaseHandler(const ScriptReceivers::ScriptReceiver& a_receiver) :
		IEventHandler(a_receiver)
	{
		Register();
	}

	PerkPointIncreaseHandler::~PerkPointIncreaseHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl PerkPointIncreaseHandler::ProcessEvent(const PerkPointIncreaseEvent& a_event, RE::BSTEventSource<PerkPointIncreaseEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("Amount"sv, a_event.amount);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void PerkPointIncreaseHandler::Register()
	{
		PerkPointIncreaseSource::GetEventSource()->RegisterSink(this);
	}

	void PerkPointIncreaseHandler::Unregister()
	{
		PerkPointIncreaseSource::GetEventSource()->UnregisterSink(this);
	}
}
