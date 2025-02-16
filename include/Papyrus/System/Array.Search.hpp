#pragma once

namespace System::Array::Search
{
	static bool Contains(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array,
		const RE::BSScript::Variable* a_value)
	{
		if (a_array.empty()) {
			return false;
		}

		return std::ranges::any_of(a_array, [&](const RE::BSScript::Variable* a_element) {
			return ::Internal::Comparer::Equals(a_element, a_value);
		});
	}

	static bool StartsWith(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array,
		const RE::BSScript::Variable* a_value)
	{
		if (a_array.empty()) {
			return false;
		}

		return ::Internal::Comparer::Equals(a_array.front(), a_value);
	}

	static bool EndsWith(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array,
		const RE::BSScript::Variable* a_value)
	{
		if (a_array.empty()) {
			return false;
		}

		return ::Internal::Comparer::Equals(a_array.back(), a_value);
	}

	static std::int32_t IndexOf(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array,
		const RE::BSScript::Variable* a_value,
		std::int32_t a_startIndex,
		std::int32_t a_count)
	{
		const auto size = static_cast<std::int32_t>(a_array.size());
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

		const auto begin = a_array.begin() + a_startIndex;
		const auto end = a_array.begin() + std::min(size, a_startIndex + a_count);

		for (auto it = begin; it != end; it++) {
			if (::Internal::Comparer::Equals(*it, a_value)) {
				return static_cast<std::int32_t>(std::distance(a_array.begin(), it));
			}
		}

		return -1;
	}

	static std::int32_t LastIndexOf(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array,
		const RE::BSScript::Variable* a_value,
		std::int32_t a_startIndex,
		std::int32_t a_count)
	{
		const auto size = static_cast<std::int32_t>(a_array.size());
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

		const auto begin = a_array.rbegin() + size - a_startIndex - 1;
		const auto end = a_array.rbegin() + std::min(size, size - a_startIndex - 1 + a_count);

		for (auto it = begin; it != end; it++) {
			if (::Internal::Comparer::Equals(*it, a_value)) {
				return static_cast<std::int32_t>(std::distance(it, a_array.rend()) - 1);
			}
		}

		return -1;
	}

	static bool Any(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array1,
		std::vector<const RE::BSScript::Variable*> a_array2)
	{
		if (a_array1.empty() || a_array2.empty()) {
			return false;
		}

		return std::ranges::any_of(a_array2, [&](const RE::BSScript::Variable* a_element2) {
			return std::ranges::any_of(a_array1, [&](const RE::BSScript::Variable* a_element1) {
				return ::Internal::Comparer::Equals(a_element1, a_element2);
			});
		});
	}

	static bool All(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array1,
		std::vector<const RE::BSScript::Variable*> a_array2)
	{
		if (a_array1.empty() || a_array2.empty()) {
			return false;
		}

		return std::ranges::all_of(a_array2, [&](const RE::BSScript::Variable* a_element2) {
			return std::ranges::any_of(a_array1, [&](const RE::BSScript::Variable* a_element1) {
				return ::Internal::Comparer::Equals(a_element1, a_element2);
			});
		});
	}

	static const RE::BSScript::Variable* Min(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array)
	{
		const auto it = std::ranges::min_element(a_array, ::Internal::Comparer::IsLessThan);
		return it != a_array.end() ? ::Internal::Copier::CopyVar(*it) : nullptr;
	}

	static const RE::BSScript::Variable* Max(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array)
	{
		const auto it = std::ranges::max_element(a_array, ::Internal::Comparer::IsLessThan);
		return it != a_array.end() ? ::Internal::Copier::CopyVar(*it) : nullptr;
	}

	static std::int32_t Sum(std::monostate,
		std::vector<std::int32_t> a_array)
	{
		return std::ranges::fold_left(a_array, 0, std::plus<std::int32_t>());
	}

	static float SumFloat(std::monostate,
		std::vector<float> a_array)
	{
		return std::ranges::fold_left(a_array, 0.0f, std::plus<float>());
	}

	static std::int32_t Average(std::monostate,
		std::vector<std::int32_t> a_array)
	{
		if (a_array.empty()) {
			return 0;
		}

		return std::ranges::fold_left(a_array, 0, std::plus<std::int32_t>()) / static_cast<std::int32_t>(a_array.size());
	}

