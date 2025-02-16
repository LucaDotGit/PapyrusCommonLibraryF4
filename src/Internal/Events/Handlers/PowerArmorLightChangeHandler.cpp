#include "Internal/Events/Handlers/PowerArmorLightChangeHandler.hpp"

namespace Internal::Events
{
	PowerArmorLightChangeHandler::PowerArmorLightChangeHandler(const ScriptReceivers::ScriptReceiver& a_receiver) :
		IEventHandler(a_receiver)
	{
		Register();
	}

	PowerArmorLightChangeHandler::~PowerArmorLightChangeHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl PowerArmorLightChangeHandler::ProcessEvent(const RE::PowerArmorLightData& a_event, RE::BSTEventSource<RE::PowerArmorLightData>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("IsOn"sv, a_event.lightOn);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void PowerArmorLightChangeHandler::Register()
	{
		RE::PowerArmorLightData::GetEventSource()->RegisterSink(this);
	}

	void PowerArmorLightChangeHandler::Unregister()
	{
		RE::PowerArmorLightData::GetEventSource()->UnregisterSink(this);
	}
}
