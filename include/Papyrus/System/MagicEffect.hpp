#pragma once

namespace System::MagicEffect
{
	static constexpr auto SCRIPT_NAME = "System:MagicEffect"sv;

	static constexpr auto FLAGS_KEY = "Flags"sv;
	static constexpr auto ARCHETYPE_KEY = "Archetype"sv;
	static constexpr auto CAST_TYPE_KEY = "CastType"sv;
	static constexpr auto TARGET_TYPE_KEY = "TargetType"sv;
	static constexpr auto PRIMARY_VALUE_KEY = "PrimaryValue"sv;
	static constexpr auto SECONDARY_VALUE_KEY = "SecondaryValue"sv;
	static constexpr auto SECONDARY_VALUE_WEIGHT_KEY = "SecondaryValueWeight"sv;
	static constexpr auto RESIST_VALUE_KEY = "ResistValue"sv;
	static constexpr auto APPLYING_PERK_KEY = "ApplyingPerk"sv;
	static constexpr auto TAPER_CURVE_KEY = "TaperCurve"sv;
	static constexpr auto TAPER_WEIGHT_KEY = "TaperWeight"sv;
	static constexpr auto TAPER_DURATION_KEY = "TaperDuration"sv;
	static constexpr auto BASE_COST_KEY = "BaseCost"sv;
	static constexpr auto SKILL_USAGE_MULT_KEY = "SkillUsageMult"sv;
	static constexpr auto HIT_VISUALS_KEY = "HitVisuals"sv;
	static constexpr auto ENCHANT_VISUALS_KEY = "EnchantVisuals"sv;
	static constexpr auto CASTING_ART_KEY = "CastingArt"sv;
	static constexpr auto CASTING_LIGHT_KEY = "CastingLight"sv;
	static constexpr auto HIT_ART_KEY = "HitArt"sv;
	static constexpr auto HIT_SHADER_KEY = "HitShader"sv;
	static constexpr auto ENCHANT_ART_KEY = "EnchantArt"sv;
	static constexpr auto ENCHANT_SHADER_KEY = "EnchantShader"sv;
	static constexpr auto EFFECT_PROJECTILE_KEY = "EffectProjectile"sv;
	static constexpr auto IMPACT_DATA_KEY = "ImpactData"sv;
	static constexpr auto EFFECT_EXPLOSION_KEY = "EffectExplosion"sv;
	static constexpr auto IMAGE_SPACE_MOD_KEY = "ImageSpaceMod"sv;
	static constexpr auto SPELL_AREA_KEY = "SpellArea"sv;
	static constexpr auto SPELL_CHARGE_TIME_KEY = "SpellChargeTime"sv;
	static constexpr auto AI_SCORE_KEY = "AIScore"sv;
	static constexpr auto AI_DELAY_TIME_KEY = "AIDelayTime"sv;
	static constexpr auto EQUIP_ABILITY_KEY = "EquipAbility"sv;
	static constexpr auto DESCRIPTION_KEY = "Description"sv;

