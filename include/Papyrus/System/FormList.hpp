#pragma once

namespace System::FormList
{
	static constexpr auto SCRIPT_NAME = "System:FormList"sv;

	static constexpr auto EDITOR_FORMS_KEY = "EditorForms"sv;
	static constexpr auto SCRIPT_FORMS_KEY = "ScriptForms"sv;

	using Data = RE::BSScript::structure_wrapper<"System:FormList", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSListForm* a_formList)
	{
		if (!a_formList) {
			a_vm.PostError(::Internal::Errors::FORM_LIST_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		auto scriptForms = std::vector<RE::TESForm*>();
		const auto* scriptFormIDs = a_formList->scriptAddedTempForms;

		if (scriptFormIDs) {
			scriptForms.reserve(a_formList->scriptAddedFormCount);

			const auto&& [map, mutex] = RE::TESForm::GetAllForms();
			const auto lock = RE::BSAutoReadLock{ mutex };

			for (const auto formID : *scriptFormIDs) {
				auto formIt = map->find(formID);
				auto* form = formIt == map->end() ? nullptr : formIt->second;

				scriptForms.push_back(form);
			}
		}

		auto data = Data();
		data.insert(EDITOR_FORMS_KEY, a_formList->arrayOfForms);
		data.insert(SCRIPT_FORMS_KEY, scriptForms);

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSListForm* a_formList,
		Data a_data)
	{
		if (!a_formList) {
			a_vm.PostError(::Internal::Errors::FORM_LIST_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		const auto newEditorForms = a_data.find<std::vector<RE::TESForm*>>(EDITOR_FORMS_KEY).value_or(std::vector<RE::TESForm*>());
		const auto newScriptForms = a_data.find<std::vector<RE::TESForm*>>(SCRIPT_FORMS_KEY).value_or(std::vector<RE::TESForm*>());

		auto& oldEditorForms = a_formList->arrayOfForms;
		auto*& oldScriptForms = a_formList->scriptAddedTempForms;

		const auto newEditorFormSize = static_cast<std::uint32_t>(newEditorForms.size());
		const auto newScriptFormSize = static_cast<std::uint32_t>(newScriptForms.size());

		oldEditorForms.resize(newEditorFormSize);
		std::ranges::copy(newEditorForms, oldEditorForms.begin());

		if (oldScriptForms) {
			delete oldScriptForms;
			oldScriptForms = nullptr;
		}

		if (newScriptFormSize > 0) {
			oldScriptForms = new RE::BSTArray<RE::TESFormID>();
			oldScriptForms->resize(newScriptFormSize);

			for (auto i = 0ui32; i < newScriptFormSize; i++) {
				const auto* form = newScriptForms[i];
				const auto formID = form ? form->formID : 0;

				(*oldScriptForms)[i] = formID;
			}
		}

		a_formList->scriptAddedFormCount = newScriptFormSize;
		a_formList->AddChange(RE::CHANGE_TYPE::kFormListAddedForm);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}