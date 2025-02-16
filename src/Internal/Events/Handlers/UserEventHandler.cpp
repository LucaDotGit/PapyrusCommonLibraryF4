#include "Internal/Events/Handlers/UserEventHandler.hpp"

namespace Internal::Events
{
	UserEventHandler::UserEventHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		RE::BSFixedString a_eventName) :
		IEventHandler(a_receiver),
		_eventName(std::move(a_eventName))
	{
		Register();
	}

	UserEventHandler::~UserEventHandler()
	{
		Unregister();
	}

	const RE::BSFixedString& UserEventHandler::GetEventName() const noexcept
	{
		return _eventName;
	}

	RE::BSEventNotifyControl UserEventHandler::ProcessEvent(const UserEvent& a_event, RE::BSTEventSource<UserEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		if (a_event.eventName == _eventName) {
			DispatchAppliedCall(a_event.args);
		}

		return RE::BSEventNotifyControl::kContinue;
	}

	void UserEventHandler::Register()
	{
		UserEventSource::GetEventSource()->RegisterSink(this);
	}

	void UserEventHandler::Unregister()
	{
		UserEventSource::GetEventSource()->UnregisterSink(this);
	}
}
