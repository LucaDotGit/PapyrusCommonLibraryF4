#include "Internal/Events/Handlers/ObjectOpenCloseHandler.hpp"

namespace Internal::Events
{
	ObjectOpenCloseHandler::ObjectOpenCloseHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
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

	ObjectOpenCloseHandler::~ObjectOpenCloseHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl ObjectOpenCloseHandler::ProcessEvent(const ObjectOpenCloseEvent& a_event, RE::BSTEventSource<ObjectOpenCloseEvent>*)
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

		const auto* source = sourceRef ? sourceRef->GetBaseObject() : nullptr;
		const auto* target = targetRef ? targetRef->GetBaseObject() : nullptr;

		auto args = EventArgs();
		args.insert("SourceRef"sv, sourceRef);
		args.insert("Source"sv, source);
		args.insert("TargetRef"sv, targetRef);
		args.insert("Target"sv, target);
		args.insert("IsOpened"sv, a_event.isOpened);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void ObjectOpenCloseHandler::Register()
	{
		ObjectOpenCloseSource::GetEventSource()->RegisterSink(this);
	}

	void ObjectOpenCloseHandler::Unregister()
	{
		ObjectOpenCloseSource::GetEventSource()->UnregisterSink(this);
	}
}
