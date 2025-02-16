#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/LifeStateChangeSource.hpp"

namespace Internal::Events
{
	class LifeStateChangeHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<LifeStateChangeEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "LifeStateChangeArgs">;

	public:
		LifeStateChangeHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedSources,
			const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
			const std::vector<RE::ACTOR_LIFE_STATE> a_includedOldStates,
			const std::vector<RE::ACTOR_LIFE_STATE> a_excludedOldStates,
			const std::vector<RE::ACTOR_LIFE_STATE> a_includedNewStates,
			const std::vector<RE::ACTOR_LIFE_STATE> a_excludedNewStates);

		~LifeStateChangeHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const LifeStateChangeEvent& a_event, RE::BSTEventSource<LifeStateChangeEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _sourceFilter;
		const std::unordered_set<RE::ACTOR_LIFE_STATE> _includedOldStates;
		const std::unordered_set<RE::ACTOR_LIFE_STATE> _excludedOldStates;
		const std::unordered_set<RE::ACTOR_LIFE_STATE> _includedNewStates;
		const std::unordered_set<RE::ACTOR_LIFE_STATE> _excludedNewStates;
	};
}
