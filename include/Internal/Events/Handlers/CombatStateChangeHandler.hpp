#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/CombatStateChangeSource.hpp"

namespace Internal::Events
{
	class CombatStateChangeHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<CombatStateChangeEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "CombatStateChangeArgs">;

	public:
		CombatStateChangeHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedSources,
			const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
			const std::vector<const RE::BSScript::Variable*>& a_includedTargets,
			const std::vector<const RE::BSScript::Variable*>& a_excludedTargets,
			const std::vector<RE::ACTOR_COMBAT_STATE>& a_includedStates,
			const std::vector<RE::ACTOR_COMBAT_STATE>& a_excludedStates);

		~CombatStateChangeHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const CombatStateChangeEvent& a_event, RE::BSTEventSource<CombatStateChangeEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _sourceFilter;
		const VarFilter _targetFilter;
		const std::unordered_set<RE::ACTOR_COMBAT_STATE> _includedStates;
		const std::unordered_set<RE::ACTOR_COMBAT_STATE> _excludedStates;
	};
}
