#pragma once

namespace System::Projectile
{
	static constexpr auto SCRIPT_NAME = "System:Projectile"sv;

	static constexpr auto FLAGS_KEY = "Flags"sv;
	static constexpr auto TYPE_KEY = "Type"sv;
	static constexpr auto SPEED_KEY = "Speed"sv;
	static constexpr auto GRAVITY_KEY = "Gravity"sv;
	static constexpr auto RANGE_KEY = "Range"sv;
	static constexpr auto IMPACT_FORCE_KEY = "ImpactForce"sv;
	static constexpr auto TRACER_FREQUENCY_KEY = "TracerFrequency"sv;
	static constexpr auto FADE_DURATION_KEY = "FadeDuration"sv;
	static constexpr auto CONE_SPREAD_KEY = "ConeSpread"sv;
	static constexpr auto COLLISION_RADIUS_KEY = "CollisionRadius"sv;
	static constexpr auto LIFETIME_KEY = "Lifetime"sv;
	static constexpr auto RELAUNCH_INTERVAL_KEY = "RelaunchInterval"sv;
	static constexpr auto MUZZLE_FLASH_LIGHT_KEY = "MuzzleFlashLight"sv;
	static constexpr auto MUZZLE_FLASH_DURATION_KEY = "MuzzleFlashDuration"sv;
	static constexpr auto EFFECT_LIGHT_KEY = "EffectLight"sv;
	static constexpr auto SOURCE_WEAPON_KEY = "SourceWeapon"sv;
	static constexpr auto DECAL_KEY = "Decal"sv;
	static constexpr auto PLAYED_SOUND_KEY = "PlayedSound"sv;
	static constexpr auto COUNTDOWN_SOUND_KEY = "CountdownSound"sv;
	static constexpr auto DISARM_SOUND_KEY = "DisarmSound"sv;
	static constexpr auto SOUND_LEVEL_KEY = "SoundLevel"sv;
	static constexpr auto EXPLOSION_OBJECT_KEY = "ExplosionObject"sv;
	static constexpr auto EXPLOSION_TIMER_KEY = "ExplosionTimer"sv;
	static constexpr auto EXPLOSION_PROXIMITY_KEY = "ExplosionProximity"sv;
	static constexpr auto LAYER_KEY = "Layer"sv;
	static constexpr auto VATS_PROJECTILE_KEY = "VATSProjectile"sv;

