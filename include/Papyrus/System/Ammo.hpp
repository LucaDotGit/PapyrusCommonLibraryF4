#pragma once

namespace System::Ammo
{
	static constexpr auto SCRIPT_NAME = "System:Ammo"sv;

	static constexpr auto FLAGS_KEY = "Flags"sv;
	static constexpr auto USED_PROJECTILE_KEY = "UsedProjectile"sv;
	static constexpr auto HEALTH_KEY = "Health"sv;
	static constexpr auto DAMAGE_KEY = "Damage"sv;
	static constexpr auto SHORT_NAME_KEY = "ShortName"sv;

	using Data = RE::BSScript::structure_wrapper<"System:Ammo", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESAmmo* a_ammo)
	{
		if (!a_ammo) {
			a_vm.PostError(::Internal::Errors::AMMO_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto& ammoData = a_ammo->data;

		auto data = Data();
		data.insert(FLAGS_KEY, ammoData.flags.underlying());
		data.insert(USED_PROJECTILE_KEY, ammoData.projectile);
		data.insert(HEALTH_KEY, ammoData.health);
		data.insert(DAMAGE_KEY, ammoData.damage);
		data.insert(SHORT_NAME_KEY, a_ammo->shortDesc);

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESAmmo* a_ammo,
		Data a_data)
	{
		if (!a_ammo) {
			a_vm.PostError(::Internal::Errors::AMMO_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		auto& ammoData = a_ammo->data;

		ammoData.flags = a_data.find<RE::AMMO_DATA::Flags>(FLAGS_KEY).value();
		ammoData.projectile = a_data.find<RE::BGSProjectile*>(USED_PROJECTILE_KEY).value_or(nullptr);
		ammoData.health = a_data.find<std::uint32_t>(HEALTH_KEY).value();
		ammoData.damage = a_data.find<float>(DAMAGE_KEY).value();
		a_ammo->shortDesc = a_data.find<RE::BGSLocalizedString>(SHORT_NAME_KEY).value();
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}