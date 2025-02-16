#pragma once

namespace System::Perk
{
	static constexpr auto SCRIPT_NAME = "System:Perk"sv;

	static constexpr auto IS_TRAIT_KEY = "IsTrait"sv;
	static constexpr auto IS_PLAYABLE_KEY = "IsPlayable"sv;
	static constexpr auto IS_HIDDEN_KEY = "IsHidden"sv;
	static constexpr auto LEVEL_KEY = "Level"sv;
	static constexpr auto RANK_COUNT_KEY = "RankCount"sv;
	static constexpr auto NEXT_PERK_KEY = "NextPerk"sv;
	static constexpr auto PLAYED_SOUND_KEY = "PlayedSound"sv;
	static constexpr auto INTERFACE_FILE_KEY = "InterfaceFile"sv;
	static constexpr auto ENTRIES_KEY = "Entries"sv;
	static constexpr auto RANK_KEY = "Rank"sv;
	static constexpr auto PRIORITY_KEY = "Priority"sv;

	static constexpr auto OBJECT_KEY = "Object"sv;
	static constexpr auto STAGE_KEY = "Stage"sv;

	static constexpr auto VALUE_ONE_KEY = "Value01"sv;
	static constexpr auto VALUE_TWO_KEY = "Value02"sv;

	static constexpr auto VALUE_KEY = "Value"sv;

	using Data = RE::BSScript::structure_wrapper<"System:Perk", "Data">;
	using Entry = RE::BSScript::structure_wrapper<"System:Perk", "Entry">;
	using QuestEntry = RE::BSScript::structure_wrapper<"System:Perk", "QuestEntry">;
	using ValueTwoEntry = RE::BSScript::structure_wrapper<"System:Perk", "ValueTwoEntry">;
	using ActorValueEntry = RE::BSScript::structure_wrapper<"System:Perk", "ActorValueEntry">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto& perkData = a_perk->data;

		auto data = Data();
		data.insert(IS_TRAIT_KEY, perkData.trait);
		data.insert(IS_PLAYABLE_KEY, perkData.playable);
		data.insert(IS_HIDDEN_KEY, perkData.hidden);
		data.insert(LEVEL_KEY, perkData.level);
		data.insert(RANK_COUNT_KEY, perkData.numRanks);
		data.insert(NEXT_PERK_KEY, a_perk->nextPerk);
		data.insert(PLAYED_SOUND_KEY, a_perk->sound);
		data.insert(INTERFACE_FILE_KEY, a_perk->swfFile);

		auto entries = std::vector<Entry>();
		entries.reserve(a_perk->perkEntries.size());

		for (const auto* perkEntry : a_perk->perkEntries) {
			auto entry = Entry();
			entry.insert(RANK_KEY, perkEntry->header.rank);
			entry.insert(PRIORITY_KEY, perkEntry->header.priority);

			entries.push_back(std::move(entry));
		}

