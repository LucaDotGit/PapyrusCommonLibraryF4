#include "Internal/Events/Handlers/LockPickHandler.hpp"

#include "Internal/Callbacks/LockpickRefHandler.hpp"

namespace Internal::Events
{
	LockPickHandler::LockPickHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
		const std::vector<const RE::BSScript::Variable*>& a_excludedObjects) :
		IEventHandler(a_receiver),
		_filter{ a_includedObjects, a_excludedObjects }
	{
		Register();
	}

	LockPickHandler::~LockPickHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl LockPickHandler::ProcessEvent(const RE::LocksPicked::Event&, RE::BSTEventSource<RE::LocksPicked::Event>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto* objectRef = LockpickRefHandler::GetSingleton()->GetLastRef().get();
		auto* object = objectRef ? objectRef->GetBaseObject() : nullptr;

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

	void LockPickHandler::Register()
	{
		RE::LocksPicked::GetEventSource()->RegisterSink(this);
	}

	void LockPickHandler::Unregister()
	{
		RE::LocksPicked::GetEventSource()->UnregisterSink(this);
	}
}
