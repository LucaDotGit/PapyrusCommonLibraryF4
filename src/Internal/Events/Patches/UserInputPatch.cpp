#include "Internal/Events/Patches/UserInputPatch.hpp"

#include "Internal/Events/Sources/ButtonEventSource.hpp"

namespace Internal::Events::UserInputPatch
{
	static auto _PerformInputProcessing = REL::Relocation<decltype(&RE::BSInputEventReceiver::PerformInputProcessing)>();

	static void PerformInputProcessing(RE::MenuControls* a_this, const RE::InputEvent* a_queueHead)
	{
		if (!a_queueHead ||
			a_queueHead->eventType != RE::INPUT_EVENT_TYPE::kButton) {
			_PerformInputProcessing(a_this, a_queueHead);
			return;
		}

		const auto* event = reinterpret_cast<const RE::ButtonEvent*>(a_queueHead);
		if (event->disabled) {
			_PerformInputProcessing(a_this, a_queueHead);
			return;
		}

		_PerformInputProcessing(a_this, a_queueHead);

		ButtonEventSource::GetEventSource()->Notify(ButtonEvent{
			event->device.get(),
			event->GetBSButtonCode(),
			event->strUserEvent,
			event->value,
			event->heldDownSecs });
	}

	void Install() noexcept
	{
		auto vtable = REL::Relocation<std::uintptr_t>{ RE::VTABLE::MenuControls[0] };
		_PerformInputProcessing = vtable.write_vfunc(0x0, PerformInputProcessing);
	}
}
