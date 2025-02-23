#pragma once

namespace System::Faction
{
	static constexpr auto SCRIPT_NAME = "System:Faction"sv;

	static constexpr auto FLAGS_KEY = "Flags"sv;
	static constexpr auto EXTERIOR_JAIL_MARKER_KEY = "ExteriorJailMarker"sv;
	static constexpr auto COMPANION_WAIT_MARKER_KEY = "CompanionWaitMarker"sv;
	static constexpr auto STOLEN_ITEMS_CONTAINER_KEY = "StolenItemsContainer"sv;
	static constexpr auto PLAYER_INVENTORY_CONTAINER_KEY = "PlayerInventoryContainer"sv;
	static constexpr auto SHARED_CRIME_FACTIONS_KEY = "SharedCrimeFactions"sv;
	static constexpr auto JAIL_OUTFIT_KEY = "JailOutfit"sv;
	static constexpr auto ARRESTS_KEY = "Arrests"sv;
	static constexpr auto ATTACKS_ON_SIGHT_KEY = "AttacksOnSight"sv;
	static constexpr auto MURDER_VALUE_KEY = "MurderValue"sv;
	static constexpr auto ASSAULT_VALUE_KEY = "AssaultValue"sv;
	static constexpr auto TRESPASS_VALUE_KEY = "TrespassValue"sv;
	static constexpr auto PICKPOCKET_VALUE_KEY = "PickpocketValue"sv;
	static constexpr auto ESCAPE_VALUE_KEY = "EscapeValue"sv;
	static constexpr auto STEAL_MULT_KEY = "StealMult"sv;
	static constexpr auto MERCHANT_TRADE_LIST_KEY = "MerchantTradeList"sv;
	static constexpr auto MERCHANT_CONTAINER_KEY = "MerchantContainer"sv;
	static constexpr auto MERCHANT_START_HOUR_KEY = "MerchantStartHour"sv;
	static constexpr auto MERCHANT_END_HOUR_KEY = "MerchantEndHour"sv;
	static constexpr auto MERCHANT_RADIUS_KEY = "MerchantRadius"sv;
	static constexpr auto BUYS_STOLEN_ITEMS_KEY = "BuysStolenItems"sv;
	static constexpr auto BUYS_NON_STOLEN_ITEMS_KEY = "BuysNonStolenItems"sv;
	static constexpr auto TRADES_EVERYTHING_KEY = "TradesEverything"sv;
	static constexpr auto RELATIONS_KEY = "Relations"sv;
	static constexpr auto OBJECT_KEY = "Object"sv;
	static constexpr auto MODIFIER_KEY = "Modifier"sv;
	static constexpr auto COMBAT_REACTION_KEY = "CombatReaction"sv;

