#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class ActorDeathHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::TESDeathEvent>
	{
	public:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "ActorDeathArgs">;

	public:
		ActorDeathHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedSources,
			const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
			const std::vector<const RE::BSScript::Variable*>& a_includedTargets,
			const std::vector<const RE::BSScript::Variable*>& a_excludedTargets);

		~ActorDeathHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::TESDeathEvent& a_event, RE::BSTEventSource<RE::TESDeathEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _sourceFilter;
		const VarFilter _targetFilter;
	};
}
