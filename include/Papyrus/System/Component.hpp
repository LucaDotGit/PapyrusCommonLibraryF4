#pragma once

namespace System::Component
{
	static constexpr auto SCRIPT_NAME = "System:Component"sv;

	static constexpr auto CRAFT_SOUND_KEY = "CraftSound"sv;
	static constexpr auto SCRAP_ITEM_KEY = "ScrapItem"sv;
	static constexpr auto SCRAP_SCALAR_KEY = "ScrapScalar"sv;

	using Data = RE::BSScript::structure_wrapper<"System:Component", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSComponent* a_component)
	{
		if (!a_component) {
			a_vm.PostError(::Internal::Errors::COMPONENT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		auto data = Data();
		data.insert(CRAFT_SOUND_KEY, a_component->craftingUseSound);
		data.insert(SCRAP_ITEM_KEY, a_component->scrapItem);
		data.insert(SCRAP_SCALAR_KEY, a_component->modScrapScalar);

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSComponent* a_component,
		Data a_data)
	{
		if (!a_component) {
			a_vm.PostError(::Internal::Errors::COMPONENT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		a_component->craftingUseSound = a_data.find<RE::BGSSoundDescriptorForm*>(CRAFT_SOUND_KEY).value_or(nullptr);
		a_component->scrapItem = a_data.find<RE::TESObjectMISC*>(SCRAP_ITEM_KEY).value_or(nullptr);
		a_component->modScrapScalar = a_data.find<RE::TESGlobal*>(SCRAP_SCALAR_KEY).value_or(nullptr);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}