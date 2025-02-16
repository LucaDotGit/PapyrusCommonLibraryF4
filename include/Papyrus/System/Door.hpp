#pragma once

namespace System::Door
{
	static constexpr auto SCRIPT_NAME = "System:Door"sv;

	static constexpr auto FORM_FLAGS_KEY = "FormFlags"sv;
	static constexpr auto FLAGS_KEY = "Flags"sv;
	static constexpr auto OPEN_SOUND_KEY = "OpenSound"sv;
	static constexpr auto CLOSE_SOUND_KEY = "CloseSound"sv;
	static constexpr auto LOOP_SOUND_KEY = "LoopSound"sv;
	static constexpr auto ALT_OPEN_TEXT_KEY = "AltOpenText"sv;
	static constexpr auto ALT_CLOSE_TEXT_KEY = "AltCloseText"sv;

	using Data = RE::BSScript::structure_wrapper<"System:Door", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectDOOR* a_door)
	{
		if (!a_door) {
			a_vm.PostError(::Internal::Errors::DOOR_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		auto data = Data();
		data.insert(FORM_FLAGS_KEY, a_door->formFlags);
		data.insert(FLAGS_KEY, a_door->flags.underlying());
		data.insert(OPEN_SOUND_KEY, a_door->openSound);
		data.insert(CLOSE_SOUND_KEY, a_door->closeSound);
		data.insert(LOOP_SOUND_KEY, a_door->loopSound);
		data.insert(ALT_OPEN_TEXT_KEY, a_door->altOpenText);
		data.insert(ALT_CLOSE_TEXT_KEY, a_door->altCloseText);

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectDOOR* a_door,
		Data a_data)
	{
		if (!a_door) {
			a_vm.PostError(::Internal::Errors::DOOR_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		a_door->flags = a_data.find<RE::TESObjectDOOR::Flags>(FLAGS_KEY).value();
		a_door->openSound = a_data.find<RE::BGSSoundDescriptorForm*>(OPEN_SOUND_KEY).value_or(nullptr);
		a_door->closeSound = a_data.find<RE::BGSSoundDescriptorForm*>(CLOSE_SOUND_KEY).value_or(nullptr);
		a_door->loopSound = a_data.find<RE::BGSSoundDescriptorForm*>(LOOP_SOUND_KEY).value_or(nullptr);
		a_door->altOpenText = a_data.find<RE::BGSLocalizedString>(ALT_OPEN_TEXT_KEY).value();
		a_door->altCloseText = a_data.find<RE::BGSLocalizedString>(ALT_CLOSE_TEXT_KEY).value();

		const auto formFlags = a_data.find<std::uint32_t>(FORM_FLAGS_KEY).value();
		if (formFlags != a_door->formFlags) {
			a_door->formFlags = formFlags;
			a_door->AddChange(RE::CHANGE_TYPE::kFormFlags);
		}
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}