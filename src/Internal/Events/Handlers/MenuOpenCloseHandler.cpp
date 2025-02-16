#include "Internal/Events/Handlers/MenuOpenCloseHandler.hpp"

namespace Internal::Events
{
	MenuOpenCloseHandler::MenuOpenCloseHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<RE::BSFixedString>& a_includedMenuNames,
		const std::vector<RE::BSFixedString>& a_excludedMenuNames) :
		IEventHandler(a_receiver),
		_includedMenuNames{ a_includedMenuNames.begin(), a_includedMenuNames.end() },
		_excludedMenuNames{ a_excludedMenuNames.begin(), a_excludedMenuNames.end() }
	{
		Register();
	}

	MenuOpenCloseHandler::~MenuOpenCloseHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl MenuOpenCloseHandler::ProcessEvent(const RE::MenuOpenCloseEvent& a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		if (!VarFilter::FilterByStrings(a_event.menuName, _includedMenuNames, _excludedMenuNames)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("MenuName"sv, a_event.menuName);
		args.insert("IsOpened"sv, a_event.opening);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void MenuOpenCloseHandler::Register()
	{
		RE::UI::GetSingleton()->RegisterSink(this);
	}

	void MenuOpenCloseHandler::Unregister()
	{
		RE::UI::GetSingleton()->UnregisterSink(this);
	}
}
