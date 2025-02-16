#pragma once

#include "Internal/Callbacks/CrosshairRefHandler.hpp"
#include "Internal/Callbacks/GameStartedHandler.hpp"

#include "Internal/Bethesda/IniSettings.hpp"

namespace System::Game
{
	static constexpr auto SCRIPT_NAME = "System:Game"sv;

	static constexpr auto FLAGS_KEY = "Flags"sv;
	static constexpr auto NAME_KEY = "Name"sv;
	static constexpr auto INDEX_KEY = "Index"sv;

	using ModInfo = RE::BSScript::structure_wrapper<"System:Game", "ModInfo">;

	static ::Internal::Versions::Version GetVersion(std::monostate)
	{
		const auto version = REL::Module::get().version();
		return ::Internal::Versions::MakeVersion(version);
	}

	static bool IsOldGen(std::monostate)
	{
		return REL::Module::IsF4();
	}

	static bool IsNextGen(std::monostate)
	{
		return REL::Module::IsNG();
	}

	static bool IsPostGameStart(std::monostate)
	{
		return ::Internal::GameStartedHandler::IsPostGameStart;
	}

	static bool IsModLoaded(std::monostate,
		std::string_view a_modName)
	{
		const auto* dataHandler = RE::TESDataHandler::GetSingleton();
		const auto* file = dataHandler->LookupModByName(a_modName);
		return file != nullptr;
	}

	static ModInfo GetModByName(std::monostate,
		std::string_view a_modName)
	{
		const auto* dataHandler = RE::TESDataHandler::GetSingleton();
		const auto* file = dataHandler->LookupModByName(a_modName);
		if (!file) {
			return ModInfo();
		}

		auto mod = ModInfo();
		mod.insert(FLAGS_KEY, file->flags.underlying());
		mod.insert(NAME_KEY, std::string_view{ file->filename });
		mod.insert(INDEX_KEY, file->compileIndex);

		return mod;
	}

	static std::vector<ModInfo> GetLoadedMods(std::monostate)
	{
		const auto* dataHandler = RE::TESDataHandler::GetSingleton();
		const auto& files = dataHandler->files;

		auto mods = std::vector<ModInfo>();
		mods.reserve(std::distance(files.begin(), files.end()));

		for (auto it = files.begin(); it != files.end(); it++) {
			const auto* file = *it;
			if (!file) {
				continue;
			}

			auto mod = ModInfo();
			mod.insert(FLAGS_KEY, file->flags.underlying());
			mod.insert(NAME_KEY, std::string_view{ file->filename });
			mod.insert(INDEX_KEY, file->compileIndex);

			mods.push_back(std::move(mod));
		}

		return mods;
	}

	static std::vector<std::string_view> GetINISections(std::monostate)
	{
		const auto lock = std::shared_lock{ ::Internal::IniSettings::GetMutex() };
		return ::Internal::IniSettings::GetSections();
	}

	static std::vector<std::string_view> GetINIKeys(std::monostate,
		std::string_view a_section)
	{
		const auto lock = std::shared_lock{ ::Internal::IniSettings::GetMutex() };
		return ::Internal::IniSettings::GetKeys(a_section);
	}

	static bool ContainsINISection(std::monostate,
		std::string_view a_section)
	{
		const auto lock = std::shared_lock{ ::Internal::IniSettings::GetMutex() };
		return ::Internal::IniSettings::ContainsSection(a_section);
	}

	static bool ContainsINIKey(std::monostate,
		std::string_view a_section,
		std::string_view a_key)
	{
		const auto lock = std::shared_lock{ ::Internal::IniSettings::GetMutex() };
		return ::Internal::IniSettings::ContainsKey(a_section, a_key);
	}

	static bool GetINIBool(std::monostate,
		std::string_view a_section,
		std::string_view a_key,
		bool a_default)
	{
		const auto lock = std::shared_lock{ ::Internal::IniSettings::GetMutex() };

		const auto* setting = ::Internal::IniSettings::GetSetting(a_section, a_key);
		if (!setting || setting->GetType() != RE::Setting::SETTING_TYPE::kBinary) {
			return a_default;
		}

		return setting->GetBinary();
	}

	static bool SetINIBool(std::monostate,
		std::string_view a_section,
		std::string_view a_key,
		bool a_value)
	{
		const auto lock = std::unique_lock{ ::Internal::IniSettings::GetMutex() };

		auto* setting = ::Internal::IniSettings::GetSetting(a_section, a_key);
		if (!setting || setting->GetType() != RE::Setting::SETTING_TYPE::kBinary) {
			return false;
		}

		setting->SetBinary(a_value);
		return true;
	}