		data.insert(ENTRIES_KEY, std::move(entries));

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk,
		Data a_data)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		auto& perkData = a_perk->data;

		perkData.trait = a_data.find<bool>(IS_TRAIT_KEY).value();
		perkData.playable = a_data.find<bool>(IS_PLAYABLE_KEY).value();
		perkData.hidden = a_data.find<bool>(IS_HIDDEN_KEY).value();
		perkData.level = a_data.find<std::int8_t>(LEVEL_KEY).value();
		perkData.numRanks = a_data.find<std::int8_t>(RANK_COUNT_KEY).value();
		a_perk->nextPerk = a_data.find<RE::BGSPerk*>(NEXT_PERK_KEY).value_or(nullptr);
		a_perk->sound = a_data.find<RE::BGSSoundDescriptorForm*>(PLAYED_SOUND_KEY).value_or(nullptr);
		a_perk->swfFile = a_data.find<RE::BSFixedStringCS>(INTERFACE_FILE_KEY).value();

		const auto entries = a_data.find<std::vector<Entry>>(ENTRIES_KEY).value_or(std::vector<Entry>());
		const auto maxIndex = std::min(a_perk->perkEntries.size(), static_cast<std::uint32_t>(perkData.numRanks));

		for (auto i = 0ui32; i < maxIndex; i++) {
			const auto& entry = entries[i];

			auto* perkEntry = a_perk->perkEntries[i];
			if (!perkEntry) {
				continue;
			}

			perkEntry->header.rank = entry.find<std::uint8_t>(RANK_KEY).value();
			perkEntry->header.priority = entry.find<std::uint8_t>(PRIORITY_KEY).value();
		}
	}

	static RE::PERK_ENTRY_TYPE GetNthEntryType(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk,
		std::int32_t a_index)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return static_cast<RE::PERK_ENTRY_TYPE>(-1);
		}

		const auto maxIndex = static_cast<std::int32_t>(a_perk->perkEntries.size() - 1);
		if (a_index < 0 || a_index > maxIndex) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_index, 0, maxIndex),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return static_cast<RE::PERK_ENTRY_TYPE>(-1);
		}

		const auto* perkEntry = a_perk->perkEntries[a_index];
		return perkEntry->GetType();
	}

	static RE::BGSEntryPointFunctionData::FunctionType GetNthEntryFunctionType(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk,
		std::int32_t a_index)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return RE::BGSEntryPointFunctionData::FunctionType::kInvalid;
		}

		const auto maxIndex = static_cast<std::int32_t>(a_perk->perkEntries.size() - 1);
		if (a_index < 0 || a_index > maxIndex) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_index, 0, maxIndex),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return RE::BGSEntryPointFunctionData::FunctionType::kInvalid;
		}

		const auto* perkEntry = a_perk->perkEntries[a_index];
		const auto* perkEntryPoint = RE::fallout_cast<const RE::BGSEntryPointPerkEntry*>(perkEntry);
		if (!perkEntryPoint || !perkEntryPoint->functionData) {
			return RE::BGSEntryPointFunctionData::FunctionType::kInvalid;
		}

		return perkEntryPoint->functionData->GetType();
	}

	static QuestEntry GetNthQuestEntry(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk,
		std::int32_t a_index)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto maxIndex = static_cast<std::int32_t>(a_perk->perkEntries.size() - 1);
		if (a_index < 0 || a_index > maxIndex) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_index, 0, maxIndex),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto* perkEntry = a_perk->perkEntries[a_index];
		const auto* perkQuestEntry = RE::fallout_cast<const RE::BGSQuestPerkEntry*>(perkEntry);

		if (!perkQuestEntry) {
			return nullptr;
		}

		auto entry = QuestEntry();
		entry.insert(OBJECT_KEY, perkQuestEntry->quest);
		entry.insert(STAGE_KEY, perkQuestEntry->stage);

		return entry;
	}

	static bool SetNthQuestEntry(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk,
		std::int32_t a_index,
		QuestEntry a_entry)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
		}

		if (!a_entry) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto maxIndex = static_cast<std::int32_t>(a_perk->perkEntries.size() - 1);
		if (a_index < 0 || a_index > maxIndex) {
			a_vm.PostError(fmt::format(::Internal::Errors::ENTRY_INDEX_OUT_OF_RANGE, a_index, 0, maxIndex),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* perkEntry = a_perk->perkEntries[a_index];
		auto* questEntry = RE::fallout_cast<RE::BGSQuestPerkEntry*>(perkEntry);

		if (!questEntry) {
			return false;
		}

		questEntry->quest = a_entry.find<RE::TESQuest*>(OBJECT_KEY).value_or(nullptr);
		questEntry->stage = a_entry.find<std::int16_t>(STAGE_KEY).value();
		return true;
	}

	static float GetNthEntryValue(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk,
		std::int32_t a_entryIndex)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return 0.0f;
		}

		const auto maxIndex = static_cast<std::int32_t>(a_perk->perkEntries.size() - 1);
		if (a_entryIndex < 0 || a_entryIndex > maxIndex) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_entryIndex, 0, maxIndex),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return 0.0f;
		}

		const auto* perkEntry = a_perk->perkEntries[a_entryIndex];
		const auto* perkEntryPoint = RE::fallout_cast<const RE::BGSEntryPointPerkEntry*>(perkEntry);

		if (!perkEntryPoint) {
			return 0.0f;
		}

		const auto* functionOne = RE::fallout_cast<const RE::BGSEntryPointFunctionDataOneValue*>(perkEntryPoint->functionData);
		return functionOne ? functionOne->value : 0.0f;
	}

	static bool SetNthEntryValue(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk,
		std::int32_t a_entryIndex,
		float a_value)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto maxIndex = static_cast<std::int32_t>(a_perk->perkEntries.size() - 1);
		if (a_entryIndex < 0 || a_entryIndex > maxIndex) {
			a_vm.PostError(fmt::format(::Internal::Errors::ENTRY_INDEX_OUT_OF_RANGE, a_entryIndex, 0, maxIndex),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* perkEntry = a_perk->perkEntries[a_entryIndex];
		auto* perkEntryPoint = RE::fallout_cast<RE::BGSEntryPointPerkEntry*>(perkEntry);

		if (!perkEntryPoint) {
			return false;
		}

		auto* functionOne = RE::fallout_cast<RE::BGSEntryPointFunctionDataOneValue*>(perkEntryPoint->functionData);
		if (!functionOne) {
			return false;
		}

		functionOne->value = a_value;
		return true;
	}

	static ValueTwoEntry GetNthValueTwoEntry(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk,
		std::int32_t a_entryIndex)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto maxIndex = static_cast<std::int32_t>(a_perk->perkEntries.size() - 1);
		if (a_entryIndex < 0 || a_entryIndex > maxIndex) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_entryIndex, 0, maxIndex),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto* perkEntry = a_perk->perkEntries[a_entryIndex];
		const auto* perkEntryPoint = RE::fallout_cast<const RE::BGSEntryPointPerkEntry*>(perkEntry);

		if (!perkEntryPoint) {
			return nullptr;
		}

		const auto* functionTwo = RE::fallout_cast<const RE::BGSEntryPointFunctionDataTwoValue*>(perkEntryPoint->functionData);
		if (!functionTwo) {
			return nullptr;
		}

		auto entry = ValueTwoEntry();
		entry.insert(VALUE_ONE_KEY, functionTwo->value01);
		entry.insert(VALUE_TWO_KEY, functionTwo->value02);

		return entry;
	}

	static bool SetNthValueTwoEntry(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk,
		std::int32_t a_entryIndex,
		ValueTwoEntry a_entry)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
		}

		if (!a_entry) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto maxIndex = static_cast<std::int32_t>(a_perk->perkEntries.size() - 1);
		if (a_entryIndex < 0 || a_entryIndex > maxIndex) {
			a_vm.PostError(fmt::format(::Internal::Errors::ENTRY_INDEX_OUT_OF_RANGE, a_entryIndex, 0, maxIndex),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* perkEntry = a_perk->perkEntries[a_entryIndex];
		auto* perkEntryPoint = RE::fallout_cast<RE::BGSEntryPointPerkEntry*>(perkEntry);

		if (!perkEntryPoint) {
			return false;
		}

		auto* functionTwo = RE::fallout_cast<RE::BGSEntryPointFunctionDataTwoValue*>(perkEntryPoint->functionData);
		if (!functionTwo) {
			return false;
		}

		functionTwo->value01 = a_entry.find<float>(VALUE_ONE_KEY).value();
		functionTwo->value02 = a_entry.find<float>(VALUE_TWO_KEY).value();
		return true;
	}

	static RE::TESLevItem* GetNthEntryLeveledList(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk,
		std::int32_t a_index)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto maxIndex = static_cast<std::int32_t>(a_perk->perkEntries.size() - 1);
		if (a_index < 0 || a_index > maxIndex) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_index, 0, maxIndex),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto* perkEntry = a_perk->perkEntries[a_index];
		const auto* perkEntryPoint = RE::fallout_cast<const RE::BGSEntryPointPerkEntry*>(perkEntry);

		if (!perkEntryPoint) {
			return nullptr;
		}

		const auto* functionData = RE::fallout_cast<const RE::BGSEntryPointFunctionDataLeveledList*>(perkEntryPoint->functionData);
		return functionData ? functionData->leveledList : nullptr;
	}

	static bool SetNthEntryLeveledList(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk,
		std::int32_t a_index,
		RE::TESLevItem* a_leveledList)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto maxIndex = static_cast<std::int32_t>(a_perk->perkEntries.size() - 1);
		if (a_index < 0 || a_index > maxIndex) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_index, 0, maxIndex),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* perkEntry = a_perk->perkEntries[a_index];
		auto* perkEntryPoint = RE::fallout_cast<RE::BGSEntryPointPerkEntry*>(perkEntry);

		if (!perkEntryPoint) {
			return false;
		}

		auto* functionData = RE::fallout_cast<RE::BGSEntryPointFunctionDataLeveledList*>(perkEntryPoint->functionData);
		if (!functionData) {
			return false;
		}

		functionData->leveledList = a_leveledList;
		return true;
	}

	static RE::SpellItem* GetNthEntrySpell(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk,
		std::int32_t a_index)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto maxIndex = static_cast<std::int32_t>(a_perk->perkEntries.size() - 1);
		if (a_index < 0 || a_index > maxIndex) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_index, 0, maxIndex),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto* perkEntry = a_perk->perkEntries[a_index];
		const auto* abilityEntry = RE::fallout_cast<const RE::BGSAbilityPerkEntry*>(perkEntry);

		if (abilityEntry) {
			return abilityEntry->ability;
		}

		const auto* perkEntryPoint = RE::fallout_cast<const RE::BGSEntryPointPerkEntry*>(perkEntry);
		if (!perkEntryPoint) {
			return nullptr;
		}

		const auto* functionDataSpell = RE::fallout_cast<const RE::BGSEntryPointFunctionDataSpellItem*>(perkEntryPoint->functionData);
		if (functionDataSpell) {
			return functionDataSpell->spell;
		}

		const auto* functionDataActivation = RE::fallout_cast<const RE::BGSEntryPointFunctionDataActivateChoice*>(perkEntryPoint->functionData);
		return functionDataActivation ? functionDataActivation->appliedSpell : nullptr;
	}

	static bool SetNthEntrySpell(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk,
		std::int32_t a_index,
		RE::SpellItem* a_spell)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto maxIndex = static_cast<std::int32_t>(a_perk->perkEntries.size() - 1);
		if (a_index < 0 || a_index > maxIndex) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_index, 0, maxIndex),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* perkEntry = a_perk->perkEntries[a_index];
		auto* abilityEntry = RE::fallout_cast<RE::BGSAbilityPerkEntry*>(perkEntry);

		if (abilityEntry) {
			abilityEntry->ability = a_spell;
			return true;
		}

		auto* perkEntryPoint = RE::fallout_cast<RE::BGSEntryPointPerkEntry*>(perkEntry);
		if (!perkEntryPoint) {
			return false;
		}

		auto* functionDataSpell = RE::fallout_cast<RE::BGSEntryPointFunctionDataSpellItem*>(perkEntryPoint->functionData);
		if (functionDataSpell) {
			functionDataSpell->spell = a_spell;
			return true;
		}

		auto* functionDataActivation = RE::fallout_cast<RE::BGSEntryPointFunctionDataActivateChoice*>(perkEntryPoint->functionData);
		if (functionDataActivation) {
			functionDataActivation->appliedSpell = a_spell;
			return true;
		}

		return false;
	}

	static RE::BSFixedString GetNthEntryText(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk,
		std::int32_t a_index)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto maxIndex = static_cast<std::int32_t>(a_perk->perkEntries.size() - 1);
		if (a_index < 0 || a_index > maxIndex) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_index, 0, maxIndex),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto* perkEntry = a_perk->perkEntries[a_index];
		const auto* perkEntryPoint = RE::fallout_cast<const RE::BGSEntryPointPerkEntry*>(perkEntry);

		if (!perkEntryPoint) {
			return {};
		}

		const auto* functionData = RE::fallout_cast<const RE::BGSEntryPointFunctionDataText*>(perkEntryPoint->functionData);
		if (functionData) {
			return functionData->text;
		}

		const auto* functionDataActivation = RE::fallout_cast<const RE::BGSEntryPointFunctionDataActivateChoice*>(perkEntryPoint->functionData);
		if (functionDataActivation) {
			return functionDataActivation->label;
		}

		const auto* functionDataGraph = RE::fallout_cast<const RE::BGSEntryPointFunctionDataBooleanGraphVariable*>(perkEntryPoint->functionData);
		return functionDataGraph ? functionDataGraph->variable : nullptr;
	}

	static bool SetNthEntryText(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk,
		std::int32_t a_index,
		RE::BSFixedString a_text)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto maxIndex = static_cast<std::int32_t>(a_perk->perkEntries.size() - 1);
		if (a_index < 0 || a_index > maxIndex) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_index, 0, maxIndex),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* perkEntry = a_perk->perkEntries[a_index];
		auto* perkEntryPoint = RE::fallout_cast<RE::BGSEntryPointPerkEntry*>(perkEntry);

		if (!perkEntryPoint) {
			return false;
		}

		auto* functionData = RE::fallout_cast<RE::BGSEntryPointFunctionDataText*>(perkEntryPoint->functionData);
		if (functionData) {
			functionData->text = a_text;
			return true;
		}

		auto* functionDataActivation = RE::fallout_cast<RE::BGSEntryPointFunctionDataActivateChoice*>(perkEntryPoint->functionData);
		if (functionDataActivation) {
			functionDataActivation->label = a_text;
			return true;
		}

		auto* functionDataGraph = RE::fallout_cast<RE::BGSEntryPointFunctionDataBooleanGraphVariable*>(perkEntryPoint->functionData);
		if (functionDataGraph) {
			functionDataGraph->variable = a_text;
			return true;
		}

		return false;
	}

	static ActorValueEntry GetNthActorValueEntry(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk,
		std::int32_t a_entryIndex)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto maxIndex = static_cast<std::int32_t>(a_perk->perkEntries.size() - 1);
		if (a_entryIndex < 0 || a_entryIndex > maxIndex) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_entryIndex, 0, maxIndex),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto* perkEntry = a_perk->perkEntries[a_entryIndex];
		const auto* perkEntryPoint = RE::fallout_cast<const RE::BGSEntryPointPerkEntry*>(perkEntry);

		if (!perkEntryPoint) {
			return nullptr;
		}

		auto* functionData = RE::fallout_cast<RE::BGSEntryPointFunctionDataAVAndValue*>(perkEntryPoint->functionData);
		if (!functionData) {
			return nullptr;
		}

		auto entry = ActorValueEntry();
		entry.insert(OBJECT_KEY, functionData->actorValue);
		entry.insert(VALUE_KEY, functionData->value);

		return entry;
	}

	static bool SetNthActorValueEntry(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSPerk* a_perk,
		std::int32_t a_entryIndex,
		ActorValueEntry a_entry)
	{
		if (!a_perk) {
			a_vm.PostError(::Internal::Errors::PERK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
		}

		if (!a_entry) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto maxIndex = static_cast<std::int32_t>(a_perk->perkEntries.size() - 1);
		if (a_entryIndex < 0 || a_entryIndex > maxIndex) {
			a_vm.PostError(fmt::format(::Internal::Errors::ENTRY_INDEX_OUT_OF_RANGE, a_entryIndex, 0, maxIndex),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* perkEntry = a_perk->perkEntries[a_entryIndex];
		auto* perkEntryPoint = RE::fallout_cast<RE::BGSEntryPointPerkEntry*>(perkEntry);

		if (!perkEntryPoint) {
			return false;
		}

		auto* functionData = RE::fallout_cast<RE::BGSEntryPointFunctionDataAVAndValue*>(perkEntryPoint->functionData);
		if (!functionData) {
			return false;
		}

		functionData->actorValue = a_entry.find<RE::ActorValueInfo*>(OBJECT_KEY).value_or(nullptr);
		functionData->value = a_entry.find<float>(VALUE_KEY).value();
		return true;
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetNthEntryType);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetNthEntryFunctionType);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetNthQuestEntry);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetNthQuestEntry);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetNthEntryValue);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetNthEntryValue);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetNthValueTwoEntry);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetNthValueTwoEntry);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetNthEntryLeveledList);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetNthEntryLeveledList);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetNthEntrySpell);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetNthEntrySpell);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetNthEntryText);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetNthEntryText);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetNthActorValueEntry);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetNthActorValueEntry);

		return true;
	}
}
