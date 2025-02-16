#include "Internal/Events/Handlers/TriggerEnterLeaveHandler.hpp"

namespace Internal::Events
{
	TriggerEnterLeaveHandler::TriggerEnterLeaveHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
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

	TriggerEnterLeaveHandler::~TriggerEnterLeaveHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl TriggerEnterLeaveHandler::ProcessEvent(const TriggerEnterLeaveEvent& a_event, RE::BSTEventSource<TriggerEnterLeaveEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* sourceRef = a_event.sourceRef;
		const auto* targetRef = a_event.targetRef;

		if (!_sourceFilter.Filter(sourceRef) ||
			!_targetFilter.Filter(targetRef)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto source = sourceRef ? sourceRef->GetBaseObject() : nullptr;
		const auto target = targetRef ? targetRef->GetBaseObject()->As<RE::TESObjectACTI>() : nullptr;

		auto args = EventArgs();
		args.insert("SourceRef"sv, sourceRef);
		args.insert("TargetRef"sv, targetRef);
		args.insert("Source"sv, source);
		args.insert("Target"sv, target);
		args.insert("IsEntered"sv, a_event.isEntered);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void TriggerEnterLeaveHandler::Register()
	{
		TriggerEnterLeaveSource::GetEventSource()->RegisterSink(this);
	}

	void TriggerEnterLeaveHandler::Unregister()
	{
		TriggerEnterLeaveSource::GetEventSource()->UnregisterSink(this);
	}
}
