#include "Internal/Events/Handlers/HUDColorUpdateHandler.hpp"

namespace Internal::Events
{
	HUDColorUpdateHandler::HUDColorUpdateHandler(const ScriptReceivers::ScriptReceiver& a_receiver) :
		IEventHandler(a_receiver)
	{
		Register();
	}

	HUDColorUpdateHandler::~HUDColorUpdateHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl HUDColorUpdateHandler::ProcessEvent(const HUDColorUpdateEvent& a_event, RE::BSTEventSource<HUDColorUpdateEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto color = Colors::MakeColor(a_event.red, a_event.green, a_event.blue);
		auto args = EventArgs();

		args.insert("Color"sv, std::move(color));
		DispatchCall(std::move(args));

		return RE::BSEventNotifyControl::kContinue;
	}

	void HUDColorUpdateHandler::Register()
	{
		HUDColorUpdateSource::GetEventSource()->RegisterSink(this);
	}

	void HUDColorUpdateHandler::Unregister()
	{
		HUDColorUpdateSource::GetEventSource()->UnregisterSink(this);
	}
}
