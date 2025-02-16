#pragma once

namespace Internal::Copier
{
	[[nodiscard]] RE::BSScript::Variable Copy(const RE::BSScript::Variable* a_var);
	[[nodiscard]] RE::BSScript::Variable* CopyVar(const RE::BSScript::Variable* a_var);

	[[nodiscard]] RE::BSScript::Variable DeepCopy(const RE::BSScript::Variable* a_var);
	[[nodiscard]] RE::BSScript::Variable* DeepCopyVar(const RE::BSScript::Variable* a_var);

	[[nodiscard]] std::vector<const RE::BSScript::Variable*> CopyArray(
		const std::vector<const RE::BSScript::Variable*>& a_array);
	[[nodiscard]] std::vector<const RE::BSScript::Variable*> DeepCopyArray(
		const std::vector<const RE::BSScript::Variable*>& a_array);

	template <typename T>
	[[nodiscard]] RE::BSScript::Variable ToVar(T&& a_value)
	{
		auto result = RE::BSScript::Variable();
		result = std::forward<T>(a_value);
		return result;
	}

	template <typename T>
	[[nodiscard]] RE::BSScript::Variable* ToVarPtr(T&& a_value)
	{
		auto* result = new RE::BSScript::Variable();
		*result = std::forward<T>(a_value);
		return result;
	}

	template <typename T>
		requires(!std::same_as<RE::detail::remove_cvpr_t<T>, RE::BSScript::Variable>)
	[[nodiscard]] RE::BSScript::Variable TArrayToVar(
		const std::vector<T>& a_array)
	{
		const auto typeInfo = RE::BSScript::GetTypeInfo<T>();
		if (!typeInfo.has_value()) {
			return {};
		}

		const auto size = static_cast<std::uint32_t>(a_array.size());
		const auto vm = RE::GameVM::GetSingleton()->GetVM();

		auto result = RE::BSTSmartPointer<RE::BSScript::Array>();
		vm->CreateArray(typeInfo.value(), size, result);

		for (auto i = 0ui32; i < size; i++) {
			auto value = ToVar(a_array[i]);
			result->elements[i] = std::move(value);
		}

		return ToVar(std::move(result));
	}

	template <typename T>
		requires(!std::same_as<RE::detail::remove_cvpr_t<T>, RE::BSScript::Variable>)
	[[nodiscard]] std::vector<T> VarToTArray(
		const RE::BSScript::Variable* a_var)
	{
		if (!a_var || !a_var->is<RE::BSScript::Array>()) {
			return {};
		}

		const auto array = RE::BSScript::get<RE::BSScript::Array>(*a_var);
		if (!array) {
			return {};
		}

		auto result = std::vector<T>();
		result.reserve(array->size());

		for (const auto& element : array->elements) {
			if (!element.is<T>()) {
				return {};
			}

			const auto value = RE::BSScript::get<T>(element);
			result.push_back(value);
		}

		return result;
	}

	[[nodiscard]] RE::BSScript::Variable VarArrayToVar(
		const std::vector<const RE::BSScript::Variable*>& a_array);
	[[nodiscard]] std::vector<const RE::BSScript::Variable*> VarToVarArray(
		const RE::BSScript::Variable* a_value);

	[[nodiscard]] RE::BSScript::Variable DeepCopyStruct(
		const RE::BSTSmartPointer<RE::BSScript::Struct>& a_struct);
	[[nodiscard]] RE::BSScript::Variable DeepCopyArray(
		const RE::BSTSmartPointer<RE::BSScript::Array>& a_array);
}
