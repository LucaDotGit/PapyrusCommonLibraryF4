#include "Internal/Events/Handlers/PipBoyLightChangeHandler.hpp"

namespace Internal::Events
{
	PipBoyLightChangeHandler::PipBoyLightChangeHandler(const ScriptReceivers::ScriptReceiver& a_receiver) :
		IEventHandler(a_receiver)
	{
		Register();
	}

	PipBoyLightChangeHandler::~PipBoyLightChangeHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl PipBoyLightChangeHandler::ProcessEvent(const RE::PipboyLightEvent& a_event, RE::BSTEventSource<RE::PipboyLightEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("IsOn"sv, a_event.optionalValue.value_or(false));

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void PipBoyLightChangeHandler::Register()
	{
		RE::PipboyLightEvent::GetEventSource()->RegisterSink(this);
	}

	void PipBoyLightChangeHandler::Unregister()
	{
		RE::PipboyLightEvent::GetEventSource()->UnregisterSink(this);
	}
}
