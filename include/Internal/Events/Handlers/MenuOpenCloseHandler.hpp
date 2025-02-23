#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class MenuOpenCloseHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::MenuOpenCloseEvent>
	{
	public:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "MenuOpenCloseArgs">;

	public:
		MenuOpenCloseHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<RE::BSFixedString>& a_includedMenuNames,
			const std::vector<RE::BSFixedString>& a_excludedMenuNames);

		~MenuOpenCloseHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent& a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const Types::unordered_string_set<RE::BSFixedString> _includedMenuNames;
		const Types::unordered_string_set<RE::BSFixedString> _excludedMenuNames;
	};
}
