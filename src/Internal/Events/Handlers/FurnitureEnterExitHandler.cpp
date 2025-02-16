#include "Internal/Events/Handlers/FurnitureEnterExitHandler.hpp"

namespace Internal::Events
{
	FurnitureEnterExitHandler::FurnitureEnterExitHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
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

	FurnitureEnterExitHandler::~FurnitureEnterExitHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl FurnitureEnterExitHandler::ProcessEvent(const RE::TESFurnitureEvent& a_event, RE::BSTEventSource<RE::TESFurnitureEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* sourceActor = a_event.actor ? a_event.actor->As<RE::Actor>() : nullptr;
		const auto* targetRef = a_event.targetFurniture ? a_event.targetFurniture.get() : nullptr;

		if (!_sourceFilter.Filter(sourceActor) ||
			!_targetFilter.Filter(targetRef)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* source = sourceActor ? sourceActor->GetActorBase() : nullptr;
		const auto* target = targetRef ? targetRef->GetBaseObject()->As<RE::TESFurniture>() : nullptr;

		const auto isEntered = a_event.type == RE::TESFurnitureEvent::FurnitureEventType::kEnter;

		auto args = EventArgs();
		args.insert("SourceActor"sv, sourceActor);
		args.insert("TargetRef"sv, targetRef);
		args.insert("Source"sv, source);
		args.insert("Target"sv, target);
		args.insert("IsEntered"sv, isEntered);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void FurnitureEnterExitHandler::Register()
	{
		RE::TESFurnitureEvent::GetEventSource()->RegisterSink(this);
	}

	void FurnitureEnterExitHandler::Unregister()
	{
		RE::TESFurnitureEvent::GetEventSource()->UnregisterSink(this);
	}
}
