#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class MenuModeEnterExitHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::MenuModeChangeEvent>
	{
	public:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "MenuModeEnterExitArgs">;

	public:
		MenuModeEnterExitHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<RE::BSFixedString>& a_includedMenuNames,
			const std::vector<RE::BSFixedString>& a_excludedMenuNames);

		~MenuModeEnterExitHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::MenuModeChangeEvent& a_event, RE::BSTEventSource<RE::MenuModeChangeEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const Types::unordered_string_set<RE::BSFixedString> _includedMenuNames;
		const Types::unordered_string_set<RE::BSFixedString> _excludedMenuNames;
	};
}
