#pragma once

namespace System::Cell
{
	static constexpr auto SCRIPT_NAME = "System:Cell"sv;

	static constexpr auto FORM_FLAGS_KEY = "FormFlags"sv;
	static constexpr auto FLAGS_KEY = "Flags"sv;

	using Data = RE::BSScript::structure_wrapper<"System:Cell", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectCELL* a_cell)
	{
		if (!a_cell) {
			a_vm.PostError(::Internal::Errors::CELL_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto lock = RE::BSSpinLock{ a_cell->spinLock };

		auto data = Data();
		data.insert(FORM_FLAGS_KEY, a_cell->formFlags);
		data.insert(FLAGS_KEY, a_cell->cellFlags.underlying());

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectCELL* a_cell,
		Data a_data)
	{
		if (!a_cell) {
			a_vm.PostError(::Internal::Errors::CELL_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		const auto lock = RE::BSSpinLock{ a_cell->spinLock };

		a_cell->formFlags = a_data.find<std::uint32_t>(FORM_FLAGS_KEY).value();
		a_cell->cellFlags = a_data.find<RE::TESObjectCELL::Flags>(FLAGS_KEY).value();

		a_cell->AddChange(RE::CHANGE_TYPE::kCellFlags);
	}

	static std::vector<RE::TESObjectREFR*> FindAllRefs(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectCELL* a_originCell,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects)
	{
		if (!a_originCell) {
			a_vm.PostError(::Internal::Errors::CELL_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto filter = ::Internal::VarFilter{ a_includedObjects, a_excludedObjects };
		const auto isEmpty = filter.IsEmpty();

		auto refs = std::vector<RE::TESObjectREFR*>();
		a_originCell->ForEachRef([&](RE::TESObjectREFR* a_ref) {
			if (isEmpty || filter.Filter(a_ref)) {
				refs.push_back(a_ref);
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return refs;
	}

	static std::vector<RE::TESObjectREFR*> FindAllRefsInRange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectCELL* a_originCell,
		::Internal::Vectors::Vector3 a_center,
		float a_radius,
		std::vector<const RE::BSScript::Variable*> a_includedObjects,
		std::vector<const RE::BSScript::Variable*> a_excludedObjects)
	{
		if (!a_originCell) {
			a_vm.PostError(::Internal::Errors::CELL_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

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
		a_originCell->ForEachRefInRange(center, a_radius, [&](RE::TESObjectREFR* a_ref) {
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

		const auto* parentCell = a_originRef->GetParentCell();
		if (!parentCell) {
			return {};
		}

		const auto filter = ::Internal::VarFilter{ a_includedObjects, a_excludedObjects };
		const auto isEmpty = filter.IsEmpty();

		auto refs = std::vector<RE::TESObjectREFR*>();
		parentCell->ForEachRefInRange(a_originRef->GetPosition(), a_radius, [&](RE::TESObjectREFR* a_ref) {
			if (a_ref != a_originRef && (isEmpty || filter.Filter(a_ref))) {
				refs.push_back(a_ref);
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return refs;
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetData);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, FindAllRefs);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, FindAllRefsInRange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, FindAllRefsInRangeFromRef);

		return true;
	}
}
