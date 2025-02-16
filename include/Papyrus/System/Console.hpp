#pragma once

namespace System::Console
{
	static constexpr auto SCRIPT_NAME = "System:Console"sv;

	static constexpr auto LINE_SEPARATOR = '\n';
	static constexpr auto COMMAND_SEPARATOR = ';';

	static constexpr auto COMMAND_HISTORY_PATH = "root1.AnimHolder_mc.Menu_mc.CommandHistory.text"sv;

	static std::vector<RE::TESObjectREFR*> GetSelectableRefs(std::monostate)
	{
		const auto menu = RE::UI::GetSingleton()->GetMenu<RE::Console>();
		if (!menu) {
			return {};
		}

		const auto& pickRefs = menu->GetPickRefs();

		auto refs = std::vector<RE::TESObjectREFR*>();
		refs.reserve(pickRefs.size());

		for (const auto& refHandle : pickRefs) {
			if (refHandle) {
				refs.push_back(refHandle.get().get());
			}
		}

		return refs;
	}

	static RE::TESObjectREFR* GetSelectedRef(std::monostate)
	{
		const auto menu = RE::UI::GetSingleton()->GetMenu<RE::Console>();
		if (!menu) {
			return nullptr;
		}

		const auto refHandle = menu->GetCurrentPickREFR();
		return refHandle ? refHandle.get().get() : nullptr;
	}

	static void SetSelectedRef(std::monostate,
		RE::TESObjectREFR* a_ref)
	{
		const auto menu = RE::UI::GetSingleton()->GetMenu<RE::Console>();
		if (!menu) {
			return;
		}

		auto handle = a_ref ? a_ref->GetHandle() : RE::ObjectRefHandle();
		menu->SetCurrentPickREFR(&handle);
	}

	static std::string GetHistory(std::monostate)
	{
		const auto menu = RE::UI::GetSingleton()->GetMenu<RE::Console>();

		if (menu) {
			auto history = RE::Scaleform::GFx::Value();
			menu->uiMovie->asMovieRoot->GetVariable(&history, COMMAND_HISTORY_PATH.data());
			return { history.GetString() };
		}
		else {
			const auto* log = RE::ConsoleLog::GetSingleton();
			return { log->buffer.data(), log->buffer.size() };
		}
	}

	static void SetHistory(std::monostate,
		std::string_view a_history)
	{
		const auto menu = RE::UI::GetSingleton()->GetMenu<RE::Console>();

		if (menu) {
			auto history = RE::Scaleform::GFx::Value(a_history.data());
			menu->uiMovie->asMovieRoot->SetVariable(COMMAND_HISTORY_PATH.data(), history);
		}
		else {
			auto* log = RE::ConsoleLog::GetSingleton();
			log->buffer = a_history;
		}
	}

	static void Write(std::monostate,
		std::string_view a_text)
	{
		auto* log = RE::ConsoleLog::GetSingleton();
		log->AddString(a_text.data());
	}

	static void WriteLine(std::monostate,
		std::string_view a_text)
	{
		auto* log = RE::ConsoleLog::GetSingleton();
		log->PrintLine(a_text.data());
	}

	static bool ExecuteCommand(std::monostate,
		std::string_view a_command,
		RE::TESObjectREFR* a_targetRef,
		bool a_silent)
	{
		auto* log = RE::ConsoleLog::GetSingleton();
		auto compiler = RE::ScriptCompiler();

		auto* scriptFactory = RE::ConcreteFormFactory<RE::Script>::GetFormFactory();
		auto* script = scriptFactory->Create();

		auto& buffer = log->buffer;

		if (!a_silent) {
			log->PrintLine(a_command.data());
		}

		auto oldBuffer = a_silent ? buffer : RE::BSString();
		auto lines = a_command | std::views::split(COMMAND_SEPARATOR) | std::views::transform([](auto&& a_line) noexcept {
			return std::string_view{ a_line.begin(), a_line.end() };
		});

		auto result = true;

		for (const auto& line : lines) {
			script->SetText(line);
			script->CompileAndRun(&compiler, RE::COMPILER_NAME::kSystemWindow, a_targetRef);

			if (!script->header.isCompiled) {
				result = false;
				break;
			}
		}

		if (a_silent) {
			buffer = std::move(oldBuffer);
		}

		delete script;
		return result;
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetSelectableRefs);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetSelectedRef);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetSelectedRef);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetHistory);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetHistory);
		BIND_METHOD(a_vm, SCRIPT_NAME, Write);
		BIND_METHOD(a_vm, SCRIPT_NAME, WriteLine);
		BIND_METHOD(a_vm, SCRIPT_NAME, ExecuteCommand);

		return true;
	}
}
