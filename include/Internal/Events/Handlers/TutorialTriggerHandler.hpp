#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class TutorialTriggerHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::TutorialEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "TutorialTriggerArgs">;

	public:
		TutorialTriggerHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<RE::BSFixedString>& a_includedEventNames,
			const std::vector<RE::BSFixedString>& a_excludedEventNames);

		~TutorialTriggerHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::TutorialEvent& a_event, RE::BSTEventSource<RE::TutorialEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const Types::unordered_string_set<RE::BSFixedString> _includedEventNames;
		const Types::unordered_string_set<RE::BSFixedString> _excludedEventNames;
	};
}