#include "Internal/Events/Handlers/PreSaveGameHandler.hpp"

namespace Internal::Events
{
	PreSaveGameHandler::PreSaveGameHandler(const ScriptReceivers::ScriptReceiver& a_receiver) :
		IEventHandler(a_receiver)
	{
		Register();
	}

	PreSaveGameHandler::~PreSaveGameHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl PreSaveGameHandler::ProcessEvent(const PreSaveGameEvent& a_event, RE::BSTEventSource<PreSaveGameEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("SaveName"sv, a_event.saveName);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void PreSaveGameHandler::Register()
	{
		PreSaveGameSource::GetEventSource()->RegisterSink(this);
	}

	void PreSaveGameHandler::Unregister()
	{
		PreSaveGameSource::GetEventSource()->UnregisterSink(this);
	}
}