	using Data = RE::BSScript::structure_wrapper<"System:Projectile", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSProjectile* a_projectile)
	{
		if (!a_projectile) {
			a_vm.PostError(::Internal::Errors::PROJECTILE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto& projectileData = a_projectile->data;

		auto data = Data();
		data.insert(FLAGS_KEY, projectileData.flags.underlying());
		data.insert(TYPE_KEY, projectileData.type.underlying());
		data.insert(SPEED_KEY, projectileData.speed);
		data.insert(GRAVITY_KEY, projectileData.gravity);
		data.insert(RANGE_KEY, projectileData.range);
		data.insert(IMPACT_FORCE_KEY, projectileData.force);
		data.insert(TRACER_FREQUENCY_KEY, projectileData.tracerFrequency);
		data.insert(FADE_DURATION_KEY, projectileData.fadeOutTime);
		data.insert(CONE_SPREAD_KEY, projectileData.coneSpread);
		data.insert(COLLISION_RADIUS_KEY, projectileData.collisionRadius);
		data.insert(LIFETIME_KEY, projectileData.lifetime);
		data.insert(RELAUNCH_INTERVAL_KEY, projectileData.relaunchInterval);
		data.insert(MUZZLE_FLASH_LIGHT_KEY, projectileData.muzzleFlashLight);
		data.insert(MUZZLE_FLASH_DURATION_KEY, projectileData.muzzleFlashDuration);
		data.insert(EFFECT_LIGHT_KEY, projectileData.light);
		data.insert(SOURCE_WEAPON_KEY, projectileData.defaultWeaponSource);
		data.insert(DECAL_KEY, projectileData.decalData);
		data.insert(PLAYED_SOUND_KEY, projectileData.activeSoundLoop);
		data.insert(COUNTDOWN_SOUND_KEY, projectileData.countdownSound);
		data.insert(DISARM_SOUND_KEY, projectileData.deactivateSound);
		data.insert(SOUND_LEVEL_KEY, a_projectile->soundLevel.underlying());
		data.insert(EXPLOSION_OBJECT_KEY, projectileData.explosionType);
		data.insert(EXPLOSION_TIMER_KEY, projectileData.explosionTimer);
		data.insert(EXPLOSION_PROXIMITY_KEY, projectileData.explosionProximity);
		data.insert(LAYER_KEY, projectileData.collisionLayer);
		data.insert(VATS_PROJECTILE_KEY, projectileData.vatsProjectile);

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSProjectile* a_projectile,
		Data a_data)
	{
		if (!a_projectile) {
			a_vm.PostError(::Internal::Errors::PROJECTILE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		auto& projectileData = a_projectile->data;

		projectileData.flags = a_data.find<RE::BGSProjectileData::Flags>(FLAGS_KEY).value();
		projectileData.type = a_data.find<RE::BGSProjectileData::Type>(TYPE_KEY).value();
		projectileData.speed = a_data.find<float>(SPEED_KEY).value();
		projectileData.gravity = a_data.find<float>(GRAVITY_KEY).value();
		projectileData.range = a_data.find<float>(RANGE_KEY).value();
		projectileData.force = a_data.find<float>(IMPACT_FORCE_KEY).value();
		projectileData.tracerFrequency = a_data.find<std::int8_t>(TRACER_FREQUENCY_KEY).value();
		projectileData.fadeOutTime = a_data.find<float>(FADE_DURATION_KEY).value();
		projectileData.coneSpread = a_data.find<float>(CONE_SPREAD_KEY).value();
		projectileData.collisionRadius = a_data.find<float>(COLLISION_RADIUS_KEY).value();
		projectileData.lifetime = a_data.find<float>(LIFETIME_KEY).value();
		projectileData.relaunchInterval = a_data.find<float>(RELAUNCH_INTERVAL_KEY).value();
		projectileData.muzzleFlashLight = a_data.find<RE::TESObjectLIGH*>(MUZZLE_FLASH_LIGHT_KEY).value_or(nullptr);
		projectileData.muzzleFlashDuration = a_data.find<float>(MUZZLE_FLASH_DURATION_KEY).value();
		projectileData.light = a_data.find<RE::TESObjectLIGH*>(EFFECT_LIGHT_KEY).value_or(nullptr);
		projectileData.defaultWeaponSource = a_data.find<RE::TESObjectWEAP*>(SOURCE_WEAPON_KEY).value_or(nullptr);
		projectileData.decalData = a_data.find<RE::BGSTextureSet*>(DECAL_KEY).value_or(nullptr);
		projectileData.activeSoundLoop = a_data.find<RE::BGSSoundDescriptorForm*>(PLAYED_SOUND_KEY).value_or(nullptr);
		projectileData.countdownSound = a_data.find<RE::BGSSoundDescriptorForm*>(COUNTDOWN_SOUND_KEY).value_or(nullptr);
		projectileData.deactivateSound = a_data.find<RE::BGSSoundDescriptorForm*>(DISARM_SOUND_KEY).value_or(nullptr);
		a_projectile->soundLevel = a_data.find<RE::SOUND_LEVEL>(SOUND_LEVEL_KEY).value();
		projectileData.explosionType = a_data.find<RE::BGSExplosion*>(EXPLOSION_OBJECT_KEY).value_or(nullptr);
		projectileData.explosionTimer = a_data.find<float>(EXPLOSION_TIMER_KEY).value();
		projectileData.explosionProximity = a_data.find<float>(EXPLOSION_PROXIMITY_KEY).value();
		projectileData.collisionLayer = a_data.find<RE::BGSCollisionLayer*>(LAYER_KEY).value_or(nullptr);
		projectileData.vatsProjectile = a_data.find<RE::BGSProjectile*>(VATS_PROJECTILE_KEY).value_or(nullptr);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}