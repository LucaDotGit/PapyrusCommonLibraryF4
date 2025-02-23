#pragma once

namespace System::Enchantment
{
	static constexpr auto SCRIPT_NAME = "System:Enchantment"sv;

	static constexpr auto FLAGS_KEY = "Flags"sv;
	static constexpr auto TYPE_KEY = "Type"sv;
	static constexpr auto CAST_TYPE_KEY = "CastType"sv;
	static constexpr auto TARGET_TYPE_KEY = "TargetType"sv;
	static constexpr auto CHARGE_TIME_KEY = "ChargeTime"sv;
	static constexpr auto BASE_ENCHANTMENT_KEY = "BaseEnchantment"sv;
	static constexpr auto WORN_RESTRICTIONS_KEY = "WornRestrictions"sv;
	static constexpr auto EFFECTS_KEY = "Effects"sv;

	using Data = RE::BSScript::structure_wrapper<"System:Enchantment", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::EnchantmentItem* a_enchantment)
	{
		if (!a_enchantment) {
			a_vm.PostError(::Internal::Errors::ENCHANTMENT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto& enchantmentData = a_enchantment->data;

		auto data = Data();
		data.insert(FLAGS_KEY, enchantmentData.flags.underlying());
		data.insert(TYPE_KEY, enchantmentData.spellType.underlying());
		data.insert(CAST_TYPE_KEY, enchantmentData.castingType.underlying());
		data.insert(TARGET_TYPE_KEY, enchantmentData.delivery.underlying());
		data.insert(CHARGE_TIME_KEY, enchantmentData.chargeTime);
		data.insert(BASE_ENCHANTMENT_KEY, enchantmentData.baseEnchantment);
		data.insert(WORN_RESTRICTIONS_KEY, enchantmentData.wornRestrictions);
		data.insert(EFFECTS_KEY, ::Internal::MagicItem::GetEntries(a_enchantment));

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::EnchantmentItem* a_enchantment,
		Data a_data)
	{
		if (!a_enchantment) {
			a_vm.PostError(::Internal::Errors::ENCHANTMENT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		auto& enchantmentData = a_enchantment->data;

		enchantmentData.flags = a_data.find<RE::EnchantmentItem::Flags>(FLAGS_KEY).value();
		enchantmentData.spellType = a_data.find<RE::MagicSystem::SpellType>(TYPE_KEY).value();
		enchantmentData.castingType = a_data.find<RE::MagicSystem::CastingType>(CAST_TYPE_KEY).value();
		enchantmentData.delivery = a_data.find<RE::MagicSystem::Delivery>(TARGET_TYPE_KEY).value();
		enchantmentData.chargeTime = a_data.find<float>(CHARGE_TIME_KEY).value();
		enchantmentData.baseEnchantment = a_data.find<RE::EnchantmentItem*>(BASE_ENCHANTMENT_KEY).value_or(nullptr);
		enchantmentData.wornRestrictions = a_data.find<RE::BGSListForm*>(WORN_RESTRICTIONS_KEY).value_or(nullptr);
		::Internal::MagicItem::SetEntries(a_enchantment, a_data.find<std::vector<::Internal::MagicItem::Entry>>(EFFECTS_KEY)
															 .value_or(std::vector<::Internal::MagicItem::Entry>()));
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}