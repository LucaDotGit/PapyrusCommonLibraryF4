#include "Internal/Events/Handlers/ButtonUpDownHandler.hpp"

namespace Internal::Events
{
	ButtonUpDownHandler::ButtonUpDownHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<RE::INPUT_DEVICE>& a_includedDeviceTypes,
		const std::vector<RE::INPUT_DEVICE>& a_excludedDeviceTypes,
		const std::vector<RE::BS_BUTTON_CODE>& a_includedButtonCodes,
		const std::vector<RE::BS_BUTTON_CODE>& a_excludedButtonCodes,
		const std::vector<RE::BSFixedString>& a_includedControlNames,
		const std::vector<RE::BSFixedString>& a_excludedControlNames) :
		IEventHandler(a_receiver),
		_includedDeviceTypes{ a_includedDeviceTypes.begin(), a_includedDeviceTypes.end() },
		_excludedDeviceTypes{ a_excludedDeviceTypes.begin(), a_excludedDeviceTypes.end() },
		_includedButtonCodes{ a_includedButtonCodes.begin(), a_includedButtonCodes.end() },
		_excludedButtonCodes{ a_excludedButtonCodes.begin(), a_excludedButtonCodes.end() },
		_includedControlNames{ a_includedControlNames.begin(), a_includedControlNames.end() },
		_excludedControlNames{ a_excludedControlNames.begin(), a_excludedControlNames.end() }
	{
		Register();
	}

	ButtonUpDownHandler::~ButtonUpDownHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl ButtonUpDownHandler::ProcessEvent(const ButtonEvent& a_event, RE::BSTEventSource<ButtonEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		if (!a_event.IsUp() && !a_event.IsDown()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		if (!VarFilter::FilterByEnums(a_event.deviceType, _includedDeviceTypes, _excludedDeviceTypes) ||
			!VarFilter::FilterByEnums(a_event.buttonCode, _includedButtonCodes, _excludedButtonCodes) ||
			!VarFilter::FilterByStrings(a_event.controlName, _includedControlNames, _excludedControlNames)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("DeviceType"sv, a_event.deviceType);
		args.insert("ButtonCode"sv, a_event.buttonCode);
		args.insert("ControlName"sv, a_event.controlName);
		args.insert("AnalogValue"sv, a_event.analogValue);
		args.insert("HeldSeconds"sv, a_event.heldSeconds);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void ButtonUpDownHandler::Register()
	{
		ButtonEventSource::GetEventSource()->RegisterSink(this);
	}

	void ButtonUpDownHandler::Unregister()
	{
		ButtonEventSource::GetEventSource()->UnregisterSink(this);
	}
}
