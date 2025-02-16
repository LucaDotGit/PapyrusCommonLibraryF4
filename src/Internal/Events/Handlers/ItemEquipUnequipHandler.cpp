#include "Internal/Events/Handlers/ItemEquipUnequipHandler.hpp"

namespace Internal::Events
{
	ItemEquipUnequipHandler::ItemEquipUnequipHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
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

	ItemEquipUnequipHandler::~ItemEquipUnequipHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl ItemEquipUnequipHandler::ProcessEvent(const RE::TESEquipEvent& a_event, RE::BSTEventSource<RE::TESEquipEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* sourceActor = a_event.actor ? a_event.actor.get()->As<RE::Actor>() : nullptr;
		const auto* targetRef = RE::TESForm::GetFormByID<RE::TESObjectREFR>(a_event.originalRefr);

		const auto* source = sourceActor ? sourceActor->GetActorBase() : nullptr;
		const auto* target = RE::TESForm::GetFormByID<RE::TESForm>(a_event.baseObject);

		if (!_sourceFilter.Filter(sourceActor) ||
			!(targetRef ? _targetFilter.Filter(targetRef) : _targetFilter.Filter(target))) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("SourceActor"sv, sourceActor);
		args.insert("TargetRef"sv, targetRef);
		args.insert("Source"sv, source);
		args.insert("Target"sv, target);
		args.insert("IsEquipped"sv, a_event.equipped);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void ItemEquipUnequipHandler::Register()
	{
		RE::TESEquipEvent::GetEventSource()->RegisterSink(this);
	}

	void ItemEquipUnequipHandler::Unregister()
	{
		RE::TESEquipEvent::GetEventSource()->UnregisterSink(this);
	}
}
