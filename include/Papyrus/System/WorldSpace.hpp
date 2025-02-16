#pragma once

namespace System::WorldSpace
{
	static constexpr auto SCRIPT_NAME = "System:WorldSpace"sv;

	static constexpr auto FORM_FLAGS_KEY = "FormFlags"sv;
	static constexpr auto FLAGS_KEY = "Flags"sv;

	using Data = RE::BSScript::structure_wrapper<"System:WorldSpace", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESWorldSpace* a_worldSpace)
	{
		if (!a_worldSpace) {
			a_vm.PostError(::Internal::Errors::WORLD_SPACE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		auto data = Data();
		data.insert(FORM_FLAGS_KEY, a_worldSpace->formFlags);
		data.insert(FLAGS_KEY, a_worldSpace->flags.underlying());

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESWorldSpace* a_worldSpace,
		Data a_data)
	{
		if (!a_worldSpace) {
			a_vm.PostError(::Internal::Errors::WORLD_SPACE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		a_worldSpace->formFlags = a_data.find<std::uint32_t>(FORM_FLAGS_KEY).value();
		a_worldSpace->flags = a_data.find<RE::TESWorldSpace::Flags>(FLAGS_KEY).value();
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}
