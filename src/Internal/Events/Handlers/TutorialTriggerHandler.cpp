#include "Internal/Events/Handlers/TutorialTriggerHandler.hpp"

namespace Internal::Events
{
	TutorialTriggerHandler::TutorialTriggerHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<RE::BSFixedString>& a_includedEventNames,
		const std::vector<RE::BSFixedString>& a_excludedEventNames) :
		IEventHandler(a_receiver),
		_includedEventNames{ a_includedEventNames.begin(), a_includedEventNames.end() },
		_excludedEventNames{ a_excludedEventNames.begin(), a_excludedEventNames.end() }
	{
		Register();
	}

	TutorialTriggerHandler::~TutorialTriggerHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl TutorialTriggerHandler::ProcessEvent(const RE::TutorialEvent& a_event, RE::BSTEventSource<RE::TutorialEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		if (!VarFilter::FilterByStrings(a_event.eventName, _includedEventNames, _excludedEventNames)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("EventName"sv, a_event.eventName);
		args.insert("SentMessage"sv, a_event.assocMsg);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void TutorialTriggerHandler::Register()
	{
		RE::UI::GetSingleton()->RegisterSink(this);
	}

	void TutorialTriggerHandler::Unregister()
	{
		RE::UI::GetSingleton()->UnregisterSink(this);
	}
}