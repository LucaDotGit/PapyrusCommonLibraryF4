#include "Internal/Events/Handlers/LimbCrippleHandler.hpp"

namespace Internal::Events
{
	LimbCrippleHandler::LimbCrippleHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedSources,
		const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
		const std::vector<const RE::BSScript::Variable*>& a_includedLimbs,
		const std::vector<const RE::BSScript::Variable*>& a_excludedLimbs) :
		IEventHandler(a_receiver),
		_sourceFilter{ a_includedSources, a_excludedSources },
		_limbFilter{ a_includedLimbs, a_excludedLimbs }
	{
		Register();
	}

	LimbCrippleHandler::~LimbCrippleHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl LimbCrippleHandler::ProcessEvent(const LimbCrippleEvent& a_event, RE::BSTEventSource<LimbCrippleEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* sourceActor = a_event.actor;
		const auto* source = sourceActor ? sourceActor->GetActorBase() : nullptr;

		if (!_sourceFilter.Filter(sourceActor) ||
			!_limbFilter.Filter(a_event.limb)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("SourceActor"sv, sourceActor);
		args.insert("Source"sv, source);
		args.insert("Limb"sv, a_event.limb);
		args.insert("IsCrippled"sv, a_event.isCrippled);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void LimbCrippleHandler::Register()
	{
		LimbCrippleSource::GetEventSource()->RegisterSink(this);
	}

	void LimbCrippleHandler::Unregister()
	{
		LimbCrippleSource::GetEventSource()->UnregisterSink(this);
	}
}
