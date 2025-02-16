#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class MagicEffectApplyHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::TESMagicEffectApplyEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "MagicEffectApplyArgs">;

	public:
		MagicEffectApplyHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedSources,
			const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
			const std::vector<const RE::BSScript::Variable*>& a_includedTargets,
			const std::vector<const RE::BSScript::Variable*>& a_excludedTargets,
			const std::vector<const RE::BSScript::Variable*>& a_includedEffects,
			const std::vector<const RE::BSScript::Variable*>& a_excludedEffects);

		~MagicEffectApplyHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::TESMagicEffectApplyEvent& a_event, RE::BSTEventSource<RE::TESMagicEffectApplyEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _sourceFilter;
		const VarFilter _targetFilter;
		const VarFilter _effectFilter;
	};
}
