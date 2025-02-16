#include "Internal/Events/Handlers/ObjectActivateHandler.hpp"

namespace Internal::Events
{
	ObjectActivateHandler::ObjectActivateHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
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

	ObjectActivateHandler::~ObjectActivateHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl ObjectActivateHandler::ProcessEvent(const RE::TESActivateEvent& a_event, RE::BSTEventSource<RE::TESActivateEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* sourceRef = a_event.actionRef.get();
		const auto* targetRef = a_event.objectActivated.get();

		if (!_sourceFilter.Filter(sourceRef) ||
			!_targetFilter.Filter(targetRef)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto source = sourceRef ? sourceRef->GetBaseObject() : nullptr;
		const auto target = targetRef ? targetRef->GetBaseObject() : nullptr;

		auto args = EventArgs();
		args.insert("SourceRef"sv, sourceRef);
		args.insert("TargetRef"sv, targetRef);
		args.insert("Source"sv, source);
		args.insert("Target"sv, target);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void ObjectActivateHandler::Register()
	{
		RE::TESActivateEvent::GetEventSource()->RegisterSink(this);
	}

	void ObjectActivateHandler::Unregister()
	{
		RE::TESActivateEvent::GetEventSource()->UnregisterSink(this);
	}
}
