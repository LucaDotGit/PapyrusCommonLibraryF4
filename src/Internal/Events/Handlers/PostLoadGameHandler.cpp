#include "Internal/Events/Handlers/PostLoadGameHandler.hpp"

namespace Internal::Events
{
	PostLoadGameHandler::PostLoadGameHandler(const ScriptReceivers::ScriptReceiver& a_receiver) :
		IEventHandler(a_receiver)
	{
		Register();
	}

	PostLoadGameHandler::~PostLoadGameHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl PostLoadGameHandler::ProcessEvent(const PostLoadGameEvent& a_event, RE::BSTEventSource<PostLoadGameEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("IsSucceeded"sv, a_event.isSucceeded);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void PostLoadGameHandler::Register()
	{
		PostLoadGameSource::GetEventSource()->RegisterSink(this);
	}

	void PostLoadGameHandler::Unregister()
	{
		PostLoadGameSource::GetEventSource()->UnregisterSink(this);
	}
}
