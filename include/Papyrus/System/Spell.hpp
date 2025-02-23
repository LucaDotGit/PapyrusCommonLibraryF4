#pragma once

namespace System::Spell
{
	static constexpr auto SCRIPT_NAME = "System:Spell"sv;

	static constexpr auto FLAGS_KEY = "Flags"sv;
	static constexpr auto TYPE_KEY = "Type"sv;
	static constexpr auto CAST_TYPE_KEY = "CastType"sv;
	static constexpr auto TARGET_TYPE_KEY = "TargetType"sv;
	static constexpr auto RANGE_KEY = "Range"sv;
	static constexpr auto CHARGE_TIME_KEY = "ChargeTime"sv;
	static constexpr auto CAST_DURATION_KEY = "CastDuration"sv;
	static constexpr auto CASTING_PERK_KEY = "CastingPerk"sv;
	static constexpr auto EFFECTS_KEY = "Effects"sv;

	using Data = RE::BSScript::structure_wrapper<"System:Spell", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::SpellItem* a_spell)
	{
		if (!a_spell) {
			a_vm.PostError(::Internal::Errors::SPELL_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto& spellData = a_spell->data;

		auto data = Data();
		data.insert(FLAGS_KEY, spellData.flags.underlying());
		data.insert(TYPE_KEY, spellData.spellType.underlying());
		data.insert(CAST_TYPE_KEY, spellData.castingType.underlying());
		data.insert(TARGET_TYPE_KEY, spellData.delivery.underlying());
		data.insert(RANGE_KEY, spellData.range);
		data.insert(CHARGE_TIME_KEY, spellData.chargeTime);
		data.insert(CAST_DURATION_KEY, spellData.castDuration);
		data.insert(CASTING_PERK_KEY, spellData.castingPerk);
		data.insert(EFFECTS_KEY, ::Internal::MagicItem::GetEntries(a_spell));

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::SpellItem* a_spell,
		Data a_data)
	{
		if (!a_spell) {
			a_vm.PostError(::Internal::Errors::SPELL_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		auto& spellData = a_spell->data;

		spellData.flags = a_data.find<RE::SpellItem::Flags>(FLAGS_KEY).value();
		spellData.spellType = a_data.find<RE::MagicSystem::SpellType>(TYPE_KEY).value();
		spellData.castingType = a_data.find<RE::MagicSystem::CastingType>(CAST_TYPE_KEY).value();
		spellData.delivery = a_data.find<RE::MagicSystem::Delivery>(TARGET_TYPE_KEY).value();
		spellData.range = a_data.find<float>(RANGE_KEY).value();
		spellData.chargeTime = a_data.find<float>(CHARGE_TIME_KEY).value();
		spellData.castDuration = a_data.find<float>(CAST_DURATION_KEY).value();
		spellData.castingPerk = a_data.find<RE::BGSPerk*>(CASTING_PERK_KEY).value_or(nullptr);
		::Internal::MagicItem::SetEntries(a_spell, a_data.find<std::vector<::Internal::MagicItem::Entry>>(EFFECTS_KEY)
													   .value_or(std::vector<::Internal::MagicItem::Entry>()));
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}