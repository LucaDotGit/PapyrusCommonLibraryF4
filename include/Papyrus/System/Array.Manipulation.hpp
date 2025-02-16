#pragma once

namespace System::Array::Manipulation
{
	static std::vector<const RE::BSScript::Variable*> Add(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array,
		const RE::BSScript::Variable* a_value)
	{
		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(a_array.size() + 1);

		for (const auto* element : a_array) {
			const auto* value = ::Internal::Copier::CopyVar(element);
			result.push_back(value);
		}

		const auto* value = ::Internal::Copier::CopyVar(a_value);
		result.push_back(value);

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> AddRange(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array1,
		std::vector<const RE::BSScript::Variable*> a_array2)
	{
		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(a_array1.size() + a_array2.size());

		for (const auto* element : a_array1) {
			const auto* value = ::Internal::Copier::CopyVar(element);
			result.push_back(value);
		}

		for (const auto* element : a_array2) {
			const auto* value = ::Internal::Copier::CopyVar(element);
			result.push_back(value);
		}

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> Insert(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array,
		std::int32_t a_index,
		const RE::BSScript::Variable* a_value)
	{
		if (a_index < 0 || a_index > a_array.size()) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_index, 0, a_array.size()),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(a_array.size() + 1);

		for (auto i = 0; i < a_index; i++) {
			const auto* value = ::Internal::Copier::CopyVar(a_array[i]);
			result.push_back(value);
		}

		const auto* insertion = ::Internal::Copier::CopyVar(a_value);
		result.push_back(insertion);

		for (auto i = a_index; i < a_array.size(); i++) {
			const auto* value = ::Internal::Copier::CopyVar(a_array[i]);
			result.push_back(value);
		}

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> InsertRange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array1,
		std::int32_t a_index,
		std::vector<const RE::BSScript::Variable*> a_array2)
	{
		if (a_index < 0 || a_index > a_array1.size()) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_index, 0, a_array1.size()),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(a_array1.size() + a_array2.size());

		for (auto i = 0; i < a_index; i++) {
			const auto* value = ::Internal::Copier::CopyVar(a_array1[i]);
			result.push_back(value);
		}

		for (const auto* element : a_array2) {
			const auto* value = ::Internal::Copier::CopyVar(element);
			result.push_back(value);
		}

		for (auto i = a_index; i < a_array1.size(); i++) {
			const auto* value = ::Internal::Copier::CopyVar(a_array1[i]);
			result.push_back(value);
		}

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> Remove(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array,
		const RE::BSScript::Variable* a_value)
	{
		const auto it = std::ranges::find_if(a_array, [&](const RE::BSScript::Variable* a_element) {
			return ::Internal::Comparer::Equals(a_element, a_value);
		});

		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(a_array.size() - 1);

		for (auto i = a_array.begin(); i < it; i++) {
			const auto* value = ::Internal::Copier::CopyVar(*i);
			result.push_back(value);
		}

		for (auto i = it + 1; i < a_array.end(); i++) {
			const auto* value = ::Internal::Copier::CopyVar(*i);
			result.push_back(value);
		}

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> RemoveAll(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array,
		const RE::BSScript::Variable* a_value)
	{
		const auto it = std::ranges::remove_if(a_array, [&](const RE::BSScript::Variable* a_element) {
			return ::Internal::Comparer::Equals(a_element, a_value);
		});

		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(std::distance(a_array.begin(), it.begin()));

		for (auto i = a_array.begin(); i != it.begin(); i++) {
			const auto* value = ::Internal::Copier::CopyVar(*i);
			result.push_back(value);
		}

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> RemoveAt(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array,
		std::int32_t a_index)
	{
		const auto size = static_cast<std::int32_t>(a_array.size());
		if (a_index < 0 || a_index >= size) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_index, 0, size),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(size - 1);

		for (auto i = 0; i < a_index; i++) {
			const auto* value = ::Internal::Copier::CopyVar(a_array[i]);
			result.push_back(value);
		}

		for (auto i = a_index + 1; i < size; i++) {
			const auto* value = ::Internal::Copier::CopyVar(a_array[i]);
			result.push_back(value);
		}

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> RemoveRange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array,
		std::int32_t a_index,
		std::int32_t a_count)
	{
		const auto size = static_cast<std::int32_t>(a_array.size());
		if (a_index < 0 || a_index >= size) {
			a_vm.PostError(fmt::format(::Internal::Errors::INDEX_OUT_OF_RANGE, a_index, 0, size),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(size - a_count);

		for (auto i = 0; i < a_index; i++) {
			const auto* value = ::Internal::Copier::CopyVar(a_array[i]);
			result.push_back(value);
		}

		for (auto i = a_index + a_count; i < size; i++) {
			const auto* value = ::Internal::Copier::CopyVar(a_array[i]);
			result.push_back(value);
		}

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> Fill(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array,
		const RE::BSScript::Variable* a_value,
		std::int32_t a_startIndex,
		std::int32_t a_count)
	{
		const auto size = static_cast<std::int32_t>(a_array.size());
		if (a_startIndex < 0 || a_startIndex >= size) {
			a_vm.PostError(fmt::format(::Internal::Errors::START_INDEX_OUT_OF_RANGE, a_startIndex, 0, size),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(size);

		for (auto i = 0; i < a_startIndex; i++) {
			const auto* value = ::Internal::Copier::CopyVar(a_array[i]);
			result.push_back(value);
		}

		for (auto i = 0; i < a_count; i++) {
			const auto* value = ::Internal::Copier::CopyVar(a_value);
			result.push_back(value);
		}

		for (auto i = a_startIndex + a_count; i < size; i++) {
			const auto* value = ::Internal::Copier::CopyVar(a_array[i]);
			result.push_back(value);
		}

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> Resize(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array,
		std::int32_t a_count)
	{
		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(a_count);

		for (auto i = 0; i < a_count; i++) {
			const auto* value = i < a_array.size() ? ::Internal::Copier::CopyVar(a_array[i]) : nullptr;
			result.push_back(value);
		}

		return result;
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Add);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, AddRange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Insert);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, InsertRange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Remove);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RemoveAll);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RemoveAt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RemoveRange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Fill);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Resize);

		return true;
	}
}
