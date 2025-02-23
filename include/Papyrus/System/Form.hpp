#pragma once

namespace System::Form
{
	static constexpr auto SCRIPT_NAME = "System:Form"sv;

	static constexpr auto OBJECT_KEY = "Object"sv;
	static constexpr auto VALUE_KEY = "Value"sv;

	static constexpr auto PICKUP_SOUND_KEY = "PickupSound"sv;
	static constexpr auto PUTDOWN_SOUND_KEY = "PutdownSound"sv;

	static constexpr auto COLOR_INDEX_KEY = "ColorIndex"sv;

	static constexpr auto MIN_FORM_TYPE = std::to_underlying(RE::ENUM_FORMTYPE::kNONE);
	static constexpr auto MAX_FORM_TYPE = std::to_underlying(RE::ENUM_FORMTYPE::kTotal) - 1;

	using PropertyEntry = RE::BSScript::structure_wrapper<"System:Form", "PropertyEntry">;
	using PickupPutdownSounds = RE::BSScript::structure_wrapper<"System:Form", "PickupPutdownSounds">;
	using MaterialSwapModel = RE::BSScript::structure_wrapper<"System:Form", "MaterialSwapModel">;

	static RE::TESForm* Create(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::int32_t a_type)
	{
		if (a_type < MIN_FORM_TYPE || a_type > MAX_FORM_TYPE) {
			a_vm.PostError(fmt::format(::Internal::Errors::TYPE_ID_OUT_OF_RANGE, a_type, MIN_FORM_TYPE, MAX_FORM_TYPE),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto factories = RE::IFormFactory::GetFormFactories();
		auto* factory = factories[a_type];

		return factory ? factory->DoCreate() : nullptr;
	}

	static RE::TESForm* Copy(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto factories = RE::IFormFactory::GetFormFactories();

		const auto type = a_form->formType.underlying();
		auto* factory = factories[type];

		if (!factory) {
			return nullptr;
		}

		auto* copy = factory->DoCreate();
		if (!copy) {
			return nullptr;
		}

		copy->Copy(a_form);
		return copy;
	}

	static bool HasFlag(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		std::uint32_t a_flag)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return a_form->formFlags & a_flag;
	}

	static std::uint32_t GetFlags(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return 0;
		}

		return a_form->formFlags;
	}

