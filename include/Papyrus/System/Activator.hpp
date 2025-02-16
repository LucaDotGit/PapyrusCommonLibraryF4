#pragma once

namespace System::Activator
{
	static constexpr auto SCRIPT_NAME = "System:Activator"sv;

	static constexpr auto FORM_FLAGS_KEY = "FormFlags"sv;
	static constexpr auto FLAGS_KEY = "Flags"sv;
	static constexpr auto LOOP_SOUND_KEY = "LoopSound"sv;
	static constexpr auto ACTIVATE_SOUND_KEY = "ActivateSound"sv;
	static constexpr auto WATER_KEY = "Water"sv;

	using Data = RE::BSScript::structure_wrapper<"System:Activator", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectACTI* a_activator)
	{
		if (!a_activator) {
			a_vm.PostError(::Internal::Errors::ACTIVATOR_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		auto data = Data();
		data.insert(FORM_FLAGS_KEY, a_activator->formFlags);
		data.insert(FLAGS_KEY, a_activator->flags.underlying());
		data.insert(LOOP_SOUND_KEY, a_activator->soundLoop);
		data.insert(ACTIVATE_SOUND_KEY, a_activator->soundActivate);
		data.insert(WATER_KEY, a_activator->waterForm);

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectACTI* a_activator,
		Data a_data)
	{
		if (!a_activator) {
			a_vm.PostError(::Internal::Errors::ACTIVATOR_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		a_activator->flags = a_data.find<RE::TESObjectACTI::Flags>(FLAGS_KEY).value();
		a_activator->soundLoop = a_data.find<RE::BGSSoundDescriptorForm*>(LOOP_SOUND_KEY).value_or(nullptr);
		a_activator->soundActivate = a_data.find<RE::BGSSoundDescriptorForm*>(ACTIVATE_SOUND_KEY).value_or(nullptr);
		a_activator->waterForm = a_data.find<RE::TESWaterForm*>(WATER_KEY).value_or(nullptr);

		const auto formFlags = a_data.find<std::uint32_t>(FORM_FLAGS_KEY).value();
		if (formFlags != a_activator->formFlags) {
			a_activator->formFlags = formFlags;
			a_activator->AddChange(RE::CHANGE_TYPE::kFormFlags);
		}
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}
