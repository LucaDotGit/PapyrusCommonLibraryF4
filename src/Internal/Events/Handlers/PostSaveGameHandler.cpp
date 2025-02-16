#include "Internal/Events/Handlers/PostSaveGameHandler.hpp"

namespace Internal::Events
{
	PostSaveGameHandler::PostSaveGameHandler(const ScriptReceivers::ScriptReceiver& a_receiver) :
		IEventHandler(a_receiver)
	{
		Register();
	}

	PostSaveGameHandler::~PostSaveGameHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl PostSaveGameHandler::ProcessEvent(const PostSaveGameEvent& a_event, RE::BSTEventSource<PostSaveGameEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("SaveName"sv, a_event.saveName);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void PostSaveGameHandler::Register()
	{
		PostSaveGameSource::GetEventSource()->RegisterSink(this);
	}

	void PostSaveGameHandler::Unregister()
	{
		PostSaveGameSource::GetEventSource()->UnregisterSink(this);
	}
}
