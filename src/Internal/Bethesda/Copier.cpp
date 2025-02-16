#include "Internal/Bethesda/Copier.hpp"

namespace Internal::Copier
{
	RE::BSScript::Variable Copy(const RE::BSScript::Variable* a_var)
	{
		return a_var ? RE::BSScript::Variable(*a_var) : RE::BSScript::Variable();
	}

	RE::BSScript::Variable* CopyVar(const RE::BSScript::Variable* a_var)
	{
		return a_var ? new RE::BSScript::Variable(*a_var) : nullptr;
	}

	RE::BSScript::Variable DeepCopy(const RE::BSScript::Variable* a_var)
	{
		if (!a_var) {
			return {};
		}

		if (a_var->is<RE::BSScript::Variable>()) {
			const auto* value = RE::BSScript::get<RE::BSScript::Variable>(*a_var);
			return DeepCopy(value);
		}

		if (a_var->is<RE::BSScript::Struct>()) {
			const auto value = RE::BSScript::get<RE::BSScript::Struct>(*a_var);
			return DeepCopyStruct(value);
		}

		if (a_var->is<RE::BSScript::Array>()) {
			const auto value = RE::BSScript::get<RE::BSScript::Array>(*a_var);
			return DeepCopyArray(value);
		}

		return { *a_var };
	}

	RE::BSScript::Variable* DeepCopyVar(const RE::BSScript::Variable* a_var)
	{
		const auto copy = DeepCopy(a_var);
		return new RE::BSScript::Variable(copy);
	}

	std::vector<const RE::BSScript::Variable*> CopyArray(
		const std::vector<const RE::BSScript::Variable*>& a_array)
	{
		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(a_array.size());

		for (const auto* element : a_array) {
			const auto* value = CopyVar(element);
			result.push_back(value);
		}

		return result;
	}

	std::vector<const RE::BSScript::Variable*> DeepCopyArray(
		const std::vector<const RE::BSScript::Variable*>& a_array)
	{
		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(a_array.size());

		for (const auto* element : a_array) {
			const auto* value = DeepCopyVar(element);
			result.push_back(value);
		}

		return result;
	}

	RE::BSScript::Variable VarArrayToVar(
		const std::vector<const RE::BSScript::Variable*>& a_array)
	{
		constexpr auto DEFAULT_TYPE = RE::BSScript::TypeInfo::RawType::kVar;

		const auto vm = RE::GameVM::GetSingleton()->GetVM();
		const auto size = static_cast<std::uint32_t>(a_array.size());

		auto result = RE::BSTSmartPointer<RE::BSScript::Array>();
		vm->CreateArray(DEFAULT_TYPE, size, result);

		for (auto i = 0ui32; i < size; i++) {
			auto* value = CopyVar(a_array[i]);
			result->elements[i] = value;
		}

		return ToVar(std::move(result));
	}

	std::vector<const RE::BSScript::Variable*> VarToVarArray(
		const RE::BSScript::Variable* a_value)
	{
		if (!a_value || !a_value->is<RE::BSScript::Array>()) {
			return {};
		}

		const auto array = RE::BSScript::get<RE::BSScript::Array>(*a_value);
		if (!array) {
			return {};
		}

		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(array->size());

		for (const auto& element : array->elements) {
			const auto* value = CopyVar(&element);
			result.push_back(value);
		}

		return result;
	}

	RE::BSScript::Variable DeepCopyStruct(
		const RE::BSTSmartPointer<RE::BSScript::Struct>& a_struct)
	{
		if (!a_struct) {
			return {};
		}

		const auto lock = RE::BSAutoLock{ a_struct->structLock };

		const auto& typeInfo = a_struct->type;
		if (!typeInfo) {
			return {};
		}

		const auto vm = RE::GameVM::GetSingleton()->GetVM();
		const auto size = typeInfo->variables.size();

		auto result = RE::BSTSmartPointer<RE::BSScript::Struct>();
		vm->CreateStruct(typeInfo->name, result);

		for (auto i = 0ui32; i < size; i++) {
			auto copy = DeepCopy(&a_struct->variables[i]);
			result->variables[i] = std::move(copy);
		}

		return ToVar(std::move(result));
	}

	RE::BSScript::Variable DeepCopyArray(
		const RE::BSTSmartPointer<RE::BSScript::Array>& a_array)
	{
		if (!a_array) {
			return {};
		}

		const auto vm = RE::GameVM::GetSingleton()->GetVM();
		const auto lock = RE::BSAutoLock{ a_array->elementsLock };
		const auto size = a_array->size();

		auto result = RE::BSTSmartPointer<RE::BSScript::Array>();
		vm->CreateArray(a_array->elementType, size, result);

		for (auto i = 0ui32; i < size; i++) {
			auto copy = DeepCopy(&a_array->elements[i]);
			result->elements[i] = std::move(copy);
		}

		return ToVar(std::move(result));
	}
}
