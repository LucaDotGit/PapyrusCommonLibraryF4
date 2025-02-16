#include "Internal/Events/Handlers/ActorDeathHandler.hpp"

namespace Internal::Events
{
	ActorDeathHandler::ActorDeathHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedSources,
		const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
		const std::vector<const RE::BSScript::Variable*>& a_includedTargets,
		const std::vector<const RE::BSScript::Variable*>& a_excludedTargets) :
		IEventHandler(a_receiver),
		_sourceFilter{ a_includedSources, a_excludedSources },
		_targetFilter{ a_includedTargets, a_excludedTargets }
	{
		Register();
	}

	ActorDeathHandler::~ActorDeathHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl ActorDeathHandler::ProcessEvent(const RE::TESDeathEvent& a_event, RE::BSTEventSource<RE::TESDeathEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* sourceActor = a_event.actorKiller ? a_event.actorKiller.get()->As<RE::Actor>() : nullptr;
		const auto* targetActor = a_event.actorDying ? a_event.actorDying.get()->As<RE::Actor>() : nullptr;

		if (!_sourceFilter.Filter(sourceActor) ||
			!_targetFilter.Filter(targetActor)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* source = sourceActor ? sourceActor->GetActorBase() : nullptr;
		const auto* target = targetActor ? targetActor->GetActorBase() : nullptr;

		auto args = EventArgs();
		args.insert("SourceActor"sv, sourceActor);
		args.insert("TargetActor"sv, targetActor);
		args.insert("Source"sv, source);
		args.insert("Target"sv, target);
		args.insert("IsDead"sv, !a_event.dying);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void ActorDeathHandler::Register()
	{
		RE::TESDeathEvent::GetEventSource()->RegisterSink(this);
	}

	void ActorDeathHandler::Unregister()
	{
		RE::TESDeathEvent::GetEventSource()->UnregisterSink(this);
	}
}