	static char GetINIChar(std::monostate,
		std::string_view a_section,
		std::string_view a_key,
		char a_default)
	{
		const auto lock = std::shared_lock{ ::Internal::IniSettings::GetMutex() };

		const auto* setting = ::Internal::IniSettings::GetSetting(a_section, a_key);
		if (!setting) {
			return a_default;
		}

		switch (setting->GetType()) {
			case RE::Setting::SETTING_TYPE::kChar:
				return setting->GetChar();
			case RE::Setting::SETTING_TYPE::kUChar:
				return setting->GetUChar();
			default:
				return a_default;
		}
	}

	static bool SetINIChar(std::monostate,
		std::string_view a_section,
		std::string_view a_key,
		char a_value)
	{
		const auto lock = std::unique_lock{ ::Internal::IniSettings::GetMutex() };

		auto* setting = ::Internal::IniSettings::GetSetting(a_section, a_key);
		if (!setting) {
			return false;
		}

		switch (setting->GetType()) {
			case RE::Setting::SETTING_TYPE::kChar:
				setting->SetChar(a_value);
				break;
			case RE::Setting::SETTING_TYPE::kUChar:
				setting->SetUChar(a_value);
				break;
			default:
				return false;
		}

		return true;
	}

	static std::int32_t GetINIInt(std::monostate,
		std::string_view a_section,
		std::string_view a_key,
		std::int32_t a_default)
	{
		const auto lock = std::shared_lock{ ::Internal::IniSettings::GetMutex() };

		const auto* setting = ::Internal::IniSettings::GetSetting(a_section, a_key);
		if (!setting) {
			return a_default;
		}

		switch (setting->GetType()) {
			case RE::Setting::SETTING_TYPE::kInt:
				return setting->GetInt();
			case RE::Setting::SETTING_TYPE::kUInt:
				return setting->GetUInt();
			default:
				return a_default;
		}
	}

	static bool SetINIInt(std::monostate,
		std::string_view a_section,
		std::string_view a_key,
		std::int32_t a_value)
	{
		const auto lock = std::unique_lock{ ::Internal::IniSettings::GetMutex() };

		auto* setting = ::Internal::IniSettings::GetSetting(a_section, a_key);
		if (!setting) {
			return false;
		}

		switch (setting->GetType()) {
			case RE::Setting::SETTING_TYPE::kInt:
				setting->SetInt(a_value);
				break;
			case RE::Setting::SETTING_TYPE::kUInt:
				setting->SetUInt(a_value);
				break;
			default:
				return false;
		}

		return true;
	}

	static float GetINIFloat(std::monostate,
		std::string_view a_section,
		std::string_view a_key,
		float a_default)
	{
		const auto lock = std::shared_lock{ ::Internal::IniSettings::GetMutex() };

		const auto* setting = ::Internal::IniSettings::GetSetting(a_section, a_key);
		if (!setting || setting->GetType() != RE::Setting::SETTING_TYPE::kFloat) {
			return a_default;
		}

		return setting->GetFloat();
	}

	static bool SetINIFloat(std::monostate,
		std::string_view a_section,
		std::string_view a_key,
		float a_value)
	{
		const auto lock = std::unique_lock{ ::Internal::IniSettings::GetMutex() };

		auto* setting = ::Internal::IniSettings::GetSetting(a_section, a_key);
		if (!setting || setting->GetType() != RE::Setting::SETTING_TYPE::kFloat) {
			return false;
		}

		setting->SetFloat(a_value);
		return true;
	}

	static std::string GetINIString(std::monostate,
		std::string_view a_section,
		std::string_view a_key,
		std::string_view a_default)
	{
		const auto lock = std::shared_lock{ ::Internal::IniSettings::GetMutex() };

		const auto* setting = ::Internal::IniSettings::GetSetting(a_section, a_key);
		if (!setting || setting->GetType() != RE::Setting::SETTING_TYPE::kString) {
			return std::string(a_default);
		}

		return std::string{ setting->GetString() };
	}

	static bool SetINIString(std::monostate,
		std::string_view a_section,
		std::string_view a_key,
		std::string_view a_value)
	{
		const auto lock = std::unique_lock{ ::Internal::IniSettings::GetMutex() };

		auto* setting = ::Internal::IniSettings::GetSetting(a_section, a_key);
		if (!setting || setting->GetType() != RE::Setting::SETTING_TYPE::kString) {
			return false;
		}

		auto oldString = setting->GetString();
		RE::free(reinterpret_cast<void*>(const_cast<char*>(oldString.data())));

		auto* newString = RE::calloc<char>(a_value.size() + sizeof(char));
		std::ranges::copy(a_value, newString);

		setting->SetString(newString);
		return true;
	}

