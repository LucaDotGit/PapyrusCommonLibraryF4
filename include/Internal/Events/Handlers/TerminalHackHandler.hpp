#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class TerminalHackHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::TerminalHacked::Event>
	{
	public:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "TerminalHackArgs">;

	public:
		TerminalHackHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
			const std::vector<const RE::BSScript::Variable*>& a_excludedObjects);

		~TerminalHackHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::TerminalHacked::Event& a_event, RE::BSTEventSource<RE::TerminalHacked::Event>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _filter;
	};
}
