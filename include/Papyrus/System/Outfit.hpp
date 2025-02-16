#pragma once

namespace System::Outfit
{
	static constexpr auto SCRIPT_NAME = "System:Outfit"sv;

	static RE::BSTArray<RE::TESForm*> GetParts(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSOutfit* a_outfit)
	{
		if (!a_outfit) {
			a_vm.PostError(::Internal::Errors::OUTFIT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		return a_outfit->outfitItems;
	}

	static void SetParts(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSOutfit* a_outfit,
		RE::BSTArray<RE::TESForm*> a_parts)
	{
		if (!a_outfit) {
			a_vm.PostError(::Internal::Errors::OUTFIT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		a_outfit->outfitItems = std::move(a_parts);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetParts);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetParts);

		return true;
	}
}
