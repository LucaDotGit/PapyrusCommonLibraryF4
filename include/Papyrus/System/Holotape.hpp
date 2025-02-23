#pragma once

namespace System::Holotape
{
	static constexpr auto SCRIPT_NAME = "System:Holotape"sv;

	static constexpr auto TYPE_KEY = "Type"sv;
	static constexpr auto HAS_BEEN_READ_KEY = "HasBeenRead"sv;
	static constexpr auto PLAYING_SOUND_KEY = "PlayingSound"sv;
	static constexpr auto PLAYING_SCENE_KEY = "PlayingScene"sv;
	static constexpr auto PLAYING_PROGRAM_KEY = "PlayingProgram"sv;
	static constexpr auto PLAYING_TERMINAL_KEY = "PlayingTerminal"sv;

	using Data = RE::BSScript::structure_wrapper<"System:Holotape", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSNote* a_holotape)
	{
		if (!a_holotape) {
			a_vm.PostError(::Internal::Errors::HOLOTAPE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto* sound = a_holotape->type == RE::BGSNote::NOTE_TYPE::kVoice
								? a_holotape->noteSound
								: nullptr;

		const auto* scene = a_holotape->type == RE::BGSNote::NOTE_TYPE::kScene
								? RE::TESForm::GetFormByID<RE::BGSScene>(static_cast<RE::TESFormID>(a_holotape->noteFormID))
								: nullptr;

		const auto* terminal = a_holotape->type == RE::BGSNote::NOTE_TYPE::kTerminal
								   ? RE::TESForm::GetFormByID<RE::BGSTerminal>(static_cast<RE::TESFormID>(a_holotape->noteFormID))
								   : nullptr;

		auto data = Data();
		data.insert(TYPE_KEY, a_holotape->type.underlying());
		data.insert(HAS_BEEN_READ_KEY, a_holotape->hasBeenRead);
		data.insert(PLAYING_SOUND_KEY, sound);
		data.insert(PLAYING_SCENE_KEY, scene);
		data.insert(PLAYING_PROGRAM_KEY, a_holotape->programFile);
		data.insert(PLAYING_TERMINAL_KEY, terminal);

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSNote* a_holotape,
		Data a_data)
	{
		if (!a_holotape) {
			a_vm.PostError(::Internal::Errors::HOLOTAPE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		const auto type = a_data.find<RE::BGSNote::NOTE_TYPE>(TYPE_KEY).value();

		a_holotape->type = type;
		a_holotape->hasBeenRead = a_data.find<bool>(HAS_BEEN_READ_KEY).value();

		switch (type) {
			case RE::BGSNote::NOTE_TYPE::kVoice: {
				auto* voice = a_data.find<RE::BGSSoundDescriptorForm*>(PLAYING_SOUND_KEY).value_or(nullptr);

				a_holotape->programFile = nullptr;
				a_holotape->noteFormID = 0;
				a_holotape->noteSound = voice;
				break;
			}
			case RE::BGSNote::NOTE_TYPE::kScene: {
				auto* scene = a_data.find<RE::BGSScene*>(PLAYING_SCENE_KEY).value_or(nullptr);

				a_holotape->programFile = nullptr;
				a_holotape->noteSound = nullptr;
				a_holotape->noteFormID = scene ? scene->GetFormID() : 0;
				break;
			}
			case RE::BGSNote::NOTE_TYPE::kProgram: {
				auto program = a_data.find<RE::BSFixedString>(PLAYING_PROGRAM_KEY).value();

				a_holotape->noteSound = nullptr;
				a_holotape->noteFormID = 0;
				a_holotape->programFile = std::move(program);
				break;
			}
			case RE::BGSNote::NOTE_TYPE::kTerminal: {
				auto* terminal = a_data.find<RE::BGSTerminal*>(PLAYING_TERMINAL_KEY).value_or(nullptr);

				a_holotape->programFile = nullptr;
				a_holotape->noteSound = nullptr;
				a_holotape->noteFormID = terminal ? terminal->GetFormID() : 0;
				break;
			}
		}
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}