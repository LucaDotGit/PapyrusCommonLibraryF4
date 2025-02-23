#pragma once

namespace System::Structure
{
	static constexpr auto SCRIPT_NAME = "System:Structure"sv;

	static RE::BSFixedString GetName(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		const RE::BSScript::Variable* a_struct)
	{
		if (!a_struct || !a_struct->is<RE::BSScript::Struct>()) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto structure = RE::BSScript::get<RE::BSScript::Struct>(*a_struct);
		if (!structure) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		return structure->type->name;
	}

	static std::vector<::Internal::Pairs::Pair> GetInitialVariables(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BSFixedString a_structName)
	{
		auto typeInfo = RE::BSTSmartPointer<RE::BSScript::StructTypeInfo>();
		if (!a_vm.GetScriptStructType(a_structName, typeInfo)) {
			a_vm.PostError(fmt::format(::Internal::Errors::STRUCT_NAME_NOT_FOUND, a_structName),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto& varMap = typeInfo->varNameIndexMap;

		auto variables = std::vector<::Internal::Pairs::Pair>();
		variables.reserve(varMap.size());

		for (const auto& [name, index] : varMap) {
			const auto& var = typeInfo->variables[index];
			const auto* value = new RE::BSScript::Variable(var.initialValue);

			auto pair = ::Internal::Pairs::MakePair(name, value);
			variables.push_back(std::move(pair));
		}

		return variables;
	}

	static std::vector<::Internal::Pairs::Pair> GetVariables(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		const RE::BSScript::Variable* a_struct)
	{
		if (!a_struct || !a_struct->is<RE::BSScript::Struct>()) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto structure = RE::BSScript::get<RE::BSScript::Struct>(*a_struct);
		if (!structure) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto lock = RE::BSAutoLock{ structure->structLock };
		const auto& typeInfo = structure->type;

		auto variables = std::vector<::Internal::Pairs::Pair>();
		variables.reserve(typeInfo->variables.size());

		for (const auto& [name, index] : typeInfo->varNameIndexMap) {
			const auto& var = structure->variables[index];
			const auto* value = new RE::BSScript::Variable(var);

			auto pair = ::Internal::Pairs::MakePair(name, value);
			variables.push_back(std::move(pair));
		}

		return variables;
	}

	static std::vector<const RE::BSScript::Variable*> GetValuesByName(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_structs,
		RE::BSFixedString a_variableName)
	{
		auto variables = std::vector<const RE::BSScript::Variable*>();
		variables.reserve(a_structs.size());

		for (const auto& element : a_structs) {
			if (!element || !element->is<RE::BSScript::Struct>()) {
				continue;
			}

			const auto structure = RE::BSScript::get<RE::BSScript::Struct>(*element);
			if (!structure) {
				continue;
			}

			const auto lock = RE::BSAutoLock{ structure->structLock };
			const auto& typeInfo = structure->type;

			const auto nameIt = typeInfo->varNameIndexMap.find(a_variableName);
			if (nameIt == typeInfo->varNameIndexMap.end()) {
				continue;
			}

			const auto& var = structure->variables[nameIt->second];
			const auto* value = new RE::BSScript::Variable(var);
			variables.push_back(value);
		}

		return variables;
	}

	static std::int32_t IndexOfValue(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::vector<const RE::BSScript::Variable*> a_structs,
		RE::BSFixedString a_variableName,
		const RE::BSScript::Variable* a_value,
		std::int32_t a_startIndex,
		std::int32_t a_count)
	{
		const auto size = static_cast<std::int32_t>(a_structs.size());
		if (a_startIndex < 0 || a_startIndex >= size) {
			a_vm.PostError(fmt::format(::Internal::Errors::START_INDEX_OUT_OF_RANGE, a_startIndex, 0, size),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return -1;
		}

		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return -1;
		}

		if (a_count == 0) {
			return -1;
		}

		if (a_count > size) {
			a_count = size;
		}

		const auto begin = a_structs.begin() + a_startIndex;
		const auto end = a_structs.begin() + std::min(size, a_startIndex + a_count);

		for (auto it = begin; it != end; it++) {
			const auto* element = *it;
			if (!element || !element->is<RE::BSScript::Struct>()) {
				continue;
			}

			const auto structure = RE::BSScript::get<RE::BSScript::Struct>(*element);
			if (!structure) {
				continue;
			}

			const auto lock = RE::BSAutoLock{ structure->structLock };
			const auto& typeInfo = structure->type;

			const auto varIndex = typeInfo->varNameIndexMap.find(a_variableName);
			if (varIndex == typeInfo->varNameIndexMap.end()) {
				continue;
			}

			const auto& var = structure->variables[varIndex->second];
			if (::Internal::Comparer::Equals(&var, a_value)) {
				return static_cast<std::int32_t>(std::distance(a_structs.begin(), it));
			}
		}

		return -1;
	}

	static std::int32_t LastIndexOfValue(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::vector<const RE::BSScript::Variable*> a_structs,
		RE::BSFixedString a_variableName,
		const RE::BSScript::Variable* a_value,
		std::int32_t a_startIndex,
		std::int32_t a_count)
	{
		const auto size = static_cast<std::int32_t>(a_structs.size());
		if (a_startIndex < 0) {
			a_vm.PostError(::Internal::Errors::START_INDEX_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return -1;
		}

		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return -1;
		}

		if (a_count == 0) {
			return -1;
		}

		if (a_startIndex >= size) {
			a_startIndex = size - 1;
		}

		if (a_count > size) {
			a_count = size;
		}

		const auto begin = a_structs.rbegin() + size - a_startIndex - 1;
		const auto end = a_structs.rbegin() + std::min(size, size - a_startIndex - 1 + a_count);

		for (auto it = begin; it != end; it++) {
			const auto* element = *it;
			if (!element || !element->is<RE::BSScript::Struct>()) {
				continue;
			}

			const auto structure = RE::BSScript::get<RE::BSScript::Struct>(*element);
			if (!structure) {
				continue;
			}

			const auto lock = RE::BSAutoLock{ structure->structLock };
			const auto& typeInfo = structure->type;

			const auto varIndex = typeInfo->varNameIndexMap.find(a_variableName);
			if (varIndex == typeInfo->varNameIndexMap.end()) {
				continue;
			}

			const auto& var = structure->variables[varIndex->second];
			if (::Internal::Comparer::Equals(&var, a_value)) {
				return static_cast<std::int32_t>(std::distance(it, a_structs.rend()) - 1);
			}
		}

		return -1;
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetName);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetInitialVariables);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetVariables);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetValuesByName);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IndexOfValue);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, LastIndexOfValue);

		return true;
	}
}
