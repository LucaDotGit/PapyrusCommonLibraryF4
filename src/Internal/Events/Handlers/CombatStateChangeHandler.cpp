#include "Internal/Events/Handlers/CombatStateChangeHandler.hpp"

namespace Internal::Events
{
	CombatStateChangeHandler::CombatStateChangeHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedSources,
		const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
		const std::vector<const RE::BSScript::Variable*>& a_includedTargets,
		const std::vector<const RE::BSScript::Variable*>& a_excludedTargets,
		const std::vector<RE::ACTOR_COMBAT_STATE>& a_includedStates,
		const std::vector<RE::ACTOR_COMBAT_STATE>& a_excludedStates) :
		IEventHandler(a_receiver),
		_sourceFilter{ a_includedSources, a_excludedSources },
		_targetFilter{ a_includedTargets, a_excludedTargets },
		_includedStates(a_includedStates.begin(), a_includedStates.end()),
		_excludedStates(a_excludedStates.begin(), a_excludedStates.end())
	{
		Register();
	}

	CombatStateChangeHandler::~CombatStateChangeHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl CombatStateChangeHandler::ProcessEvent(const CombatStateChangeEvent& a_event, RE::BSTEventSource<CombatStateChangeEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* sourceActor = a_event.sourceActor;
		const auto* targetActor = a_event.targetActor;

		const auto setState = a_event.setState;

		if (!VarFilter::FilterByEnums(setState, _includedStates, _excludedStates) ||
			!_sourceFilter.Filter(sourceActor) ||
			!_targetFilter.Filter(targetActor)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* source = sourceActor ? sourceActor->GetActorBase() : nullptr;
		const auto* target = targetActor ? targetActor->GetActorBase() : nullptr;

		auto args = EventArgs();
		args.insert("SourceActor"sv, sourceActor);
		args.insert("targetActor"sv, targetActor);
		args.insert("Source"sv, source);
		args.insert("Target"sv, target);
		args.insert("SetState"sv, setState);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void CombatStateChangeHandler::Register()
	{
		CombatStateChangeSource::GetEventSource()->RegisterSink(this);
	}

	void CombatStateChangeHandler::Unregister()
	{
		CombatStateChangeSource::GetEventSource()->UnregisterSink(this);
	}
}
