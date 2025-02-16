#include "Internal/Events/Handlers/TerminalHackHandler.hpp"

namespace Internal::Events
{
	TerminalHackHandler::TerminalHackHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
		const std::vector<const RE::BSScript::Variable*>& a_excludedObjects) :
		IEventHandler(a_receiver),
		_filter{ a_includedObjects, a_excludedObjects }
	{
		Register();
	}

	TerminalHackHandler::~TerminalHackHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl TerminalHackHandler::ProcessEvent(const RE::TerminalHacked::Event& a_event, RE::BSTEventSource<RE::TerminalHacked::Event>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto* objectRef = a_event.terminal ? a_event.terminal.get().get() : nullptr;
		auto* object = objectRef ? objectRef->GetBaseObject()->As<RE::BGSTerminal>() : nullptr;

		const auto lock = objectRef ? objectRef->GetLock()->GetLockLevel(objectRef) : RE::LOCK_LEVEL::kUnlocked;
		const auto lockLevel = RE::REFR_LOCK::GetLevelForLock(lock);

		if (!_filter.Filter(objectRef)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("ObjectRef"sv, objectRef);
		args.insert("Object"sv, object);
		args.insert("LockLevel"sv, lockLevel);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void TerminalHackHandler::Register()
	{
		RE::TerminalHacked::GetEventSource()->RegisterSink(this);
	}

	void TerminalHackHandler::Unregister()
	{
		RE::TerminalHacked::GetEventSource()->UnregisterSink(this);
	}
}
