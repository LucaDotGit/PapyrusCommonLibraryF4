#pragma once

#include "Internal/Bethesda/VarMap.hpp"

namespace System::MemVar
{
	static constexpr auto SCRIPT_NAME = "System:MemVar"sv;

	static auto Map = ::Internal::VarMap();

	static std::vector<RE::BSFixedString> GetNamespaces(std::monostate)
	{
		return Map.GetNamespaces();
	}

	static std::vector<RE::BSFixedString> GetKeys(std::monostate,
		RE::BSFixedString a_namespace)
	{
		return Map.GetKeys(a_namespace);
	}

	static std::vector<const RE::BSScript::Variable*> GetValues(std::monostate,
		RE::BSFixedString a_namespace)
	{
		return Map.GetValues(a_namespace);
	}

	static std::vector<::Internal::Pairs::Pair> GetPairs(std::monostate,
		RE::BSFixedString a_namespace)
	{
		return Map.GetPairs(a_namespace);
	}

	static bool SetPairs(std::monostate,
		RE::BSFixedString a_namespace,
		std::vector<::Internal::Pairs::Pair> a_pairs)
	{
		return Map.SetPairs(a_namespace, a_pairs);
	}

	static bool ContainsNamespace(std::monostate,
		RE::BSFixedString a_namespace)
	{
		return Map.ContainsNamespace(a_namespace);
	}

	static bool ContainsKey(std::monostate,
		RE::BSFixedString a_namespace,
		RE::BSFixedString a_key)
	{
		return Map.ContainsKey(a_namespace, a_key);
	}

	static const RE::BSScript::Variable* GetValue(std::monostate,
		RE::BSFixedString a_namespace,
		RE::BSFixedString a_key)
	{
		return Map.GetValue(a_namespace, a_key);
	}

	static const RE::BSScript::Variable* GetValueOrDefault(std::monostate,
		RE::BSFixedString a_namespace,
		RE::BSFixedString a_key,
		const RE::BSScript::Variable* a_default)
	{
		return Map.GetValueOrDefault(a_namespace, a_key, a_default);
	}

	static bool SetValue(std::monostate,
		RE::BSFixedString a_namespace,
		RE::BSFixedString a_key,
		const RE::BSScript::Variable* a_value)
	{
		return Map.SetValue(a_namespace, a_key, a_value);
	}

	static std::vector<const RE::BSScript::Variable*> GetArray(std::monostate,
		RE::BSFixedString a_namespace,
		RE::BSFixedString a_key)
	{
		return Map.GetArray(a_namespace, a_key);
	}

	static bool SetArray(std::monostate,
		RE::BSFixedString a_namespace,
		RE::BSFixedString a_key,
		std::vector<const RE::BSScript::Variable*> a_values)
	{
		return Map.SetArray(a_namespace, a_key, a_values);
	}

	static bool Remove(std::monostate,
		RE::BSFixedString a_namespace,
		RE::BSFixedString a_key)
	{
		return Map.Remove(a_namespace, a_key);
	}

	static bool Clear(std::monostate,
		RE::BSFixedString a_namespace)
	{
		return Map.Clear(a_namespace);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
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
