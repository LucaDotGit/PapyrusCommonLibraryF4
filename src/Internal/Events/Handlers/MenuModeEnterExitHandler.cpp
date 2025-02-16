#include "Internal/Events/Handlers/MenuModeEnterExitHandler.hpp"

namespace Internal::Events
{
	MenuModeEnterExitHandler::MenuModeEnterExitHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<RE::BSFixedString>& a_includedMenuNames,
		const std::vector<RE::BSFixedString>& a_excludedMenuNames) :
		IEventHandler(a_receiver),
		_includedMenuNames{ a_includedMenuNames.begin(), a_includedMenuNames.end() },
		_excludedMenuNames{ a_excludedMenuNames.begin(), a_excludedMenuNames.end() }
	{
		Register();
	}

	MenuModeEnterExitHandler::~MenuModeEnterExitHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl MenuModeEnterExitHandler::ProcessEvent(const RE::MenuModeChangeEvent& a_event, RE::BSTEventSource<RE::MenuModeChangeEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		if (!VarFilter::FilterByStrings(a_event.menuName, _includedMenuNames, _excludedMenuNames)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("MenuName"sv, a_event.menuName);
		args.insert("IsEntered"sv, a_event.enteringMenuMode);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void MenuModeEnterExitHandler::Register()
	{
		RE::UI::GetSingleton()->RegisterSink(this);
	}

	void MenuModeEnterExitHandler::Unregister()
	{
		RE::UI::GetSingleton()->UnregisterSink(this);
	}
}
