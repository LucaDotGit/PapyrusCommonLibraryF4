#pragma once

#include "Internal/IO/JsonParser.hpp"

namespace System::IO::JSON
{
	static constexpr auto SCRIPT_NAME = "System:IO:JSON"sv;

	static bool Contains(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::JsonParser::Contains(path, a_key);
	}

	static bool Remove(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::JsonParser::Remove(path, a_key);
	}

	static bool Clear(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::JsonParser::Clear(path, a_key);
	}

	static bool GetBool(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		bool a_default)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return a_default;
		}

		return ::Internal::JsonParser::GetT(path, a_key, a_default);
	}

	static bool SetBool(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		bool a_value)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::JsonParser::SetT(path, a_key, a_value);
	}

	static std::vector<bool> GetBoolArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		return ::Internal::JsonParser::GetT(path, a_key, std::vector<bool>());
	}

	static bool SetBoolArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		std::vector<bool> a_values)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::JsonParser::SetT(path, a_key, a_values);
	}

	static std::int32_t GetInt(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		std::int32_t a_default)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return a_default;
		}

		return ::Internal::JsonParser::GetT(path, a_key, a_default);
	}

	static bool SetInt(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		std::int32_t a_value)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::JsonParser::SetT(path, a_key, a_value);
	}

	static std::vector<std::int32_t> GetIntArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		return ::Internal::JsonParser::GetT(path, a_key, std::vector<std::int32_t>());
	}

	static bool SetIntArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		std::vector<std::int32_t> a_values)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::JsonParser::SetT(path, a_key, a_values);
	}

	static std::uint32_t GetUInt(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		std::uint32_t a_default)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return a_default;
		}

		return ::Internal::JsonParser::GetT(path, a_key, a_default);
	}

	static bool SetUInt(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		std::uint32_t a_value)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::JsonParser::SetT(path, a_key, a_value);
	}

	static std::vector<std::uint32_t> GetUIntArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		return ::Internal::JsonParser::GetT(path, a_key, std::vector<std::uint32_t>());
	}

	static bool SetUIntArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		std::vector<std::uint32_t> a_values)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::JsonParser::SetT(path, a_key, a_values);
	}

	static float GetFloat(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		float a_default)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return a_default;
		}

		return ::Internal::JsonParser::GetT(path, a_key, a_default);
	}

	static bool SetFloat(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		float a_value)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::JsonParser::SetT(path, a_key, a_value);
	}

	static std::vector<float> GetFloatArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		return ::Internal::JsonParser::GetT(path, a_key, std::vector<float>());
	}

	static bool SetFloatArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		std::vector<float> a_values)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::JsonParser::SetT(path, a_key, a_values);
	}

	static std::string GetString(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		std::string a_default)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return a_default;
		}

		return ::Internal::JsonParser::GetT(path, a_key, a_default);
	}

	static bool SetString(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		std::string_view a_value)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::JsonParser::SetT(path, a_key, a_value);
	}

	static std::vector<std::string> GetStringArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		return ::Internal::JsonParser::GetT(path, a_key, std::vector<std::string>());
	}

	static bool SetStringArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		std::vector<std::string_view> a_values)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::JsonParser::SetT(path, a_key, a_values);
	}

	static const RE::BSScript::Variable* GetVar(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		return ::Internal::JsonParser::GetVar(path, a_key);
	}

	static bool SetVar(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		const RE::BSScript::Variable* a_value)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::JsonParser::SetVar(path, a_key, a_value);
	}

	static std::vector<const RE::BSScript::Variable*> GetVarArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		return ::Internal::JsonParser::GetVarArray(path, a_key);
	}

	static bool SetVarArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		std::vector<const RE::BSScript::Variable*> a_values)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::JsonParser::SetVarArray(path, a_key, a_values);
	}

	static const RE::BSScript::Variable* GetStruct(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		RE::BSFixedString a_structName)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto typeInfo = RE::BSTSmartPointer<RE::BSScript::StructTypeInfo>();
		if (!a_vm.GetScriptStructType(a_structName, typeInfo)) {
			a_vm.PostError(fmt::format(::Internal::Errors::STRUCT_NAME_NOT_FOUND, a_structName),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		auto structure = ::Internal::JsonParser::GetStruct(path, a_key, typeInfo);
		return ::Internal::Copier::ToVarPtr(std::move(structure));
	}

	static bool SetStruct(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		const RE::BSScript::Variable* a_value)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		if (!a_value || !a_value->is<RE::BSScript::Struct>()) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto structure = RE::BSScript::get<RE::BSScript::Struct>(*a_value);
		if (!structure) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::JsonParser::SetStruct(path, a_key, structure);
	}

	static std::vector<const RE::BSScript::Variable*> GetStructArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		RE::BSFixedString a_structName)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto typeInfo = RE::BSTSmartPointer<RE::BSScript::StructTypeInfo>();
		if (!a_vm.GetScriptStructType(a_structName, typeInfo)) {
			a_vm.PostError(fmt::format(::Internal::Errors::STRUCT_NAME_NOT_FOUND, a_structName),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto structures = ::Internal::JsonParser::GetStructArray(path, a_key, typeInfo);

		auto array = std::vector<const RE::BSScript::Variable*>();
		array.reserve(structures.size());

		for (const auto& structure : structures) {
			const auto* value = ::Internal::Copier::ToVarPtr(structure);
			array.push_back(value);
		}

		return array;
	}

	static bool SetStructArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_key,
		std::vector<const RE::BSScript::Variable*> a_values)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto array = std::vector<RE::BSTSmartPointer<RE::BSScript::Struct>>();
		array.reserve(a_values.size());

		for (const auto* element : a_values) {
			if (!element || !element->is<RE::BSScript::Struct>()) {
				continue;
			}

			auto structure = RE::BSScript::get<RE::BSScript::Struct>(*element);
			array.push_back(std::move(structure));
		}

		return ::Internal::JsonParser::SetStructArray(path, a_key, array);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Contains);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Remove);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Clear);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetBool);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetBool);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetBoolArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetBoolArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetInt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetInt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetIntArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetIntArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetUInt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetUInt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetUIntArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetUIntArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetFloat);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetFloat);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetFloatArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetFloatArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetString);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetString);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetStringArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetStringArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetVar);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetVar);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetVarArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetVarArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetStruct);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetStruct);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetStructArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetStructArray);

		return true;
	}
}
