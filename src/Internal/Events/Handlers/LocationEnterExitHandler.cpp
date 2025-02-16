#include "Internal/Events/Handlers/LocationEnterExitHandler.hpp"

namespace Internal::Events
{
	LocationEnterExitHandler::LocationEnterExitHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedSources,
		const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
		const std::vector<const RE::BSScript::Variable*>& a_includedOldLocations,
		const std::vector<const RE::BSScript::Variable*>& a_excludedOldLocations,
		const std::vector<const RE::BSScript::Variable*>& a_includedNewLocations,
		const std::vector<const RE::BSScript::Variable*>& a_excludedNewLocations) :
		IEventHandler(a_receiver),
		_sourceFilter{ a_includedSources, a_excludedSources },
		_oldLocationFilter{ a_includedOldLocations, a_excludedOldLocations },
		_newLocationFilter{ a_includedNewLocations, a_excludedNewLocations }
	{
		Register();
	}

	LocationEnterExitHandler::~LocationEnterExitHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl LocationEnterExitHandler::ProcessEvent(const LocationEnterExitEvent& a_event, RE::BSTEventSource<LocationEnterExitEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* sourceActor = a_event.actor;
		const auto* source = sourceActor ? sourceActor->GetActorBase() : nullptr;

		if (!_sourceFilter.Filter(sourceActor) ||
			!_oldLocationFilter.Filter(a_event.oldLocation) ||
			!_newLocationFilter.Filter(a_event.newLocation)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("SourceActor"sv, sourceActor);
		args.insert("Source"sv, source);
		args.insert("OldLocation"sv, a_event.oldLocation);
		args.insert("NewLocation"sv, a_event.newLocation);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void LocationEnterExitHandler::Register()
	{
		LocationEnterExitSource::GetEventSource()->RegisterSink(this);
	}

	void LocationEnterExitHandler::Unregister()
	{
		LocationEnterExitSource::GetEventSource()->UnregisterSink(this);
	}
}
