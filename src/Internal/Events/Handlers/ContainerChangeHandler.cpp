#include "Internal/Events/Handlers/ContainerChangeHandler.hpp"

namespace Internal::Events
{
	ContainerChangeHandler::ContainerChangeHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedSources,
		const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
		const std::vector<const RE::BSScript::Variable*>& a_includedTargets,
		const std::vector<const RE::BSScript::Variable*>& a_excludedTargets,
		const std::vector<const RE::BSScript::Variable*>& a_includedItems,
		const std::vector<const RE::BSScript::Variable*>& a_excludedItems) :
		IEventHandler(a_receiver),
		_sourceFilter{ a_includedSources, a_excludedSources },
		_targetFilter{ a_includedTargets, a_excludedTargets },
		_itemFilter{ a_includedItems, a_excludedItems }
	{
		Register();
	}

	ContainerChangeHandler::~ContainerChangeHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl ContainerChangeHandler::ProcessEvent(const RE::TESContainerChangedEvent& a_event, RE::BSTEventSource<RE::TESContainerChangedEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* sourceRef = RE::TESForm::GetFormByID<RE::TESObjectREFR>(a_event.oldContainerFormID);
		const auto* targetRef = RE::TESForm::GetFormByID<RE::TESObjectREFR>(a_event.newContainerFormID);

		const auto* itemRef = RE::TESForm::GetFormByID<RE::TESObjectREFR>(a_event.referenceFormID);
		const auto* item = RE::TESForm::GetFormByID(a_event.baseObjectFormID);

		if (!_sourceFilter.Filter(sourceRef) ||
			!_targetFilter.Filter(targetRef) ||
			!(_itemFilter.Filter(itemRef) || _itemFilter.Filter(item))) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* source = sourceRef ? sourceRef->GetBaseObject() : nullptr;
		const auto* target = targetRef ? targetRef->GetBaseObject() : nullptr;

		auto args = EventArgs();
		args.insert("SourceRef"sv, sourceRef);
		args.insert("TargetRef"sv, targetRef);
		args.insert("ItemRef"sv, itemRef);
		args.insert("Source"sv, source);
		args.insert("Target"sv, target);
		args.insert("Item"sv, item);
		args.insert("ItemCount"sv, a_event.itemCount);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void ContainerChangeHandler::Register()
	{
		RE::TESContainerChangedEvent::GetEventSource()->RegisterSink(this);
	}

	void ContainerChangeHandler::Unregister()
	{
		RE::TESContainerChangedEvent::GetEventSource()->UnregisterSink(this);
	}
}
