#include "Internal/Events/Handlers/MagicEffectApplyHandler.hpp"

namespace Internal::Events
{
	MagicEffectApplyHandler::MagicEffectApplyHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedSources,
		const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
		const std::vector<const RE::BSScript::Variable*>& a_includedTargets,
		const std::vector<const RE::BSScript::Variable*>& a_excludedTargets,
		const std::vector<const RE::BSScript::Variable*>& a_includedEffects,
		const std::vector<const RE::BSScript::Variable*>& a_excludedEffects) :
		IEventHandler(a_receiver),
		_sourceFilter{ a_includedSources, a_excludedSources },
		_targetFilter{ a_includedTargets, a_excludedTargets },
		_effectFilter{ a_includedEffects, a_excludedEffects }
	{
		Register();
	}

	MagicEffectApplyHandler::~MagicEffectApplyHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl MagicEffectApplyHandler::ProcessEvent(const RE::TESMagicEffectApplyEvent& a_event, RE::BSTEventSource<RE::TESMagicEffectApplyEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* sourceRef = a_event.caster ? a_event.caster.get() : nullptr;
		const auto* targetRef = a_event.target ? a_event.target.get() : nullptr;

		const auto* effect = RE::TESForm::GetFormByID<RE::EffectSetting>(a_event.magicEffectFormID);

		if (!_sourceFilter.Filter(sourceRef) ||
			!_targetFilter.Filter(targetRef) ||
			!_effectFilter.Filter(effect)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* source = sourceRef ? sourceRef->GetBaseObject() : nullptr;
		const auto* target = targetRef ? targetRef->GetBaseObject() : nullptr;

		auto args = EventArgs();
		args.insert("SourceRef"sv, sourceRef);
		args.insert("TargetRef"sv, targetRef);
		args.insert("Source"sv, source);
		args.insert("Target"sv, target);
		args.insert("Effect"sv, effect);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void MagicEffectApplyHandler::Register()
	{
		RE::TESMagicEffectApplyEvent::GetEventSource()->RegisterSink(this);
	}

	void MagicEffectApplyHandler::Unregister()
	{
		RE::TESMagicEffectApplyEvent::GetEventSource()->UnregisterSink(this);
	}
}