	using Data = RE::BSScript::structure_wrapper<"System:MagicEffect", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::EffectSetting* a_magicEffect)
	{
		if (!a_magicEffect) {
			a_vm.PostError(::Internal::Errors::MAGIC_EFFECT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto& effectData = a_magicEffect->data;

		auto data = Data();
		data.insert(FLAGS_KEY, effectData.flags.underlying());
		data.insert(ARCHETYPE_KEY, effectData.archetype.underlying());
		data.insert(CAST_TYPE_KEY, effectData.castingType.underlying());
		data.insert(TARGET_TYPE_KEY, effectData.delivery.underlying());
		data.insert(PRIMARY_VALUE_KEY, effectData.primaryAV);
		data.insert(SECONDARY_VALUE_KEY, effectData.secondaryAV);
		data.insert(SECONDARY_VALUE_WEIGHT_KEY, effectData.secondaryAVWeight);
		data.insert(RESIST_VALUE_KEY, effectData.resistVariable);
		data.insert(APPLYING_PERK_KEY, effectData.perk);
		data.insert(TAPER_CURVE_KEY, effectData.taperCurve);
		data.insert(TAPER_WEIGHT_KEY, effectData.taperWeight);
		data.insert(TAPER_DURATION_KEY, effectData.taperDuration);
		data.insert(BASE_COST_KEY, effectData.baseCost);
		data.insert(SKILL_USAGE_MULT_KEY, effectData.skillUsageMult);
		data.insert(HIT_VISUALS_KEY, effectData.hitVisuals);
		data.insert(ENCHANT_VISUALS_KEY, effectData.enchantVisuals);
		data.insert(CASTING_ART_KEY, effectData.castingArt);
		data.insert(CASTING_LIGHT_KEY, effectData.light);
		data.insert(HIT_ART_KEY, effectData.hitEffectArt);
		data.insert(HIT_SHADER_KEY, effectData.effectShader);
		data.insert(ENCHANT_ART_KEY, effectData.enchantEffectArt);
		data.insert(ENCHANT_SHADER_KEY, effectData.enchantEffect);
		data.insert(EFFECT_PROJECTILE_KEY, effectData.projectileBase);
		data.insert(IMPACT_DATA_KEY, effectData.impactDataSet);
		data.insert(EFFECT_EXPLOSION_KEY, effectData.explosion);
		data.insert(IMAGE_SPACE_MOD_KEY, effectData.imageSpaceMod);
		data.insert(SPELL_AREA_KEY, effectData.spellmakingArea);
		data.insert(SPELL_CHARGE_TIME_KEY, effectData.spellmakingChargeTime);
		data.insert(AI_SCORE_KEY, effectData.aiScore);
		data.insert(AI_DELAY_TIME_KEY, effectData.aiDelayTime);
		data.insert(EQUIP_ABILITY_KEY, effectData.equipAbility);
		data.insert(DESCRIPTION_KEY, a_magicEffect->magicItemDescription);

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::EffectSetting* a_magicEffect,
		Data a_data)
	{
		if (!a_magicEffect) {
			a_vm.PostError(::Internal::Errors::MAGIC_EFFECT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		auto& effectData = a_magicEffect->data;

		effectData.flags = a_data.find<RE::EffectSetting::EffectSettingData::Flags>(FLAGS_KEY).value();
		effectData.archetype = a_data.find<RE::EffectArchetypes::ArchetypeID>(ARCHETYPE_KEY).value();
		effectData.castingType = a_data.find<RE::MagicSystem::CastingType>(CAST_TYPE_KEY).value();
		effectData.delivery = a_data.find<RE::MagicSystem::Delivery>(TARGET_TYPE_KEY).value();
		effectData.primaryAV = a_data.find<RE::ActorValueInfo*>(PRIMARY_VALUE_KEY).value_or(nullptr);
		effectData.secondaryAV = a_data.find<RE::ActorValueInfo*>(SECONDARY_VALUE_KEY).value_or(nullptr);
		effectData.secondaryAVWeight = a_data.find<float>(SECONDARY_VALUE_WEIGHT_KEY).value();
		effectData.resistVariable = a_data.find<RE::ActorValueInfo*>(RESIST_VALUE_KEY).value_or(nullptr);
		effectData.perk = a_data.find<RE::BGSPerk*>(APPLYING_PERK_KEY).value_or(nullptr);
		effectData.taperCurve = a_data.find<float>(TAPER_CURVE_KEY).value();
		effectData.taperWeight = a_data.find<float>(TAPER_WEIGHT_KEY).value();
		effectData.taperDuration = a_data.find<float>(TAPER_DURATION_KEY).value();
		effectData.baseCost = a_data.find<float>(BASE_COST_KEY).value();
		effectData.skillUsageMult = a_data.find<float>(SKILL_USAGE_MULT_KEY).value();
		effectData.hitVisuals = a_data.find<RE::BGSReferenceEffect*>(HIT_VISUALS_KEY).value_or(nullptr);
		effectData.enchantVisuals = a_data.find<RE::BGSReferenceEffect*>(ENCHANT_VISUALS_KEY).value_or(nullptr);
		effectData.castingArt = a_data.find<RE::BGSArtObject*>(CASTING_ART_KEY).value_or(nullptr);
		effectData.light = a_data.find<RE::TESObjectLIGH*>(CASTING_LIGHT_KEY).value_or(nullptr);
		effectData.hitEffectArt = a_data.find<RE::BGSArtObject*>(HIT_ART_KEY).value_or(nullptr);
		effectData.effectShader = a_data.find<RE::TESEffectShader*>(HIT_SHADER_KEY).value_or(nullptr);
		effectData.enchantEffectArt = a_data.find<RE::BGSArtObject*>(ENCHANT_ART_KEY).value_or(nullptr);
		effectData.enchantEffect = a_data.find<RE::TESEffectShader*>(ENCHANT_SHADER_KEY).value_or(nullptr);
		effectData.projectileBase = a_data.find<RE::BGSProjectile*>(EFFECT_PROJECTILE_KEY).value_or(nullptr);
		effectData.impactDataSet = a_data.find<RE::BGSImpactDataSet*>(IMPACT_DATA_KEY).value_or(nullptr);
		effectData.explosion = a_data.find<RE::BGSExplosion*>(EFFECT_EXPLOSION_KEY).value_or(nullptr);
		effectData.imageSpaceMod = a_data.find<RE::TESImageSpaceModifier*>(IMAGE_SPACE_MOD_KEY).value_or(nullptr);
		effectData.spellmakingArea = a_data.find<std::int32_t>(SPELL_AREA_KEY).value();
		effectData.spellmakingChargeTime = a_data.find<float>(SPELL_CHARGE_TIME_KEY).value();
		effectData.aiScore = a_data.find<float>(AI_SCORE_KEY).value();
		effectData.aiDelayTime = a_data.find<float>(AI_DELAY_TIME_KEY).value();
		effectData.equipAbility = a_data.find<RE::SpellItem*>(EQUIP_ABILITY_KEY).value_or(nullptr);
		a_magicEffect->magicItemDescription = a_data.find<RE::BGSLocalizedString>(DESCRIPTION_KEY).value();
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}