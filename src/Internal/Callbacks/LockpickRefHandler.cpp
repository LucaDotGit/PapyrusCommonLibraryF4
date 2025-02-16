#include "Internal/Callbacks/LockpickRefHandler.hpp"

namespace Internal
{
	LockpickRefHandler::~LockpickRefHandler()
	{
		Unregister();
	}

	void LockpickRefHandler::Register()
	{
		RE::TESActivateEvent::GetEventSource()->RegisterSink(this);
	}

	void LockpickRefHandler::Unregister()
	{
		RE::TESActivateEvent::GetEventSource()->UnregisterSink(this);
	}

	RE::NiPointer<RE::TESObjectREFR> LockpickRefHandler::GetLastRef() const
	{
		const auto lock = std::shared_lock{ _mutex };
		return _lastRef;
	}

	void LockpickRefHandler::Clear()
	{
		const auto lock = std::unique_lock{ _mutex };
		_lastRef = {};
	}

	RE::BSEventNotifyControl LockpickRefHandler::ProcessEvent(const RE::TESActivateEvent& a_event, RE::BSTEventSource<RE::TESActivateEvent>*)
	{
		if (a_event.actionRef.get() != RE::PlayerCharacter::GetSingleton()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto& target = a_event.objectActivated;
		if (!target) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* refLock = target->GetLock();
		if (!refLock || refLock->flags != RE::REFR_LOCK::Flags::kLocked) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto lock = std::unique_lock{ _mutex };

		_lastRef = target;
		return RE::BSEventNotifyControl::kContinue;
	}
}