	using Data = RE::BSScript::structure_wrapper<"System:Faction", "Data">;
	using Relation = RE::BSScript::structure_wrapper<"System:Faction", "Relation">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESFaction* a_faction)
	{
		if (!a_faction) {
			a_vm.PostError(::Internal::Errors::FACTION_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto& crimeData = a_faction->crimeData;
		const auto& crimeValues = crimeData.crimevalues;
		const auto& vendorData = a_faction->vendorData;
		const auto& vendorValues = vendorData.vendorValues;

		auto data = Data();
		data.insert(FLAGS_KEY, a_faction->data.flags.underlying());
		data.insert(EXTERIOR_JAIL_MARKER_KEY, crimeData.factionJailMarker);
		data.insert(COMPANION_WAIT_MARKER_KEY, crimeData.factionWaitMarker);
		data.insert(STOLEN_ITEMS_CONTAINER_KEY, crimeData.factionStolenContainer);
		data.insert(PLAYER_INVENTORY_CONTAINER_KEY, crimeData.factionPlayerInventoryContainer);
		data.insert(SHARED_CRIME_FACTIONS_KEY, crimeData.crimeGroup);
		data.insert(JAIL_OUTFIT_KEY, crimeData.jailOutfit);
		data.insert(ARRESTS_KEY, crimeValues.arrest);
		data.insert(ATTACKS_ON_SIGHT_KEY, crimeValues.attackOnSight);
		data.insert(MURDER_VALUE_KEY, crimeValues.murderCrimeGold);
		data.insert(ASSAULT_VALUE_KEY, crimeValues.assaultCrimeGold);
		data.insert(TRESPASS_VALUE_KEY, crimeValues.trespassCrimeGold);
		data.insert(PICKPOCKET_VALUE_KEY, crimeValues.pickpocketCrimeGold);
		data.insert(ESCAPE_VALUE_KEY, crimeValues.escapeCrimeGold);
		data.insert(STEAL_MULT_KEY, crimeValues.stealCrimeGoldMult);
		data.insert(MERCHANT_TRADE_LIST_KEY, vendorData.vendorSellBuyList);
		data.insert(MERCHANT_CONTAINER_KEY, vendorData.merchantContainer);
		data.insert(MERCHANT_START_HOUR_KEY, vendorValues.startHour);
		data.insert(MERCHANT_END_HOUR_KEY, vendorValues.endHour);
		data.insert(MERCHANT_RADIUS_KEY, vendorValues.locationRadius);
		data.insert(BUYS_STOLEN_ITEMS_KEY, vendorValues.buysStolen);
		data.insert(BUYS_NON_STOLEN_ITEMS_KEY, vendorValues.buysNonStolen);
		data.insert(TRADES_EVERYTHING_KEY, vendorValues.notBuySell);

		const auto& oldList = a_faction->reactionList;

		auto newList = std::vector<Relation>();
		newList.reserve(std::distance(oldList.begin(), oldList.end()));

		std::for_each(oldList.begin(), oldList.end(), [&](const RE::GROUP_REACTION* a_reaction) {
			if (!a_reaction) {
				return;
			}

			auto data = Relation();
			data.insert(OBJECT_KEY, a_reaction->form);
			data.insert(MODIFIER_KEY, a_reaction->reaction);
			data.insert(COMBAT_REACTION_KEY, a_reaction->fightReaction);

			newList.push_back(std::move(data));
		});

		data.insert(RELATIONS_KEY, std::move(newList));
		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESFaction* a_faction,
		Data a_data)
	{
		if (!a_faction) {
			a_vm.PostError(::Internal::Errors::FACTION_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		auto& crimeData = a_faction->crimeData;
		auto& crimeValues = crimeData.crimevalues;
		auto& vendorData = a_faction->vendorData;
		auto& vendorValues = vendorData.vendorValues;

		crimeData.factionJailMarker = a_data.find<RE::TESObjectREFR*>(EXTERIOR_JAIL_MARKER_KEY).value_or(nullptr);
		crimeData.factionWaitMarker = a_data.find<RE::TESObjectREFR*>(COMPANION_WAIT_MARKER_KEY).value_or(nullptr);
		crimeData.factionStolenContainer = a_data.find<RE::TESObjectREFR*>(STOLEN_ITEMS_CONTAINER_KEY).value_or(nullptr);
		crimeData.factionPlayerInventoryContainer = a_data.find<RE::TESObjectREFR*>(PLAYER_INVENTORY_CONTAINER_KEY).value_or(nullptr);
		crimeData.crimeGroup = a_data.find<RE::BGSListForm*>(SHARED_CRIME_FACTIONS_KEY).value_or(nullptr);
		crimeData.jailOutfit = a_data.find<RE::BGSOutfit*>(JAIL_OUTFIT_KEY).value_or(nullptr);
		crimeValues.arrest = a_data.find<bool>(ARRESTS_KEY).value();
		crimeValues.attackOnSight = a_data.find<bool>(ATTACKS_ON_SIGHT_KEY).value();
		crimeValues.murderCrimeGold = a_data.find<std::uint16_t>(MURDER_VALUE_KEY).value();
		crimeValues.assaultCrimeGold = a_data.find<std::uint16_t>(ASSAULT_VALUE_KEY).value();
		crimeValues.trespassCrimeGold = a_data.find<std::uint16_t>(TRESPASS_VALUE_KEY).value();
		crimeValues.pickpocketCrimeGold = a_data.find<std::uint16_t>(PICKPOCKET_VALUE_KEY).value();
		crimeValues.escapeCrimeGold = a_data.find<std::uint16_t>(ESCAPE_VALUE_KEY).value();
		crimeValues.stealCrimeGoldMult = a_data.find<float>(STEAL_MULT_KEY).value();
		vendorData.vendorSellBuyList = a_data.find<RE::BGSListForm*>(MERCHANT_TRADE_LIST_KEY).value_or(nullptr);
		vendorData.merchantContainer = a_data.find<RE::TESObjectREFR*>(MERCHANT_CONTAINER_KEY).value_or(nullptr);
		vendorValues.startHour = a_data.find<std::uint16_t>(MERCHANT_START_HOUR_KEY).value();
		vendorValues.endHour = a_data.find<std::uint16_t>(MERCHANT_END_HOUR_KEY).value();
		vendorValues.locationRadius = a_data.find<std::uint32_t>(MERCHANT_RADIUS_KEY).value();
		vendorValues.buysStolen = a_data.find<bool>(BUYS_STOLEN_ITEMS_KEY).value();
		vendorValues.buysNonStolen = a_data.find<bool>(BUYS_NON_STOLEN_ITEMS_KEY).value();
		vendorValues.notBuySell = a_data.find<bool>(TRADES_EVERYTHING_KEY).value();

		const auto newList = a_data.find<std::vector<Relation>>(RELATIONS_KEY).value_or(std::vector<Relation>());
		auto& oldList = a_faction->reactionList;

		for (auto it = oldList.begin(); it != oldList.end(); it++) {
			auto*& reaction = *it;
			if (!reaction) {
				continue;
			}

			delete reaction;
			reaction = nullptr;
		}

		oldList.clear();

		std::ranges::for_each(newList | std::ranges::views::reverse, [&](const Relation& a_relation) {
			if (!a_relation) {
				return;
			}

			auto* reaction = new RE::GROUP_REACTION();

			reaction->form = a_relation.find<RE::TESFaction*>(OBJECT_KEY).value_or(nullptr);
			reaction->reaction = a_relation.find<std::int32_t>(MODIFIER_KEY).value();
			reaction->fightReaction = a_relation.find<RE::FIGHT_REACTION>(COMBAT_REACTION_KEY).value_or(RE::FIGHT_REACTION::kNeutral);

			oldList.emplace_front(reaction);
		});

		a_faction->AddChange(RE::CHANGE_TYPE::kFactionReactions);
		a_faction->AddChange(RE::CHANGE_TYPE::kFactionVendorData);

		const auto flags = a_data.find<RE::FACTION_DATA::Flags>(FLAGS_KEY).value();
		if (flags != a_faction->data.flags) {
			a_faction->data.flags = flags;
			a_faction->AddChange(RE::CHANGE_TYPE::kFactionFlags);
		}
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}