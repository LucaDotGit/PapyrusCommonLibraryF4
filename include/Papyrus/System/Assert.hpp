#pragma once

#include "Internal/Bethesda/Converter.hpp"

namespace System::Assert
{
	static constexpr auto SCRIPT_NAME = "System:Assert"sv;

	template <typename... Args>
	static void Error(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID,
		std::string_view a_message,
		fmt::format_string<Args...> a_default,
		Args&&... a_args)
	{
		if (a_message.empty()) {
			a_vm.PostError(fmt::format(a_default, std::forward<Args>(a_args)...),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		try {
			a_vm.PostError(fmt::format(fmt::runtime(a_message), std::forward<Args>(a_args)...),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
		}
		catch (const fmt::format_error& a_error) {
			a_vm.PostError(a_error.what(), a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
		}
	}

	static void IsTrue(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		bool a_condition,
		std::string_view a_message)
	{
		if (a_condition) {
			return;
		}

		Error(a_vm, a_stackID, a_message, "Expected the condition to be true"sv);
	}

	static void IsFalse(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		bool a_condition,
		std::string_view a_message)
	{
		if (!a_condition) {
			return;
		}

		Error(a_vm, a_stackID, a_message, "Expected the condition to be false"sv);
	}

	static void IsNone(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		const RE::BSScript::Variable* a_value,
		std::string_view a_message)
	{
		if (a_value || *a_value) {
			return;
		}

		Error(a_vm, a_stackID, a_message, "Expected the value to be none"sv);
	}

	static void NotNone(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		const RE::BSScript::Variable* a_value,
		std::string_view a_message)
	{
		if (!a_value && !*a_value) {
			return;
		}

		Error(a_vm, a_stackID, a_message, "Expected the value to not be none"sv);
	}

	static void Equals(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right,
		std::string_view a_message)
	{
		if (::Internal::Comparer::Equals(a_left, a_right)) {
			return;
		}

		Error(a_vm, a_stackID, a_message, "Expected {} to be equal to {}"sv,
			::Internal::Converter::ToString(a_left), ::Internal::Converter::ToString(a_right));
	}

	static void NotEquals(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right,
		std::string_view a_message)
	{
		if (!::Internal::Comparer::Equals(a_left, a_right)) {
			return;
		}

		Error(a_vm, a_stackID, a_message, "Expected {} to not be equal to {}"sv,
			::Internal::Converter::ToString(a_left), ::Internal::Converter::ToString(a_right));
	}

	static void IsLessThan(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right,
		std::string_view a_message)
	{
		if (::Internal::Comparer::IsLessThan(a_left, a_right)) {
			return;
		}

		Error(a_vm, a_stackID, a_message, "Expected {} to be less than {}"sv,
			::Internal::Converter::ToString(a_left), ::Internal::Converter::ToString(a_right));
	}

	static void IsLessThanOrEqual(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right,
		std::string_view a_message)
	{
		if (::Internal::Comparer::IsLessThanOrEqual(a_left, a_right)) {
			return;
		}

		Error(a_vm, a_stackID, a_message, "Expected {} to be less than or equal to {}"sv,
			::Internal::Converter::ToString(a_left), ::Internal::Converter::ToString(a_right));
	}

	static void IsGreaterThan(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right,
		std::string_view a_message)
	{
		if (::Internal::Comparer::IsGreaterThan(a_left, a_right)) {
			return;
		}

		Error(a_vm, a_stackID, a_message, "Expected {} to be greater than {}"sv,
			::Internal::Converter::ToString(a_left), ::Internal::Converter::ToString(a_right));
	}

	static void IsGreaterThanOrEqual(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right,
		std::string_view a_message)
	{
		if (::Internal::Comparer::IsGreaterThanOrEqual(a_left, a_right)) {
			return;
		}

		Error(a_vm, a_stackID, a_message, "Expected {} to be greater than or equal to {}"sv,
			::Internal::Converter::ToString(a_left), ::Internal::Converter::ToString(a_right));
	}

	static void IsInRange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		const RE::BSScript::Variable* a_value,
		const RE::BSScript::Variable* a_min,
		const RE::BSScript::Variable* a_max,
		std::string_view a_message)
	{
		if (::Internal::Comparer::IsInRange(a_value, a_min, a_max)) {
			return;
		}

		Error(a_vm, a_stackID, a_message, "Expected {} to be in range of {} to {}"sv,
			::Internal::Converter::ToString(a_value), ::Internal::Converter::ToString(a_min), ::Internal::Converter::ToString(a_max));
	}

	static void NotInRange(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		const RE::BSScript::Variable* a_value,
		const RE::BSScript::Variable* a_min,
		const RE::BSScript::Variable* a_max,
		std::string_view a_message)
	{
		if (!::Internal::Comparer::IsInRange(a_value, a_min, a_max)) {
			return;
		}

		Error(a_vm, a_stackID, a_message, "Expected {} to not be in range of {} to {}"sv,
			::Internal::Converter::ToString(a_value), ::Internal::Converter::ToString(a_min), ::Internal::Converter::ToString(a_max));
	}

	static void RefEquals(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right,
		std::string_view a_message)
	{
		if (::Internal::Comparer::RefEquals(a_left, a_right)) {
			return;
		}

		Error(a_vm, a_stackID, a_message, "Expected {} to have the same ref as {}"sv,
			::Internal::Converter::ToString(a_left), ::Internal::Converter::ToString(a_right));
	}

	static void RefNotEquals(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right,
		std::string_view a_message)
	{
		if (!::Internal::Comparer::RefEquals(a_left, a_right)) {
			return;
		}

		Error(a_vm, a_stackID, a_message, "Expected {} to not have the same ref as {}"sv,
			::Internal::Converter::ToString(a_left), ::Internal::Converter::ToString(a_right));
	}

	static void TypeEquals(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right,
		std::string_view a_message)
	{
		if (::Internal::Comparer::TypeEquals(a_left, a_right)) {
			return;
		}

		Error(a_vm, a_stackID, a_message, "Expected {} to have the same type as {}"sv,
			::Internal::Converter::ToString(a_left), ::Internal::Converter::ToString(a_right));
	}

	static void TypeNotEquals(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right,
		std::string_view a_message)
	{
		if (!::Internal::Comparer::TypeEquals(a_left, a_right)) {
			return;
		}

		Error(a_vm, a_stackID, a_message, "Expected {} to not have the same type as {}"sv,
			::Internal::Converter::ToString(a_left), ::Internal::Converter::ToString(a_right));
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsTrue);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsFalse);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsNone);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, NotNone);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Equals);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, NotEquals);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsLessThan);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsLessThanOrEqual);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsGreaterThan);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsGreaterThanOrEqual);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsInRange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, NotInRange);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RefEquals);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RefNotEquals);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, TypeEquals);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, TypeNotEquals);

		return true;
	}
}
