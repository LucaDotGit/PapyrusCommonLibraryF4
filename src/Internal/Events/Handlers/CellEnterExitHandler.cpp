#include "Internal/Events/Handlers/CellEnterExitHandler.hpp"

namespace Internal::Events
{
	CellEnterExitHandler::CellEnterExitHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
		const std::vector<const RE::BSScript::Variable*>& a_excludedObjects) :
		IEventHandler(a_receiver),
		_filter{ a_includedObjects, a_excludedObjects }
	{
		Register();
	}

	CellEnterExitHandler::~CellEnterExitHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl CellEnterExitHandler::ProcessEvent(const RE::BGSActorCellEvent& a_event, RE::BSTEventSource<RE::BGSActorCellEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* object = RE::TESForm::GetFormByID<RE::TESObjectCELL>(a_event.cellID);

		if (!_filter.Filter(object)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto isEntered = a_event.flags == RE::BGSActorCellEvent::CellFlags::kEnter;

		auto args = EventArgs();
		args.insert("SourceActor"sv, a_event.actor.get().get());
		args.insert("Object"sv, object);
		args.insert("IsEntered"sv, isEntered);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void CellEnterExitHandler::Register()
	{
		auto* eventSource = RE::PlayerCharacter::GetSingleton();
		reinterpret_cast<RE::BSTEventSource<RE::BGSActorCellEvent>*>(eventSource)->RegisterSink(this);
	}

	void CellEnterExitHandler::Unregister()
	{
		auto* eventSource = RE::PlayerCharacter::GetSingleton();
		reinterpret_cast<RE::BSTEventSource<RE::BGSActorCellEvent>*>(eventSource)->UnregisterSink(this);
	}
}