	static ::Internal::Colors::Color GetINIColor(std::monostate,
		std::string_view a_section,
		std::string_view a_key)
	{
		const auto lock = std::shared_lock{ ::Internal::IniSettings::GetMutex() };

		const auto* setting = ::Internal::IniSettings::GetSetting(a_section, a_key);
		if (!setting) {
			return nullptr;
		}

		switch (setting->GetType()) {
			case RE::Setting::SETTING_TYPE::kRGB: {
				const auto rgb = setting->GetRGB();
				return ::Internal::Colors::MakeColor(rgb[0], rgb[1], rgb[2]);
			}
			case RE::Setting::SETTING_TYPE::kRGBA: {
				const auto rgba = setting->GetRGBA();
				return ::Internal::Colors::MakeColor(rgba[0], rgba[1], rgba[2], rgba[3]);
			}
			default: {
				return nullptr;
			}
		}
	}

	static bool SetINIColor(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_section,
		std::string_view a_key,
		::Internal::Colors::Color a_value)
	{
		if (!a_value) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto lock = std::unique_lock{ ::Internal::IniSettings::GetMutex() };

		auto* setting = ::Internal::IniSettings::GetSetting(a_section, a_key);
		if (!setting) {
			return false;
		}

		switch (setting->GetType()) {
			case RE::Setting::SETTING_TYPE::kRGB: {
				const auto&& [r, g, b, _] = ::Internal::Colors::GetColor(a_value);
				const auto rgb = std::array<std::uint8_t, 3>{ r, g, b };

				setting->SetRGB(rgb);
				break;
			}
			case RE::Setting::SETTING_TYPE::kRGBA: {
				const auto&& [r, g, b, a] = ::Internal::Colors::GetColor(a_value);
				const auto rgba = std::array<std::uint8_t, 4>{ r, g, b, a };

				setting->SetRGBA(rgba);
				break;
			}
			default: {
				return false;
			}
		}

		return true;
	}

	static bool SaveINISetting(std::monostate,
		std::string_view a_section,
		std::string_view a_key)
	{
		const auto lock = std::unique_lock{ ::Internal::IniSettings::GetMutex() };
		return ::Internal::IniSettings::SaveSetting(a_section, a_key);
	}

	static RE::TESObjectREFR* GetCurrentCrosshairRef(std::monostate)
	{
		const auto* refHandler = ::Internal::CrosshairRefHandler::GetSingleton();
		const auto refHandle = refHandler->GetCurrentRef();
		return refHandle ? refHandle.get().get() : nullptr;
	}

	static RE::TESObjectREFR* GetCurrentCommandTarget(std::monostate)
	{
		const auto* player = RE::PlayerCharacter::GetSingleton();
		return player->commandTarget;
	}

	static RE::TESObjectREFR* GetLastUsedPowerArmor(std::monostate)
	{
		const auto* player = RE::PlayerCharacter::GetSingleton();
		const auto refHandle = player->lastUsedPowerArmor;
		return refHandle ? refHandle.get().get() : nullptr;
	}

	static std::vector<RE::TESObjectREFR*> GetAllMapMarkers(std::monostate)
	{
		const auto* player = RE::PlayerCharacter::GetSingleton();
		const auto& markers = player->currentMapMarkers;

		auto refs = std::vector<RE::TESObjectREFR*>();
		refs.reserve(markers.size());

		for (const auto marker : markers) {
			auto* ref = marker ? marker.get().get() : nullptr;
			if (ref) {
				refs.push_back(ref);
			}
		}

		return refs;
	}

