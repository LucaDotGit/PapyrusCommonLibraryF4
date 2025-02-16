#include "Internal/Events/Handlers/LifeStateChangeHandler.hpp"

namespace Internal::Events
{
	LifeStateChangeHandler::LifeStateChangeHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedSources,
		const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
		const std::vector<RE::ACTOR_LIFE_STATE> a_includedOldStates,
		const std::vector<RE::ACTOR_LIFE_STATE> a_excludedOldStates,
		const std::vector<RE::ACTOR_LIFE_STATE> a_includedNewStates,
		const std::vector<RE::ACTOR_LIFE_STATE> a_excludedNewStates) :
		IEventHandler(a_receiver),
		_sourceFilter{ a_includedSources, a_excludedSources },
		_includedOldStates{ a_includedOldStates.begin(), a_includedOldStates.end() },
		_excludedOldStates{ a_excludedOldStates.begin(), a_excludedOldStates.end() },
		_includedNewStates{ a_includedNewStates.begin(), a_includedNewStates.end() },
		_excludedNewStates{ a_excludedNewStates.begin(), a_excludedNewStates.end() }
	{
		Register();
	}

	LifeStateChangeHandler::~LifeStateChangeHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl LifeStateChangeHandler::ProcessEvent(const LifeStateChangeEvent& a_event, RE::BSTEventSource<LifeStateChangeEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* sourceActor = a_event.actor ? a_event.actor : nullptr;
		const auto* source = sourceActor ? sourceActor->GetActorBase() : nullptr;

		if (!VarFilter::FilterByEnums(a_event.oldState, _includedOldStates, _excludedOldStates) ||
			!VarFilter::FilterByEnums(a_event.newState, _includedNewStates, _excludedNewStates) ||
			!_sourceFilter.Filter(sourceActor)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("SourceActor"sv, sourceActor);
		args.insert("Source"sv, source);
		args.insert("OldState"sv, a_event.oldState);
		args.insert("NewState"sv, a_event.newState);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void LifeStateChangeHandler::Register()
	{
		LifeStateChangeSource::GetEventSource()->RegisterSink(this);
	}

	void LifeStateChangeHandler::Unregister()
	{
		LifeStateChangeSource::GetEventSource()->UnregisterSink(this);
	}
}
