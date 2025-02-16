#pragma once

#include "Internal/Bethesda/MessageBoxCallback.hpp"

namespace System::Message
{
	static constexpr auto SCRIPT_NAME = "System:Message"sv;

	static constexpr auto FLAGS_KEY = "Flags"sv;
	static constexpr auto OWNER_QUEST_KEY = "OwnerQuest"sv;
	static constexpr auto DISPLAY_TIME_KEY = "DisplayTime"sv;
	static constexpr auto INTERFACE_FILE_KEY = "InterfaceFile"sv;
	static constexpr auto SHORT_NAME_KEY = "ShortName"sv;
	static constexpr auto BUTTONS_KEY = "Buttons"sv;

	static constexpr auto OK_TEXT = "$OK"sv;

	using Data = RE::BSScript::structure_wrapper<"System:Message", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSMessage* a_message)
	{
		if (!a_message) {
			a_vm.PostError(::Internal::Errors::MESSAGE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		auto data = Data();
		data.insert(FLAGS_KEY, a_message->flags.underlying());
		data.insert(OWNER_QUEST_KEY, a_message->ownerQuest);
		data.insert(DISPLAY_TIME_KEY, a_message->displayTime);
		data.insert(INTERFACE_FILE_KEY, a_message->swfFile);
		data.insert(SHORT_NAME_KEY, a_message->shortName);

		auto& oldButtons = a_message->buttonList;

		auto newButtons = std::vector<RE::BGSLocalizedString>();
		newButtons.reserve(std::distance(oldButtons.begin(), oldButtons.end()));

		std::for_each(oldButtons.begin(), oldButtons.end(), [&](const RE::MESSAGEBOX_BUTTON* button) {
			newButtons.push_back(button->text);
		});

		data.insert(BUTTONS_KEY, std::move(newButtons));

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSMessage* a_message,
		Data a_data)
	{
		if (!a_message) {
			a_vm.PostError(::Internal::Errors::MESSAGE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		a_message->flags = a_data.find<RE::BGSMessage::Flags>(FLAGS_KEY).value();
		a_message->ownerQuest = a_data.find<RE::TESQuest*>(OWNER_QUEST_KEY).value_or(nullptr);
		a_message->displayTime = a_data.find<std::uint32_t>(DISPLAY_TIME_KEY).value();
		a_message->swfFile = a_data.find<RE::BSFixedStringCS>(INTERFACE_FILE_KEY).value();
		a_message->shortName = a_data.find<RE::BGSLocalizedString>(SHORT_NAME_KEY).value();

		const auto newButtons = a_data.find<std::vector<RE::BSFixedStringCS>>(BUTTONS_KEY).value_or(std::vector<RE::BSFixedStringCS>());
		auto& oldButtons = a_message->buttonList;

		for (auto it = oldButtons.begin(); it != oldButtons.end(); it++) {
			auto*& button = *it;
			if (!button) {
				continue;
			}

			delete button;
			button = nullptr;
		}

		oldButtons.clear();

		std::ranges::for_each(newButtons, [&](const RE::BSFixedStringCS& a_text) {
			auto* button = new RE::MESSAGEBOX_BUTTON();

			button->text = a_text;
			oldButtons.emplace_front(button);
		});
	}

	static void MessageBoxEx(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		std::string_view a_text,
		std::vector<std::string_view> a_buttons)
	{
		if (!a_receiver) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		constexpr auto HEADER_TEXT = static_cast<const char*>(nullptr);

		auto* messageManager = RE::MessageMenuManager::GetSingleton();
		auto* messageCallback = new ::Internal::MessageBoxCallback(a_receiver);

		const auto lock = RE::BSAutoWriteLock{ messageManager->messageRWLock };
		const auto& messages = messageManager->messages;

		messageManager->Create(HEADER_TEXT, a_text.data(), messageCallback, RE::WARNING_TYPE::kDefault);

		const auto it = std::ranges::find_if(messages | std::views::reverse, [&](const RE::MessageBoxData* a_data) {
			return a_data && a_data->callback.get() == messageCallback;
		});

		if (it == messages.rend()) {
			delete messageCallback;
			assert(false);
			return;
		}

		auto& newButtons = (*it)->buttonText;
		newButtons.clear();

		if (a_buttons.empty()) {
			newButtons.emplace_back(OK_TEXT);
			return;
		}

		newButtons.reserve(static_cast<std::uint32_t>(a_buttons.size()));

		for (const auto& button : a_buttons) {
			newButtons.emplace_back(button);
		}
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, MessageBoxEx);

		return true;
	}
}
