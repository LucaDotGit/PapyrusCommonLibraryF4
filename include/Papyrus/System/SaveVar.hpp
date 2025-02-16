#pragma once

#include "Internal/Serialization/SaveVarMap.hpp"

namespace System::SaveVar
{
	static constexpr auto SCRIPT_NAME = "System:SaveVar"sv;

	static bool IsNamespaceValid(std::monostate,
		RE::BSFixedString a_namespace)
	{
		return ::Internal::Serialization::SaveVarMap::GetSingleton()->IsNamespaceValid(a_namespace);
	}

	static std::vector<RE::BSFixedString> GetNamespaces(std::monostate)
	{
		return ::Internal::Serialization::SaveVarMap::GetSingleton()->GetNamespaces();
	}

	static std::vector<RE::BSFixedString> GetKeys(std::monostate,
		RE::BSFixedString a_namespace)
	{
		return ::Internal::Serialization::SaveVarMap::GetSingleton()->GetKeys(a_namespace);
	}

	static std::vector<const RE::BSScript::Variable*> GetValues(std::monostate,
		RE::BSFixedString a_namespace)
	{
		return ::Internal::Serialization::SaveVarMap::GetSingleton()->GetValues(a_namespace);
	}

	static std::vector<::Internal::Pairs::Pair> GetPairs(std::monostate,
		RE::BSFixedString a_namespace)
	{
		return ::Internal::Serialization::SaveVarMap::GetSingleton()->GetPairs(a_namespace);
	}

	static bool SetPairs(std::monostate,
		RE::BSFixedString a_namespace,
		std::vector<::Internal::Pairs::Pair> a_pairs)
	{
		return ::Internal::Serialization::SaveVarMap::GetSingleton()->SetPairs(a_namespace, a_pairs);
	}

	static bool ContainsNamespace(std::monostate,
		RE::BSFixedString a_namespace)
	{
		return ::Internal::Serialization::SaveVarMap::GetSingleton()->ContainsNamespace(a_namespace);
	}

	static bool ContainsKey(std::monostate,
		RE::BSFixedString a_namespace,
		RE::BSFixedString a_key)
	{
		return ::Internal::Serialization::SaveVarMap::GetSingleton()->ContainsKey(a_namespace, a_key);
	}

	static const RE::BSScript::Variable* GetValue(std::monostate,
		RE::BSFixedString a_namespace,
		RE::BSFixedString a_key)
	{
		return ::Internal::Serialization::SaveVarMap::GetSingleton()->GetValue(a_namespace, a_key);
	}

	static const RE::BSScript::Variable* GetValueOrDefault(std::monostate,
		RE::BSFixedString a_namespace,
		RE::BSFixedString a_key,
		const RE::BSScript::Variable* a_default)
	{
		return ::Internal::Serialization::SaveVarMap::GetSingleton()->GetValueOrDefault(a_namespace, a_key, a_default);
	}

	static bool SetValue(std::monostate,
		RE::BSFixedString a_namespace,
		RE::BSFixedString a_key,
		const RE::BSScript::Variable* a_value)
	{
		return ::Internal::Serialization::SaveVarMap::GetSingleton()->SetValue(a_namespace, a_key, a_value);
	}

	static std::vector<const RE::BSScript::Variable*> GetArray(std::monostate,
		RE::BSFixedString a_namespace,
		RE::BSFixedString a_key)
	{
		return ::Internal::Serialization::SaveVarMap::GetSingleton()->GetArray(a_namespace, a_key);
	}

	static bool SetArray(std::monostate,
		RE::BSFixedString a_namespace,
		RE::BSFixedString a_key,
		std::vector<const RE::BSScript::Variable*> a_values)
	{
		return ::Internal::Serialization::SaveVarMap::GetSingleton()->SetArray(a_namespace, a_key, a_values);
	}

	static bool Remove(std::monostate,
		RE::BSFixedString a_namespace,
		RE::BSFixedString a_key)
	{
		return ::Internal::Serialization::SaveVarMap::GetSingleton()->Remove(a_namespace, a_key);
	}

	static bool Clear(std::monostate,
		RE::BSFixedString a_namespace)
	{
		return ::Internal::Serialization::SaveVarMap::GetSingleton()->Clear(a_namespace);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsNamespaceValid);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetNamespaces);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetKeys);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetValues);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetPairs);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetPairs);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ContainsNamespace);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ContainsKey);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetValue);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetValueOrDefault);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetValue);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Remove);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Clear);

		return true;
	}
}