	static std::vector<RE::Actor*> GetActorsByProcessLevel(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::ProcessLists::PROCESS_LEVEL a_level,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects)
	{
		constexpr auto MIN_PROCESS_LEVEL = std::to_underlying(RE::ProcessLists::PROCESS_LEVEL::kProcessLevel_Min);
		constexpr auto MAX_PROCESS_LEVEL = std::to_underlying(RE::ProcessLists::PROCESS_LEVEL::kProcessLevel_Max);

		if (a_level < MIN_PROCESS_LEVEL || a_level > MAX_PROCESS_LEVEL) {
			a_vm.PostError(fmt::format("The process level {} is out of range ({} - {})"sv,
							   std::to_underlying(a_level), MIN_PROCESS_LEVEL, MAX_PROCESS_LEVEL),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto filter = ::Internal::VarFilter{ a_includedObjects, a_excludedObjects };
		const auto isEmpty = filter.IsEmpty();

		auto actors = std::vector<RE::Actor*>();
		RE::ProcessLists::GetSingleton()->ForEachActorInProcess(a_level, [&](RE::Actor* a_actor) {
			if (isEmpty || filter.Filter(a_actor)) {
				actors.push_back(a_actor);
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return actors;
	}

	static std::vector<RE::TESObjectREFR*> FindAllRefs(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects)
	{
		const auto filter = ::Internal::VarFilter{ a_includedObjects, a_excludedObjects };
		const auto isEmpty = filter.IsEmpty();

		auto refs = std::vector<RE::TESObjectREFR*>();
		RE::TES::GetSingleton()->ForEachRef([&](RE::TESObjectREFR* a_ref) {
			if (isEmpty || filter.Filter(a_ref)) {
				refs.push_back(a_ref);
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return refs;
	}

	static std::vector<RE::TESObjectREFR*> FindAllRefsInRange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::Vectors::Vector3 a_center,
		float a_radius,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects)
	{
		if (!a_center) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		if (a_radius <= 0.0f) {
			return {};
		}

		const auto filter = ::Internal::VarFilter{ a_includedObjects, a_excludedObjects };
		const auto isEmpty = filter.IsEmpty();

		const auto&& [x, y, z] = ::Internal::Vectors::GetVector3(a_center);
		const auto center = RE::NiPoint3{ x, y, z };

		auto refs = std::vector<RE::TESObjectREFR*>();
		RE::TES::GetSingleton()->ForEachRefInRange(center, a_radius, [&](RE::TESObjectREFR* a_ref) {
			if (isEmpty || filter.Filter(a_ref)) {
				refs.push_back(a_ref);
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return refs;
	}

	static std::vector<RE::TESObjectREFR*> FindAllRefsInRangeFromRef(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_originRef,
		float a_radius,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects)
	{
		if (!a_originRef) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		if (a_radius <= 0.0f) {
			return {};
		}

		const auto filter = ::Internal::VarFilter{ a_includedObjects, a_excludedObjects };
		const auto isEmpty = filter.IsEmpty();

		auto refs = std::vector<RE::TESObjectREFR*>();
		RE::TES::GetSingleton()->ForEachRefInRange(a_originRef, a_radius, [&](RE::TESObjectREFR* a_ref) {
			if (a_ref != a_originRef && (isEmpty || filter.Filter(a_ref))) {
				refs.push_back(a_ref);
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return refs;
	}

	static std::vector<RE::TESObjectCELL*> GetLoadedCells(std::monostate)
	{
		const auto* tes = RE::TES::GetSingleton();

		auto* interior = tes->interiorCell;
		if (interior) {
			return { interior };
		}

		const auto* grid = tes->gridCells;
		if (!grid) {
			return {};
		}

		const auto length = grid->length;

		auto cells = std::vector<RE::TESObjectCELL*>();
		cells.reserve(length);

		for (auto i = 0ui32; i < length; i++) {
			auto* cell = grid->cells[i];
			if (cell) {
				cells.push_back(cell);
			}
		}

		return cells;
	}

	static RE::TESWorldSpace* GetCurrentWorldSpace(std::monostate)
	{
		const auto* tes = RE::TES::GetSingleton();

		auto* worldSpace = tes->worldSpace;
		if (worldSpace) {
			return worldSpace;
		}

		const auto* interior = tes->interiorCell;
		if (interior) {
			return interior->worldSpace;
		}

		return nullptr;
	}

	static void PlayMenuSound(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSSoundDescriptorForm* a_sound)
	{
		if (!a_sound) {
			a_vm.PostError(::Internal::Errors::SOUND_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		RE::UIUtils::PlayMenuSound(a_sound->GetFormEditorID());
	}

	static void PlayMenuSoundByID(std::monostate,
		std::string_view a_editorID)
	{
		RE::UIUtils::PlayMenuSound(a_editorID.data());
	}

	static void PlayPipBoySound(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSSoundDescriptorForm* a_sound)
	{
		if (!a_sound) {
			a_vm.PostError(::Internal::Errors::SOUND_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		RE::UIUtils::PlayPipboySound(a_sound->GetFormEditorID());
	}

	static void PlayPipBoySoundByID(std::monostate,
		std::string_view a_editorID)
	{
		RE::UIUtils::PlayPipboySound(a_editorID.data());
	}

	static bool IsHolotapePlaying(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSNote* a_holotape)
	{
		if (!a_holotape) {
			a_vm.PostError(::Internal::Errors::HOLOTAPE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* player = RE::PlayerCharacter::GetSingleton();
		return player->IsHolotapePlaying(a_holotape);
	}

	static void PlayHolotape(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSNote* a_holotape)
	{
		if (!a_holotape) {
			a_vm.PostError(::Internal::Errors::HOLOTAPE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		auto* player = RE::PlayerCharacter::GetSingleton();
		player->PlayHolotape(a_holotape);
	}

	static bool PauseHolotape(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSNote* a_holotape)
	{
		if (!a_holotape) {
			a_vm.PostError(::Internal::Errors::HOLOTAPE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* player = RE::PlayerCharacter::GetSingleton();
		if (!player->IsHolotapePlaying(a_holotape)) {
			return false;
		}

		player->PauseHolotape(a_holotape);
		return true;
	}

	static std::int32_t GetCameraState(std::monostate)
	{
		const auto* camera = RE::PlayerCamera::GetSingleton();
		const auto state = camera->currentState;
		return state ? state->id.underlying() : -1;
	}

	static bool SetCameraState(std::monostate,
		RE::CameraState a_state)
	{
		const auto* camera = RE::PlayerCamera::GetSingleton();
		const auto state = camera->GetState(a_state);

		if (!state) {
			return false;
		}

		camera->SetState(state.get());
		return true;
	}

	static bool GetIsTimeFrozen(std::monostate)
	{
		const auto* main = RE::Main::GetSingleton();
		return main->freezeTime;
	}

	static void SetIsTimeFrozen(std::monostate,
		bool a_freeze)
	{
		auto* main = RE::Main::GetSingleton();
		main->freezeTime = a_freeze;
	}

	static std::uint8_t GetPerkPoints(std::monostate)
	{
		const auto* player = RE::PlayerCharacter::GetSingleton();
		return static_cast<std::uint8_t>(player->perkCount);
	}

	static void SetPerkPoints(std::monostate,
		std::uint8_t a_value)
	{
		auto* player = RE::PlayerCharacter::GetSingleton();
		auto& count = player->perkCount;

		auto oldValue = count;
		auto newValue = a_value;

		count = newValue;

		if (newValue != oldValue && !REL::Module::IsNG()) {
			auto event = RE::PerkPointIncreaseEvent(newValue - oldValue);
			RE::PerkPointIncreaseEvent::GetEventSource()->Notify(event);
		}
	}

	static void ModPerkPoints(std::monostate,
		std::int8_t a_amount)
	{
		auto* player = RE::PlayerCharacter::GetSingleton();
		auto& count = player->perkCount;

		auto oldValue = count;
		auto newValue = static_cast<std::int8_t>(oldValue + a_amount);

		count += newValue;

		if (newValue != oldValue && !REL::Module::IsNG()) {
			auto event = RE::PerkPointIncreaseEvent(newValue - oldValue);
			RE::PerkPointIncreaseEvent::GetEventSource()->Notify(event);
		}
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetVersion);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsOldGen);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsNextGen);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsPostGameStart);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsModLoaded);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetModByName);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetLoadedMods);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetINISections);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetINIKeys);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ContainsINISection);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ContainsINIKey);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetINIBool);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetINIBool);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetINIChar);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetINIChar);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetINIInt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetINIInt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetINIFloat);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetINIFloat);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetINIString);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetINIString);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetINIColor);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetINIColor);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SaveINISetting);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetCurrentCrosshairRef);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetCurrentCommandTarget);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetLastUsedPowerArmor);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetAllMapMarkers);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetActorsByProcessLevel);
		BIND_METHOD(a_vm, SCRIPT_NAME, FindAllRefs);
		BIND_METHOD(a_vm, SCRIPT_NAME, FindAllRefsInRange);
		BIND_METHOD(a_vm, SCRIPT_NAME, FindAllRefsInRangeFromRef);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetLoadedCells);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetCurrentWorldSpace);
		BIND_METHOD(a_vm, SCRIPT_NAME, PlayMenuSound);
		BIND_METHOD(a_vm, SCRIPT_NAME, PlayPipBoySound);
		BIND_METHOD(a_vm, SCRIPT_NAME, PlayMenuSoundByID);
		BIND_METHOD(a_vm, SCRIPT_NAME, PlayPipBoySoundByID);
		BIND_METHOD(a_vm, SCRIPT_NAME, IsHolotapePlaying);
		BIND_METHOD(a_vm, SCRIPT_NAME, PlayHolotape);
		BIND_METHOD(a_vm, SCRIPT_NAME, PauseHolotape);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetCameraState);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetCameraState);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetIsTimeFrozen);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetIsTimeFrozen);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetPerkPoints);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetPerkPoints);
		BIND_METHOD(a_vm, SCRIPT_NAME, ModPerkPoints);

		return true;
	}
}