	static float AverageFloat(std::monostate,
		std::vector<float> a_array)
	{
		if (a_array.empty()) {
			return 0;
		}

		return std::ranges::fold_left(a_array, 0.0f, std::plus<float>()) / a_array.size();
	}

	static std::vector<const RE::BSScript::Variable*> Union(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array1,
		std::vector<const RE::BSScript::Variable*> a_array2)
	{
		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(std::max(a_array1.size(), a_array2.size()));

		for (const auto* element : a_array1) {
			const auto* value = ::Internal::Copier::CopyVar(element);
			result.push_back(value);
		}

		for (const auto* element : a_array2) {
			const auto filter = [&](const RE::BSScript::Variable* a_element) {
				return ::Internal::Comparer::Equals(a_element, element);
			};

			if (std::ranges::none_of(result, filter)) {
				const auto* value = ::Internal::Copier::CopyVar(element);
				result.push_back(value);
			}
		}

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> Intersect(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array1,
		std::vector<const RE::BSScript::Variable*> a_array2)
	{
		if (a_array2.empty()) {
			return {};
		}

		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(std::min(a_array1.size(), a_array2.size()));

		for (const auto* element : a_array1) {
			const auto filter = [&](const RE::BSScript::Variable* a_element) {
				return ::Internal::Comparer::Equals(a_element, element);
			};

			if (std::ranges::any_of(a_array2, filter)) {
				const auto* value = ::Internal::Copier::CopyVar(element);
				result.push_back(value);
			}
		}

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> Except(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array1,
		std::vector<const RE::BSScript::Variable*> a_array2)
	{
		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(std::max(a_array1.size(), a_array2.size()));

		for (const auto* element : a_array1) {
			const auto filter = [&](const RE::BSScript::Variable* a_element) {
				return ::Internal::Comparer::Equals(a_element, element);
			};

			if (std::ranges::none_of(a_array2, filter)) {
				const auto* value = ::Internal::Copier::CopyVar(element);
				result.push_back(value);
			}
		}

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> Take(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array,
		std::int32_t a_count)
	{
		const auto size = static_cast<std::int32_t>(a_array.size());
		if (a_count < 0 || a_count > size) {
			a_vm.PostError(fmt::format(::Internal::Errors::COUNT_OUT_OF_RANGE, a_count, 0, size),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(a_count);

		for (auto i = 0; i < a_count; i++) {
			const auto* value = ::Internal::Copier::CopyVar(a_array[i]);
			result.push_back(value);
		}

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> Skip(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array,
		std::int32_t a_count)
	{
		const auto size = static_cast<std::int32_t>(a_array.size());
		if (a_count < 0 || a_count > size) {
			a_vm.PostError(fmt::format(::Internal::Errors::COUNT_OUT_OF_RANGE, a_count, 0, size),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(size - a_count);

		for (auto i = a_count; i < size; i++) {
			const auto* value = ::Internal::Copier::CopyVar(a_array[i]);
			result.push_back(value);
		}

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> Distinct(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array)
	{
		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(a_array.size());

		for (const auto* element : a_array) {
			const auto filter = [&](const RE::BSScript::Variable* a_element) {
				return ::Internal::Comparer::Equals(a_element, element);
			};

			if (std::ranges::none_of(result, filter)) {
				const auto* value = ::Internal::Copier::CopyVar(element);
				result.push_back(value);
			}
		}

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> Sort(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array,
		bool a_descending)
	{
		if (a_array.empty()) {
			return {};
		}

		const auto comparer = a_descending ? ::Internal::Comparer::IsGreaterThan : ::Internal::Comparer::IsLessThan;

		auto result = ::Internal::Copier::CopyArray(a_array);
		std::ranges::sort(result, comparer);

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> Reverse(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array)
	{
		if (a_array.empty()) {
			return {};
		}

		auto result = ::Internal::Copier::CopyArray(a_array);
		std::ranges::reverse(result);

		return result;
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Contains);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, StartsWith);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, EndsWith);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IndexOf);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, LastIndexOf);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Any);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, All);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Min);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Max);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Sum);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SumFloat);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Average);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, AverageFloat);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Union);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Intersect);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Except);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Take);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Skip);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Distinct);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Sort);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Reverse);

		return true;
	}
}
