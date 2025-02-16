#pragma once

namespace System::Flora
{
	static constexpr auto SCRIPT_NAME = "System:Flora"sv;

	static constexpr auto HARVEST_ITEM_KEY = "HarvestItem"sv;
	static constexpr auto HARVEST_SOUND_KEY = "HarvestSound"sv;
	static constexpr auto SPRING_HARVEST_CHANCE_KEY = "SpringHarvestChance"sv;
	static constexpr auto SUMMER_HARVEST_CHANCE_KEY = "SummerHarvestChance"sv;
	static constexpr auto FALL_HARVEST_CHANCE_KEY = "FallHarvestChance"sv;
	static constexpr auto WINTER_HARVEST_CHANCE_KEY = "WinterHarvestChance"sv;

	using Data = RE::BSScript::structure_wrapper<"System:Flora", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESFlora* a_flora)
	{
		if (!a_flora) {
			a_vm.PostError(::Internal::Errors::FLORA_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		using SEASON = RE::TESProduceForm::SEASON;

		auto data = Data();
		data.insert(HARVEST_ITEM_KEY, a_flora->produceItem);
		data.insert(HARVEST_SOUND_KEY, a_flora->harvestSound);
		data.insert(SPRING_HARVEST_CHANCE_KEY, a_flora->produceChance[SEASON::kSpring]);
		data.insert(SUMMER_HARVEST_CHANCE_KEY, a_flora->produceChance[SEASON::kSummer]);
		data.insert(FALL_HARVEST_CHANCE_KEY, a_flora->produceChance[SEASON::kFall]);
		data.insert(WINTER_HARVEST_CHANCE_KEY, a_flora->produceChance[SEASON::kWinter]);

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESFlora* a_flora,
		Data a_data)
	{
		if (!a_flora) {
			a_vm.PostError(::Internal::Errors::FLORA_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		using SEASON = RE::TESProduceForm::SEASON;

		a_flora->produceItem = a_data.find<RE::TESBoundObject*>(HARVEST_ITEM_KEY).value_or(nullptr);
		a_flora->harvestSound = a_data.find<RE::BGSSoundDescriptorForm*>(HARVEST_SOUND_KEY).value_or(nullptr);
		a_flora->produceChance[SEASON::kSpring] = a_data.find<std::int8_t>(SPRING_HARVEST_CHANCE_KEY).value();
		a_flora->produceChance[SEASON::kSummer] = a_data.find<std::int8_t>(SUMMER_HARVEST_CHANCE_KEY).value();
		a_flora->produceChance[SEASON::kFall] = a_data.find<std::int8_t>(FALL_HARVEST_CHANCE_KEY).value();
		a_flora->produceChance[SEASON::kWinter] = a_data.find<std::int8_t>(WINTER_HARVEST_CHANCE_KEY).value();
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}