#pragma once

namespace System::EncounterZone
{
	static constexpr auto SCRIPT_NAME = "System:EncounterZone"sv;

	static constexpr auto FLAGS_KEY = "Flags"sv;
	static constexpr auto OWNER_KEY = "Owner"sv;
	static constexpr auto OWNER_RANK_KEY = "OwnerRank"sv;
	static constexpr auto PARENT_LOCATION_KEY = "ParentLocation"sv;
	static constexpr auto MIN_LEVEL_KEY = "MinLevel"sv;
	static constexpr auto MAX_LEVEL_KEY = "MaxLevel"sv;

	static constexpr auto DETACH_TIME_KEY = "DetachTime"sv;
	static constexpr auto ATTACH_TIME_KEY = "AttachTime"sv;
	static constexpr auto RESET_TIME_KEY = "ResetTime"sv;
	static constexpr auto ZONE_LEVEL_KEY = "ZoneLevel"sv;

	using Data = RE::BSScript::structure_wrapper<"System:EncounterZone", "Data">;
	using GameData = RE::BSScript::structure_wrapper<"System:EncounterZone", "GameData">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSEncounterZone* a_encounterZone)
	{
		if (!a_encounterZone) {
			a_vm.PostError(::Internal::Errors::ENCOUNTER_ZONE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto& zoneData = a_encounterZone->data;

		auto data = Data();
		data.insert(FLAGS_KEY, zoneData.flags.underlying());
		data.insert(OWNER_KEY, zoneData.zoneOwner);
		data.insert(OWNER_RANK_KEY, zoneData.ownerRank);
		data.insert(PARENT_LOCATION_KEY, zoneData.location);
		data.insert(MIN_LEVEL_KEY, zoneData.minLevel);
		data.insert(MAX_LEVEL_KEY, zoneData.maxLevel);

		return data;
	}

	void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSEncounterZone* a_encounterZone,
		Data a_data)
	{
		if (!a_encounterZone) {
			a_vm.PostError(::Internal::Errors::ENCOUNTER_ZONE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		auto& zoneData = a_encounterZone->data;

		zoneData.zoneOwner = a_data.find<RE::TESForm*>(OWNER_KEY).value_or(nullptr);
		zoneData.ownerRank = a_data.find<std::int8_t>(OWNER_RANK_KEY).value();
		zoneData.location = a_data.find<RE::BGSLocation*>(PARENT_LOCATION_KEY).value_or(nullptr);
		zoneData.minLevel = a_data.find<std::int8_t>(MIN_LEVEL_KEY).value();
		zoneData.maxLevel = a_data.find<std::int8_t>(MAX_LEVEL_KEY).value();

		const auto flags = a_data.find<RE::ENCOUNTER_ZONE_DATA::Flags>(FLAGS_KEY).value();
		if (flags != zoneData.flags) {
			zoneData.flags = flags;
			a_encounterZone->AddChange(RE::CHANGE_TYPE::kEncounterZoneFlags);
		}
	}

	static GameData GetGameData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSEncounterZone* a_encounterZone)
	{
		if (!a_encounterZone) {
			a_vm.PostError(::Internal::Errors::ENCOUNTER_ZONE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto& gameData = a_encounterZone->gameData;

		auto data = GameData();
		data.insert(DETACH_TIME_KEY, gameData.detachTime);
		data.insert(ATTACH_TIME_KEY, gameData.attachTime);
		data.insert(RESET_TIME_KEY, gameData.resetTime);
		data.insert(ZONE_LEVEL_KEY, gameData.zoneLevel);

		return data;
	}

	static void SetGameData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSEncounterZone* a_encounterZone,
		GameData a_data)
	{
		if (!a_encounterZone) {
			a_vm.PostError(::Internal::Errors::ENCOUNTER_ZONE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		auto& gameData = a_encounterZone->gameData;

		gameData.detachTime = a_data.find<std::uint32_t>(DETACH_TIME_KEY).value();
		gameData.attachTime = a_data.find<std::uint32_t>(ATTACH_TIME_KEY).value();
		gameData.resetTime = a_data.find<std::uint32_t>(RESET_TIME_KEY).value();
		gameData.zoneLevel = a_data.find<std::uint16_t>(ZONE_LEVEL_KEY).value();

		a_encounterZone->AddChange(RE::CHANGE_TYPE::kEncounterZoneGameData);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetGameData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetGameData);

		return true;
	}
}