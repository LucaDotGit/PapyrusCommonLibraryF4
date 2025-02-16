#pragma once

namespace System::Potion
{
	static constexpr auto SCRIPT_NAME = "System:Potion"sv;

	static constexpr auto FLAGS_KEY = "Flags"sv;
	static constexpr auto CRAFT_SOUND_KEY = "CraftSound"sv;
	static constexpr auto CONSUME_SOUND_KEY = "ConsumeSound"sv;
	static constexpr auto ADDICTION_KEY = "Addiction"sv;
	static constexpr auto ADDICTION_CHANCE_KEY = "AddictionChance"sv;
	static constexpr auto ADDICTION_NAME_KEY = "AddictionName"sv;
	static constexpr auto EFFECTS_KEY = "Effects"sv;

	using Data = RE::BSScript::structure_wrapper<"System:Potion", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::AlchemyItem* a_potion)
	{
		if (!a_potion) {
			a_vm.PostError(::Internal::Errors::POTION_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto& potionData = a_potion->data;

		auto data = Data();
		data.insert(FLAGS_KEY, potionData.flags.underlying());
		data.insert(CRAFT_SOUND_KEY, a_potion->craftingUseSound);
		data.insert(CONSUME_SOUND_KEY, potionData.consumptionSound);
		data.insert(ADDICTION_KEY, potionData.addictionItem);
		data.insert(ADDICTION_CHANCE_KEY, potionData.addictionChance);
		data.insert(ADDICTION_NAME_KEY, potionData.addictionName);
		data.insert(EFFECTS_KEY, ::Internal::MagicItem::GetEntries(a_potion));

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::AlchemyItem* a_potion,
		Data a_data)
	{
		if (!a_potion) {
			a_vm.PostError(::Internal::Errors::POTION_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		auto& potionData = a_potion->data;

		potionData.flags = a_data.find<RE::AlchemyItem::Flags>(FLAGS_KEY).value();
		a_potion->craftingUseSound = a_data.find<RE::BGSSoundDescriptorForm*>(CRAFT_SOUND_KEY).value_or(nullptr);
		potionData.consumptionSound = a_data.find<RE::BGSSoundDescriptorForm*>(CONSUME_SOUND_KEY).value_or(nullptr);
		potionData.addictionItem = a_data.find<RE::SpellItem*>(ADDICTION_KEY).value_or(nullptr);
		potionData.addictionChance = a_data.find<float>(ADDICTION_CHANCE_KEY).value();
		potionData.addictionName = a_data.find<RE::BGSLocalizedString>(ADDICTION_NAME_KEY).value();
		::Internal::MagicItem::SetEntries(a_potion, a_data.find<std::vector<::Internal::MagicItem::Entry>>(EFFECTS_KEY).value_or(std::vector<::Internal::MagicItem::Entry>()));
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}