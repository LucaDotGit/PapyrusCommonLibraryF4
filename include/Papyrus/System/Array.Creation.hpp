#pragma once

namespace System::Array::Creation
{
	template <typename T>
	static std::vector<T> RepeatImpl(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID,
		std::int32_t a_count,
		T a_value)
	{
		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto result = std::vector<T>();
		result.reserve(a_count);

		for (auto i = 0; i < a_count; i++) {
			result.push_back(a_value);
		}

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> Repeat(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::int32_t a_count)
	{
		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto result = std::vector<const RE::BSScript::Variable*>();
		result.resize(a_count);

		return result;
	}

	static std::vector<bool> RepeatBool(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::int32_t a_count,
		bool a_value)
	{
		return RepeatImpl(a_vm, a_stackID, a_count, a_value);
	}

	static std::vector<std::int32_t> RepeatInt(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::int32_t a_count,
		std::int32_t a_value)
	{
		return RepeatImpl(a_vm, a_stackID, a_count, a_value);
	}

	static std::vector<float> RepeatFloat(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::int32_t a_count,
		float a_value)
	{
		return RepeatImpl(a_vm, a_stackID, a_count, a_value);
	}

	static std::vector<RE::BSFixedString> RepeatString(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::int32_t a_count,
		RE::BSFixedString a_value)
	{
		return RepeatImpl(a_vm, a_stackID, a_count, a_value);
	}

	static std::vector<RE::BSTSmartPointer<RE::BSScript::Object>> RepeatObject(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::int32_t a_count,
		RE::BSTSmartPointer<RE::BSScript::Object> a_value)
	{
		return RepeatImpl(a_vm, a_stackID, a_count, a_value);
	}

	static std::vector<const RE::BSScript::Variable*> RepeatVar(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::int32_t a_count,
		const RE::BSScript::Variable* a_value)
	{
		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(a_count);

		for (auto i = 0; i < a_count; i++) {
			const auto* value = ::Internal::Copier::DeepCopyVar(a_value);
			result.push_back(value);
		}

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> RepeatArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::int32_t a_count,
		std::vector<const RE::BSScript::Variable*> a_array)
	{
		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		if (a_array.empty()) {
			return {};
		}

		auto result = std::vector<const RE::BSScript::Variable*>();
		result.reserve(a_count);

		for (auto i = 0; i < a_count; i++) {
			const auto var = ::Internal::Copier::VarArrayToVar(a_array);
			const auto* value = ::Internal::Copier::CopyVar(&var);
			result.push_back(value);
		}

		return result;
	}

	static std::vector<std::int32_t> Range(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::int32_t a_start,
		std::int32_t a_count,
		std::int32_t a_step)
	{
		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto result = std::vector<std::int32_t>();
		result.reserve(a_count);

		for (auto i = 0; i < a_count; i++) {
			const auto value = a_start + i * a_step;
			result.push_back(value);
		}

		return result;
	}

	static std::vector<float> RangeFloat(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		float a_start,
		std::int32_t a_count,
		float a_step)
	{
		if (a_count < 0) {
			a_vm.PostError(::Internal::Errors::COUNT_NEGATIVE, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto result = std::vector<float>();
		result.reserve(a_count);

		for (auto i = 0; i < a_count; i++) {
			const auto value = a_start + i * a_step;
			result.push_back(value);
		}

		return result;
	}

	static std::vector<const RE::BSScript::Variable*> Copy(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array)
	{
		return ::Internal::Copier::CopyArray(a_array);
	}

	static std::vector<const RE::BSScript::Variable*> DeepCopy(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array)
	{
		return ::Internal::Copier::DeepCopyArray(a_array);
	}

	static const RE::BSScript::Variable* BoolArrayToVar(std::monostate,
		std::vector<bool> a_array)
	{
		const auto value = ::Internal::Copier::TArrayToVar(a_array);
		return ::Internal::Copier::CopyVar(&value);
	}

	static const RE::BSScript::Variable* IntArrayToVar(std::monostate,
		std::vector<std::int32_t> a_array)
	{
		const auto value = ::Internal::Copier::TArrayToVar(a_array);
		return ::Internal::Copier::CopyVar(&value);
	}

	static const RE::BSScript::Variable* FloatArrayToVar(std::monostate,
		std::vector<float> a_array)
	{
		const auto value = ::Internal::Copier::TArrayToVar(a_array);
		return ::Internal::Copier::CopyVar(&value);
	}

	static const RE::BSScript::Variable* StringArrayToVar(std::monostate,
		std::vector<RE::BSFixedString> a_array)
	{
		const auto value = ::Internal::Copier::TArrayToVar(a_array);
		return ::Internal::Copier::CopyVar(&value);
	}

	static const RE::BSScript::Variable* ObjectArrayToVar(std::monostate,
		std::vector<RE::BSTSmartPointer<RE::BSScript::Object>> a_array)
	{
		const auto value = ::Internal::Copier::TArrayToVar(a_array);
		return ::Internal::Copier::CopyVar(&value);
	}

	static const RE::BSScript::Variable* VarArrayToVar(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array)
	{
		const auto value = ::Internal::Copier::VarArrayToVar(a_array);
		return ::Internal::Copier::CopyVar(&value);
	}

	static std::vector<bool> VarToBoolArray(std::monostate,
		const RE::BSScript::Variable* a_value)
	{
		return ::Internal::Copier::VarToTArray<bool>(a_value);
	}

	static std::vector<std::int32_t> VarToIntArray(std::monostate,
		const RE::BSScript::Variable* a_value)
	{
		return ::Internal::Copier::VarToTArray<std::int32_t>(a_value);
	}

	static std::vector<float> VarToFloatArray(std::monostate,
		const RE::BSScript::Variable* a_value)
	{
		return ::Internal::Copier::VarToTArray<float>(a_value);
	}

	static std::vector<RE::BSFixedString> VarToStringArray(std::monostate,
		const RE::BSScript::Variable* a_value)
	{
		return ::Internal::Copier::VarToTArray<RE::BSFixedString>(a_value);
	}

	static std::vector<RE::BSTSmartPointer<RE::BSScript::Object>> VarToObjectArray(std::monostate,
		const RE::BSScript::Variable* a_value)
	{
		return ::Internal::Copier::VarToTArray<RE::BSTSmartPointer<RE::BSScript::Object>>(a_value);
	}

	static std::vector<const RE::BSScript::Variable*> VarToVarArray(std::monostate,
		const RE::BSScript::Variable* a_value)
	{
		return ::Internal::Copier::VarToVarArray(a_value);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Repeat);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RepeatBool);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RepeatInt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RepeatFloat);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RepeatString);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RepeatObject);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RepeatVar);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RepeatArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Range);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RangeFloat);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Copy);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, DeepCopy);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, BoolArrayToVar);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IntArrayToVar);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, FloatArrayToVar);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, StringArrayToVar);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ObjectArrayToVar);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, VarArrayToVar);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, VarToBoolArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, VarToIntArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, VarToFloatArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, VarToStringArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, VarToObjectArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, VarToVarArray);

		return true;
	}
}
