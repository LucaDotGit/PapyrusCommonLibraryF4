#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/UserEventSource.hpp"

namespace Internal::Events
{
	class UserEventHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<UserEvent>
	{
	public:
		UserEventHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			RE::BSFixedString a_eventName);

		~UserEventHandler() override;

	public:
		[[nodiscard]] const RE::BSFixedString& GetEventName() const noexcept;

	private:
		RE::BSEventNotifyControl ProcessEvent(const UserEvent& a_event, RE::BSTEventSource<UserEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const RE::BSFixedString _eventName;
	};
}
