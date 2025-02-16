#include "Internal/Bethesda/VarFilter.hpp"

namespace Internal
{
	[[nodiscard]] static VarFilter::Entry Setup(const std::vector<const RE::BSScript::Variable*>& a_values)
	{
		auto entry = VarFilter::Entry();
		for (const auto* value : a_values) {
			if (!value || !*value) {
				continue;
			}

			if (value->is<std::int32_t>()) {
				const auto formType = static_cast<RE::ENUM_FORMTYPE>(RE::BSScript::get<std::int32_t>(*value));
				entry.formTypes.insert(formType);
				continue;
			}

			if (value->is<RE::BSFixedString>()) {
				const auto modName = RE::BSScript::get<RE::BSFixedString>(*value);
				entry.modNames.insert(modName);
				continue;
			}

			const auto* form = RE::BSScript::detail::UnpackVariable<RE::TESForm*>(*value);
			if (form) {
				entry.forms.insert(form);
			}
		}

		return entry;
	}

	[[nodiscard]] static bool Filter(const RE::TESForm* a_entry, const RE::TESForm* a_filter)
	{
		if (a_entry == a_filter) {
			return true;
		}

		if (!a_entry || !a_filter) {
			return false;
		}

		switch (a_filter->GetFormType()) {
			case RE::BGSKeyword::FORMTYPE: {
				const auto* keywordHolder = a_entry->As<RE::IKeywordFormBase>();
				if (keywordHolder) {
					const auto* keyword = a_filter->As<RE::BGSKeyword>();
					return keywordHolder->HasKeyword(keyword);
				}
				break;
			}
			case RE::TESFaction::FORMTYPE: {
				const auto* faction = a_filter->As<RE::TESFaction>();

				const auto* actor = a_entry->As<RE::Actor>();
				if (actor) {
					return actor->IsInFaction(faction);
				}

				const auto* npc = a_entry->As<RE::TESNPC>();
				if (npc) {
					return npc->IsInFaction(faction);
				}
				break;
			}
			case RE::TESRace::FORMTYPE: {
				const auto* race = a_filter->As<RE::TESRace>();

				const auto* actor = a_entry->As<RE::Actor>();
				if (actor) {
					return actor->race == race;
				}

				const auto* raceHolder = a_entry->As<RE::TESRaceForm>();
				if (raceHolder) {
					return raceHolder->formRace == race;
				}
				break;
			}
			case RE::TESNPC::FORMTYPE: {
				const auto* actor = a_entry->As<RE::Actor>();
				if (!actor) {
					break;
				}

				const auto* npc = a_filter->As<RE::TESNPC>();

				const auto extraList = actor->extraList;
				if (extraList) {
					const auto lock = RE::BSAutoReadLock{ extraList->extraRWLock };

					const auto* leveledNPC = extraList->GetByType<RE::ExtraLeveledCreature>();
					if (leveledNPC) {
						return leveledNPC->originalBase == npc;
					}
				}

				return actor->GetActorBase() == npc;
			}
			case RE::BGSListForm::FORMTYPE: {
				using Result = RE::BSContainer::ForEachResult;

				const auto* list = a_filter->As<RE::BGSListForm>();
				return list && list->ForEachForm([&](const RE::TESForm* a_element) {
					return Filter(a_entry, a_element) ? Result::kStop : Result::kContinue;
				}) == Result::kStop;
			}
			default: {
				const auto* ref = a_entry->As<RE::TESObjectREFR>();
				if (!ref) {
					break;
				}

				return ref->GetBaseObject() == a_filter;
			}
		}

		return false;
	}

	VarFilter::VarFilter(
		const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
		const std::vector<const RE::BSScript::Variable*>& a_excludedObjects) :
		_includedEntries(Setup(a_includedObjects)),
		_excludedEntries(Setup(a_excludedObjects))
	{
	}

	bool VarFilter::IsEmpty() const noexcept
	{
		return _includedEntries.formTypes.empty() &&
			   _includedEntries.modNames.empty() &&
			   _includedEntries.forms.empty() &&
			   _excludedEntries.formTypes.empty() &&
			   _excludedEntries.modNames.empty() &&
			   _excludedEntries.forms.empty();
	}

	const VarFilter::Entry& VarFilter::GetIncludedEntries() const noexcept
	{
		return _includedEntries;
	}

	const VarFilter::Entry& VarFilter::GetExcludedEntries() const noexcept
	{
		return _excludedEntries;
	}

	bool VarFilter::Filter(const RE::TESForm* a_form) const
	{
		if (!FilterByFormTypes(a_form, _includedEntries.formTypes, _excludedEntries.formTypes) ||
			!FilterByModNames(a_form, _includedEntries.modNames, _excludedEntries.modNames)) {
			return false;
		}

		if (_includedEntries.forms.empty() && _excludedEntries.forms.empty()) {
			return true;
		}

		const auto formFilter = [&](const RE::TESForm* a_filter) {
			return Internal::Filter(a_form, a_filter);
		};

		return std::ranges::any_of(_includedEntries.forms, formFilter) &&
			   std::ranges::none_of(_excludedEntries.forms, formFilter);
	}

	bool VarFilter::FilterByFormTypes(const RE::TESForm* a_form,
		const std::unordered_set<RE::ENUM_FORMTYPE>& a_includedFormTypes,
		const std::unordered_set<RE::ENUM_FORMTYPE>& a_excludedFormTypes)
	{
		if (a_includedFormTypes.empty() && a_excludedFormTypes.empty()) {
			return true;
		}

		if (!a_form) {
			return false;
		}

		if (FilterByEnums(a_form->GetFormType(), a_includedFormTypes, a_excludedFormTypes)) {
			return true;
		}

		const auto* ref = a_form->As<RE::TESObjectREFR>();
		if (!ref) {
			return false;
		}

		const auto* baseObject = ref->GetBaseObject();
		if (!baseObject) {
			return false;
		}

		return FilterByEnums(baseObject->GetFormType(), a_includedFormTypes, a_excludedFormTypes);
	}
}
