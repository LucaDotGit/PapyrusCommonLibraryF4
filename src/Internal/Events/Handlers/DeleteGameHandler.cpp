#include "Internal/Events/Handlers/DeleteGameHandler.hpp"

namespace Internal::Events
{
	DeleteGameHandler::DeleteGameHandler(const ScriptReceivers::ScriptReceiver& a_receiver) :
		IEventHandler(a_receiver)
	{
		Register();
	}

	DeleteGameHandler::~DeleteGameHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl DeleteGameHandler::ProcessEvent(const DeleteGameEvent& a_event, RE::BSTEventSource<DeleteGameEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("SaveName"sv, a_event.saveName);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void DeleteGameHandler::Register()
	{
		DeleteGameSource::GetEventSource()->RegisterSink(this);
	}

	void DeleteGameHandler::Unregister()
	{
		DeleteGameSource::GetEventSource()->UnregisterSink(this);
	}
}
