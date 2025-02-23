#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class CellEnterExitHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::BGSActorCellEvent>
	{
	public:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "CellEnterExitArgs">;

	public:
		CellEnterExitHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
			const std::vector<const RE::BSScript::Variable*>& a_excludedObjects);

		~CellEnterExitHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::BGSActorCellEvent& a_event, RE::BSTEventSource<RE::BGSActorCellEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _filter;
	};
}