	static void SetFlags(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		std::uint32_t a_flags)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		a_form->formFlags = a_flags;
		a_form->AddChange(RE::CHANGE_TYPE::kFormFlags);
	}

	static void SetFlag(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		std::uint32_t a_flag,
		bool a_set)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (a_set) {
			a_form->formFlags |= a_flag;
		}
		else {
			a_form->formFlags &= ~a_flag;
		}

		a_form->AddChange(RE::CHANGE_TYPE::kFormFlags);
	}

	static bool IsCreated(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return a_form->IsCreated();
	}

	static std::int8_t GetType(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return -1;
		}

		return a_form->formType.underlying();
	}

	static std::int32_t GetTypeByTypeString(std::monostate,
		std::string_view a_type)
	{
		return std::to_underlying(RE::TESForm::GetFormTypeFromString(a_type.data()));
	}

	static std::string_view GetTypeString(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto types = RE::TESForm::GetFormEnumString();
		const auto index = a_form->formType.underlying();

		return types[index].formString;
	}

	static std::string_view GetTypeStringByType(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::int32_t a_type)
	{
		if (a_type < MIN_FORM_TYPE || a_type > MAX_FORM_TYPE) {
			a_vm.PostError(fmt::format(::Internal::Errors::TYPE_ID_OUT_OF_RANGE, a_type, MIN_FORM_TYPE, MAX_FORM_TYPE),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto types = RE::TESForm::GetFormEnumString();
		return types[a_type].formString;
	}

	static RE::BSFixedString GetScriptName(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto formType = a_form->formType.underlying();

		auto objectType = RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo>();
		if (!a_vm.GetScriptObjectType(formType, objectType)) {
			return {};
		}

		return objectType->name;
	}

	static bool IsInMod(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		std::string_view a_modName)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto* dataHandler = RE::TESDataHandler::GetSingleton();
		const auto* file = dataHandler->LookupModByName(a_modName);
		return file ? file->IsFormInMod(a_form->GetFormID()) : false;
	}

	static std::string_view GetModName(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		bool a_lastModified)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto index = a_lastModified ? -1 : 0;
		const auto* file = a_form->GetFile(index);
		return file ? file->filename : nullptr;
	}

	static std::uint32_t GetLocalFormID(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return 0;
		}

		return a_form->GetLocalFormID();
	}

	static RE::BSFixedString GetEditorID(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		return a_form->GetFormEditorID();
	}

	static bool SetEditorID(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		std::string_view a_editorID)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return a_form->SetFormEditorID(a_editorID.data());
	}

	static RE::TESForm* GetByEditorID(std::monostate,
		std::string_view a_editorID)
	{
		// The parameter is not a BSFixedString, due to the possibility that the string is case-sensitive,
		// which causes the hashing in GetFormByEditorID to potentially fail.
		const auto editorID = RE::BSFixedString(a_editorID);
		return RE::TESForm::GetFormByEditorID(editorID);
	}

	static std::vector<RE::TESForm*> GetAllByType(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::int32_t a_type,
		std::string_view a_modName)
	{
		if (a_type < MIN_FORM_TYPE || a_type > MAX_FORM_TYPE) {
			a_vm.PostError(fmt::format(::Internal::Errors::TYPE_ID_OUT_OF_RANGE, a_type, MIN_FORM_TYPE, MAX_FORM_TYPE),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto modFilter = [&](const RE::TESForm* a_form) {
			if (!a_form) {
				return false;
			}

			const auto* file = a_form->GetFile(0);
			if (!file) {
				return false;
			}

			if (a_modName.empty()) {
				return true;
			}

			const auto modName = std::string_view{ file->filename };
			return ::Internal::Comparer::CompareString(a_modName, modName) == std::strong_ordering::equal;
		};

		const auto* dataHandler = RE::TESDataHandler::GetSingleton();

		if (a_type == std::to_underlying(RE::TESObjectCELL::FORMTYPE)) {
			const auto& cells = dataHandler->interiorCells;
			if (a_modName.empty()) {
				return { cells.begin(), cells.end() };
			}

			auto forms = std::vector<RE::TESForm*>();
			std::ranges::copy_if(cells, std::back_inserter(forms), modFilter);
			return forms;
		}

		const auto& formArray = dataHandler->formArrays[a_type];
		if (a_modName.empty()) {
			return { formArray.begin(), formArray.end() };
		}

		auto forms = std::vector<RE::TESForm*>();
		std::ranges::copy_if(formArray, std::back_inserter(forms), modFilter);
		return forms;
	}

	static std::vector<RE::TESForm*> FindAllByType(std::monostate,
		std::vector<RE::TESForm*> a_forms,
		std::int32_t a_type)
	{
		auto forms = std::vector<RE::TESForm*>();
		std::ranges::copy_if(a_forms, std::back_inserter(forms), [&](const RE::TESForm* a_form) {
			return a_form && a_form->formType.underlying() == a_type;
		});

		return forms;
	}

	static std::vector<RE::TESForm*> FindAllByModName(std::monostate,
		std::vector<RE::TESForm*> a_forms,
		std::string_view a_modName)
	{
		auto forms = std::vector<RE::TESForm*>();
		std::ranges::copy_if(a_forms, std::back_inserter(forms), [&](const RE::TESForm* a_form) {
			if (!a_form) {
				return false;
			}

			const auto* file = a_form->GetFile(0);
			if (!file) {
				return false;
			}

			const auto modName = std::string_view{ file->filename };
			return ::Internal::Comparer::CompareString(a_modName, modName) == std::strong_ordering::equal;
		});

		return forms;
	}

	static std::vector<RE::TESForm*> FindAllByFilter(std::monostate,
		std::vector<RE::TESForm*> a_forms,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects)
	{
		const auto filter = ::Internal::VarFilter{ a_includedObjects, a_excludedObjects };

		auto forms = std::vector<RE::TESForm*>();
		std::ranges::copy_if(a_forms, std::back_inserter(forms), [&](const RE::TESForm* a_form) {
			return filter.Filter(a_form);
		});

		return forms;
	}

	static std::vector<RE::TESForm*> FindAllByFlag(std::monostate,
		std::vector<RE::TESForm*> a_forms,
		std::uint32_t a_flag,
		bool a_set)
	{
		auto forms = std::vector<RE::TESForm*>();
		std::ranges::copy_if(a_forms, std::back_inserter(forms), [&](const RE::TESForm* a_form) {
			return a_form && ((a_form->formFlags & a_flag) != 0) == a_set;
		});

		return forms;
	}

	static bool ContainsKeywordString(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		RE::BSFixedString a_editorID)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return 0;
		}

		const auto form = a_form->As<RE::IKeywordFormBase>();
		if (!form) {
			return false;
		}

		auto keywords = RE::BSScrapArray<const RE::BGSKeyword*>();
		form->CollectAllKeywords(keywords, nullptr);

		const auto it = std::ranges::find_if(keywords, [&](const RE::BGSKeyword* a_keyword) noexcept {
			return a_keyword && a_keyword->formEditorID.contains(a_editorID);
		});

		return it != keywords.end();
	}

	static bool HasKeywordString(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		RE::BSFixedString a_editorID)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return 0;
		}

		const auto form = a_form->As<RE::IKeywordFormBase>();
		if (!form) {
			return false;
		}

		auto keywords = RE::BSScrapArray<const RE::BGSKeyword*>();
		form->CollectAllKeywords(keywords, nullptr);

		const auto it = std::ranges::find_if(keywords, [&](const RE::BGSKeyword* a_keyword) noexcept {
			return a_keyword && a_keyword->formEditorID == a_editorID;
		});

		return it != keywords.end();
	}

	static std::vector<RE::BGSKeyword*> GetKeywords(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto form = a_form->As<RE::IKeywordFormBase>();
		if (!form) {
			return {};
		}

		auto keywords = RE::BSScrapArray<const RE::BGSKeyword*>();
		form->CollectAllKeywords(keywords, nullptr);

		auto forms = std::vector<RE::BGSKeyword*>();
		forms.reserve(keywords.size());

		for (const auto* keyword : keywords) {
			forms.push_back(const_cast<RE::BGSKeyword*>(keyword));
		}

		return forms;
	}

	static RE::BGSLocalizedString GetName(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		constexpr auto STRICT_SEARCH = true;

		const auto name = RE::TESFullName::GetFullName(a_form, STRICT_SEARCH);
		if (!name.has_value()) {
			return {};
		}

		return name.value();
	}

	static bool SetName(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		std::string_view a_name)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return RE::TESFullName::SetFullName(a_form, a_name);
	}

	static std::string_view GetDescription(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto* form = a_form->As<RE::TESDescription>();
		if (!form) {
			return {};
		}

		auto description = RE::BSString();
		form->descriptionText.GetDescription(description, a_form);

		return description;
	}

	static std::int32_t GetValue(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return 0;
		}

		return RE::TESValueForm::GetFormValue(a_form).value_or(0);
	}

	static bool SetValue(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		std::int32_t a_value)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return RE::TESValueForm::SetFormValue(a_form, a_value);
	}

	static float GetWeight(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return 0.0f;
		}

		const auto* form = a_form->As<RE::TESWeightForm>();
		return form ? form->weight : 0.0f;
	}

	static bool SetWeight(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		float a_weight)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* form = a_form->As<RE::TESWeightForm>();
		if (!form) {
			return false;
		}

		form->weight = a_weight;
		return true;
	}

	static RE::BGSEquipSlot* GetEquipType(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto* type = a_form->As<RE::BGSEquipType>();
		return type ? type->equipSlot : nullptr;
	}

	static bool SetEquipType(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		RE::BGSEquipSlot* a_slot)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* type = a_form->As<RE::BGSEquipType>();
		if (!type) {
			return false;
		}

		type->equipSlot = a_slot;
		return true;
	}

	static std::vector<PropertyEntry> GetProperties(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto* form = a_form->As<RE::BGSPropertySheet>();
		if (!form) {
			return {};
		}

		const auto* properties = form->properties;
		if (!properties) {
			return {};
		}

		auto entries = std::vector<PropertyEntry>();
		entries.reserve(properties->size());

		for (const auto& [object, value] : *properties) {
			auto entry = PropertyEntry();
			entry.insert(OBJECT_KEY, object->As<RE::ActorValueInfo>());
			entry.insert(VALUE_KEY, value.f);

			entries.push_back(std::move(entry));
		}

		return entries;
	}

	static bool SetProperties(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		std::vector<PropertyEntry> a_entries)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* form = a_form->As<RE::BGSPropertySheet>();
		if (!form) {
			return false;
		}

		auto*& properties = form->properties;

		if (!properties) {
			properties = new RE::BSTArray<RE::BSTTuple<RE::TESForm*, RE::BGSTypedFormValuePair::SharedVal>>();
		}

		properties->clear();
		properties->reserve(static_cast<std::uint32_t>(a_entries.size()));

		for (const auto& entry : a_entries) {
			if (!entry) {
				continue;
			}

			auto* object = entry.find<RE::ActorValueInfo*>(OBJECT_KEY).value_or(nullptr);
			auto value = entry.find<float>(VALUE_KEY).value();

			auto pair = RE::BGSTypedFormValuePair::SharedVal();
			pair.f = value;

			properties->emplace_back(object, std::move(pair));
		}

		return true;
	}

	static PickupPutdownSounds GetPickupPutdownSounds(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto* form = a_form->As<RE::BGSPickupPutdownSounds>();
		if (!form) {
			return nullptr;
		}

		auto sounds = PickupPutdownSounds();
		sounds.insert(PICKUP_SOUND_KEY, form->pickupSound);
		sounds.insert(PUTDOWN_SOUND_KEY, form->putdownSound);
		return sounds;
	}

	static bool SetPickupPutdownSounds(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		PickupPutdownSounds a_sounds)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		if (!a_sounds) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* form = a_form->As<RE::BGSPickupPutdownSounds>();
		if (!form) {
			return false;
		}

		form->pickupSound = a_sounds.find<RE::BGSSoundDescriptorForm*>(PICKUP_SOUND_KEY).value_or(nullptr);
		form->putdownSound = a_sounds.find<RE::BGSSoundDescriptorForm*>(PUTDOWN_SOUND_KEY).value_or(nullptr);
		return true;
	}

	static RE::BGSSoundDescriptorForm* GetCraftSound(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto* form = a_form->As<RE::BGSCraftingUseSound>();
		return form ? nullptr : form->craftingUseSound;
	}

	static bool SetCraftSound(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		RE::BGSSoundDescriptorForm* a_sound)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* form = a_form->As<RE::BGSCraftingUseSound>();
		if (!form) {
			return false;
		}

		form->craftingUseSound = a_sound;
		return true;
	}

	static RE::TESRace* GetRace(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto* form = a_form->As<RE::TESRaceForm>();
		return form ? form->formRace : nullptr;
	}

	static bool SetRace(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		RE::TESRace* a_race)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* form = a_form->As<RE::TESRaceForm>();
		if (!form) {
			return false;
		}

		form->formRace = a_race;
		return true;
	}

	static RE::BGSTerminal* GetTerminal(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto* form = a_form->As<RE::BGSNativeTerminalForm>();
		return form ? form->terminal : nullptr;
	}

	static bool SetTerminal(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		RE::BGSTerminal* a_terminal)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* form = a_form->As<RE::BGSNativeTerminalForm>();
		if (!form) {
			return false;
		}

		form->terminal = a_terminal;
		return true;
	}

	static MaterialSwapModel GetMaterialSwapModel(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto* form = a_form->As<RE::BGSModelMaterialSwap>();
		if (!form) {
			return nullptr;
		}

		auto model = MaterialSwapModel();
		model.insert(OBJECT_KEY, form->swapForm);
		model.insert(COLOR_INDEX_KEY, form->colorRemappingIndex);
		return model;
	}

	static bool SetMaterialSwapModel(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		MaterialSwapModel a_model)
	{
		if (!a_form) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		if (!a_model) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* form = a_form->As<RE::BGSModelMaterialSwap>();
		if (!form) {
			return false;
		}

		form->swapForm = a_model.find<RE::BGSMaterialSwap*>(OBJECT_KEY).value_or(nullptr);
		form->colorRemappingIndex = a_model.find<float>(COLOR_INDEX_KEY).value();
		return true;
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, Create);
		BIND_METHOD(a_vm, SCRIPT_NAME, Copy);
		BIND_METHOD(a_vm, SCRIPT_NAME, HasFlag);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetFlags);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetFlags);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetFlag);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsCreated);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetType);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetTypeByTypeString);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetTypeString);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetTypeStringByType);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetScriptName);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsInMod);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetModName);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetLocalFormID);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetEditorID);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetEditorID);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetByEditorID);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetAllByType);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, FindAllByType);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, FindAllByModName);
		BIND_METHOD(a_vm, SCRIPT_NAME, FindAllByFilter);
		BIND_METHOD(a_vm, SCRIPT_NAME, FindAllByFlag);
		BIND_METHOD(a_vm, SCRIPT_NAME, ContainsKeywordString);
		BIND_METHOD(a_vm, SCRIPT_NAME, HasKeywordString);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetKeywords);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetName);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetName);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetDescription);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetValue);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetValue);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetWeight);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetWeight);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetEquipType);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetEquipType);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetProperties);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetProperties);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetPickupPutdownSounds);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetPickupPutdownSounds);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetCraftSound);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetCraftSound);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetRace);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetRace);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetTerminal);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetTerminal);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetMaterialSwapModel);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetMaterialSwapModel);

		return true;
	}
}