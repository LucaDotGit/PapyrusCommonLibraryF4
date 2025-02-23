#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/ButtonEventSource.hpp"

namespace Internal::Events
{
	class ButtonUpDownHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<ButtonEvent>
	{
	public:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "ButtonUpDownArgs">;

	public:
		ButtonUpDownHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<RE::INPUT_DEVICE>& a_includedDeviceTypes,
			const std::vector<RE::INPUT_DEVICE>& a_excludedDeviceTypes,
			const std::vector<RE::BS_BUTTON_CODE>& a_includedButtonCodes,
			const std::vector<RE::BS_BUTTON_CODE>& a_excludedButtonCodes,
			const std::vector<RE::BSFixedString>& a_includedControlNames,
			const std::vector<RE::BSFixedString>& a_excludedControlNames);

		~ButtonUpDownHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const ButtonEvent& a_event, RE::BSTEventSource<ButtonEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const std::unordered_set<RE::INPUT_DEVICE> _includedDeviceTypes;
		const std::unordered_set<RE::INPUT_DEVICE> _excludedDeviceTypes;
		const std::unordered_set<RE::BS_BUTTON_CODE> _includedButtonCodes;
		const std::unordered_set<RE::BS_BUTTON_CODE> _excludedButtonCodes;
		const Types::unordered_string_set<RE::BSFixedString> _includedControlNames;
		const Types::unordered_string_set<RE::BSFixedString> _excludedControlNames;
	};
}
