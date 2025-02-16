#pragma once

namespace System::Explosion
{
	static constexpr auto SCRIPT_NAME = "System:Explosion"sv;

	static constexpr auto FLAGS_KEY = "Flags"sv;
	static constexpr auto USED_LIGHT_KEY = "UsedLight"sv;
	static constexpr auto SOUND01_KEY = "Sound01"sv;
	static constexpr auto SOUND02_KEY = "Sound02"sv;
	static constexpr auto IMPACT_DATA_KEY = "ImpactData"sv;
	static constexpr auto PLACED_OBJECT_KEY = "PlacedObject"sv;
	static constexpr auto PLACED_OBJECT_AUTO_FADE_DELAY_KEY = "PlacedObjectAutoFadeDelay"sv;
	static constexpr auto SPAWNED_PROJECTILE_KEY = "SpawnedProjectile"sv;
	static constexpr auto SPAWN_POSITION_KEY = "SpawnPosition"sv;
	static constexpr auto PROJECTILE_SPREAD_ANGLE_KEY = "ProjectileSpreadAngle"sv;
	static constexpr auto PROJECTILE_COUNT_KEY = "ProjectileCount"sv;
	static constexpr auto FORCE_KEY = "Force"sv;
	static constexpr auto DAMAGE_KEY = "Damage"sv;
	static constexpr auto INNER_RADIUS_KEY = "InnerRadius"sv;
	static constexpr auto OUTER_RADIUS_KEY = "OuterRadius"sv;
	static constexpr auto IMAGE_SPACE_RADIUS_KEY = "ImageSpaceRadius"sv;
	static constexpr auto VERTICAL_OFFSET_MULT_KEY = "VerticalOffsetMult"sv;
	static constexpr auto SOUND_LEVEL_KEY = "SoundLevel"sv;
	static constexpr auto STAGGER_MAGNITUDE_KEY = "StaggerMagnitude"sv;

	using Data = RE::BSScript::structure_wrapper<"System:Explosion", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSExplosion* a_explosion)
	{
		if (!a_explosion) {
			a_vm.PostError(::Internal::Errors::EXPLOSION_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto& explosionData = a_explosion->data;

		auto data = Data();
		data.insert(FLAGS_KEY, explosionData.flags.underlying());
		data.insert(USED_LIGHT_KEY, explosionData.light);
		data.insert(SOUND01_KEY, explosionData.sound1);
		data.insert(SOUND02_KEY, explosionData.sound2);
		data.insert(IMPACT_DATA_KEY, explosionData.impactDataSet);
		data.insert(PLACED_OBJECT_KEY, explosionData.impactPlacedObject);
		data.insert(PLACED_OBJECT_AUTO_FADE_DELAY_KEY, explosionData.placedObjectFadeDelay);
		data.insert(SPAWNED_PROJECTILE_KEY, explosionData.spawnProjectile);
		data.insert(SPAWN_POSITION_KEY, ::Internal::Vectors::MakeVector3(explosionData.projectileVector));
		data.insert(PROJECTILE_SPREAD_ANGLE_KEY, explosionData.projectileSpread);
		data.insert(PROJECTILE_COUNT_KEY, explosionData.projectileCount);
		data.insert(FORCE_KEY, explosionData.force);
		data.insert(DAMAGE_KEY, explosionData.damage);
		data.insert(INNER_RADIUS_KEY, explosionData.innerRadius);
		data.insert(OUTER_RADIUS_KEY, explosionData.outerRadius);
		data.insert(IMAGE_SPACE_RADIUS_KEY, explosionData.imageSpaceRadius);
		data.insert(VERTICAL_OFFSET_MULT_KEY, explosionData.verticalOffsetMult);
		data.insert(SOUND_LEVEL_KEY, explosionData.soundLevel.underlying());
		data.insert(STAGGER_MAGNITUDE_KEY, explosionData.staggerMagnitude.underlying());

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSExplosion* a_explosion,
		Data a_data)
	{
		if (!a_explosion) {
			a_vm.PostError(::Internal::Errors::EXPLOSION_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		const auto position = a_data.find<::Internal::Vectors::Vector3>(SPAWN_POSITION_KEY).value_or(::Internal::Vectors::Vector3());
		const auto&& [x, y, z] = ::Internal::Vectors::GetVector3(position);

		auto& explosionData = a_explosion->data;

		explosionData.flags = a_data.find<RE::BGSExplosionData::Flags>(FLAGS_KEY).value();
		explosionData.light = a_data.find<RE::TESObjectLIGH*>(USED_LIGHT_KEY).value_or(nullptr);
		explosionData.sound1 = a_data.find<RE::BGSSoundDescriptorForm*>(SOUND01_KEY).value_or(nullptr);
		explosionData.sound2 = a_data.find<RE::BGSSoundDescriptorForm*>(SOUND02_KEY).value_or(nullptr);
		explosionData.impactDataSet = a_data.find<RE::BGSImpactDataSet*>(IMPACT_DATA_KEY).value_or(nullptr);
		explosionData.impactPlacedObject = a_data.find<RE::TESBoundObject*>(PLACED_OBJECT_KEY).value_or(nullptr);
		explosionData.placedObjectFadeDelay = a_data.find<float>(PLACED_OBJECT_AUTO_FADE_DELAY_KEY).value();
		explosionData.spawnProjectile = a_data.find<RE::BGSProjectile*>(SPAWNED_PROJECTILE_KEY).value_or(nullptr);
		explosionData.projectileVector = { x, y, z };
		explosionData.projectileSpread = a_data.find<float>(PROJECTILE_SPREAD_ANGLE_KEY).value();
		explosionData.projectileCount = a_data.find<std::uint32_t>(PROJECTILE_COUNT_KEY).value();
		explosionData.force = a_data.find<float>(FORCE_KEY).value();
		explosionData.damage = a_data.find<float>(DAMAGE_KEY).value();
		explosionData.innerRadius = a_data.find<float>(INNER_RADIUS_KEY).value();
		explosionData.outerRadius = a_data.find<float>(OUTER_RADIUS_KEY).value();
		explosionData.imageSpaceRadius = a_data.find<float>(IMAGE_SPACE_RADIUS_KEY).value();
		explosionData.verticalOffsetMult = a_data.find<float>(VERTICAL_OFFSET_MULT_KEY).value();
		explosionData.soundLevel = a_data.find<RE::SOUND_LEVEL>(SOUND_LEVEL_KEY).value();
		explosionData.staggerMagnitude = a_data.find<RE::STAGGER_MAGNITUDE>(STAGGER_MAGNITUDE_KEY).value();
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}