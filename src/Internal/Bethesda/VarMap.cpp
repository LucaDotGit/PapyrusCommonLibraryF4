#include "Internal/Bethesda/VarMap.hpp"

namespace Internal
{
	std::vector<RE::BSFixedString> VarMap::GetNamespaces() const
	{
		const auto lock = std::shared_lock{ _mutex };

		auto names = std::vector<RE::BSFixedString>();
		names.reserve(_variables.size());

		for (const auto& [name, _] : _variables) {
			names.push_back(name);
		}

		return names;
	}

	std::vector<RE::BSFixedString> VarMap::GetKeys(const RE::BSFixedString& a_namespace) const
	{
		const auto lock = std::shared_lock{ _mutex };

		const auto nameIt = _variables.find(a_namespace);
		if (nameIt == _variables.end()) {
			return {};
		}

		auto keys = std::vector<RE::BSFixedString>();
		keys.reserve(nameIt->second.size());

		for (const auto& [name, _] : nameIt->second) {
			keys.push_back(name);
		}

		return keys;
	}

	std::vector<const RE::BSScript::Variable*> VarMap::GetValues(const RE::BSFixedString& a_namespace) const
	{
		const auto lock = std::shared_lock{ _mutex };

		const auto nameIt = _variables.find(a_namespace);
		if (nameIt == _variables.end()) {
			return {};
		}

		auto values = std::vector<const RE::BSScript::Variable*>();
		values.reserve(nameIt->second.size());

		for (const auto& [_, var] : nameIt->second) {
			const auto value = Copier::CopyVar(&var);
			values.push_back(value);
		}

		return values;
	}

	std::vector<Pairs::Pair> VarMap::GetPairs(const RE::BSFixedString& a_namespace) const
	{
		const auto lock = std::shared_lock{ _mutex };

		const auto nameIt = _variables.find(a_namespace);
		if (nameIt == _variables.end()) {
			return {};
		}

		auto pairs = std::vector<Pairs::Pair>();
		pairs.reserve(nameIt->second.size());

		for (const auto& [name, var] : nameIt->second) {
			const auto* value = Copier::CopyVar(&var);

			auto pair = Pairs::MakePair(name, value);
			pairs.push_back(std::move(pair));
		}

		return pairs;
	}

	bool VarMap::SetPairs(const RE::BSFixedString& a_namespace,
		const std::vector<Pairs::Pair>& a_pairs)
	{
		const auto lock = std::unique_lock{ _mutex };

		auto& keys = _variables[a_namespace];

		for (const auto& pair : a_pairs) {
			if (!pair) {
				continue;
			}

			const auto&& [name, value] = Pairs::GetPair(pair);
			keys[name] = Copier::Copy(value);
		}

		return true;
	}

	bool VarMap::ContainsNamespace(const RE::BSFixedString& a_namespace) const
	{
		const auto lock = std::shared_lock{ _mutex };
		return _variables.contains(a_namespace);
	}

	bool VarMap::ContainsKey(const RE::BSFixedString& a_namespace,
		const RE::BSFixedString& a_key) const
	{
		const auto lock = std::shared_lock{ _mutex };

		const auto nameIt = _variables.find(a_namespace);
		if (nameIt == _variables.end()) {
			return false;
		}

		return nameIt->second.contains(a_key);
	}

	const RE::BSScript::Variable* VarMap::GetValue(
		const RE::BSFixedString& a_namespace,
		const RE::BSFixedString& a_key) const
	{
		const auto lock = std::shared_lock{ _mutex };

		const auto nameIt = _variables.find(a_namespace);
		if (nameIt == _variables.end()) {
			return nullptr;
		}

		const auto keyIt = nameIt->second.find(a_key);
		if (keyIt == nameIt->second.end()) {
			return nullptr;
		}

		return Copier::CopyVar(&keyIt->second);
	}

	const RE::BSScript::Variable* VarMap::GetValueOrDefault(
		const RE::BSFixedString& a_namespace,
		const RE::BSFixedString& a_key,
		const RE::BSScript::Variable* a_default) const
	{
		const auto lock = std::shared_lock{ _mutex };

		const auto nameIt = _variables.find(a_namespace);
		if (nameIt == _variables.end()) {
			return Copier::CopyVar(a_default);
		}

		const auto keyIt = nameIt->second.find(a_key);
		if (keyIt == nameIt->second.end()) {
			return Copier::CopyVar(a_default);
		}

		return Copier::CopyVar(&keyIt->second);
	}

	bool VarMap::SetValue(
		const RE::BSFixedString& a_namespace,
		const RE::BSFixedString& a_key,
		const RE::BSScript::Variable* a_value)
	{
		const auto lock = std::unique_lock{ _mutex };

		_variables[a_namespace][a_key] = Copier::Copy(a_value);
		return true;
	}

	std::vector<const RE::BSScript::Variable*> VarMap::GetArray(
		const RE::BSFixedString& a_namespace,
		const RE::BSFixedString& a_key) const
	{
		const auto lock = std::shared_lock{ _mutex };

		const auto nameIt = _variables.find(a_namespace);
		if (nameIt == _variables.end()) {
			return {};
		}

		const auto keyIt = nameIt->second.find(a_key);
		if (keyIt == nameIt->second.end()) {
			return {};
		}

		return Copier::VarToVarArray(&keyIt->second);
	}

	bool VarMap::SetArray(
		const RE::BSFixedString& a_namespace,
		const RE::BSFixedString& a_key,
		const std::vector<const RE::BSScript::Variable*>& a_values)
	{
		const auto lock = std::unique_lock{ _mutex };

		_variables[a_namespace][a_key] = Copier::VarArrayToVar(a_values);
		return true;
	}

	bool VarMap::Remove(const RE::BSFixedString& a_namespace,
		const RE::BSFixedString& a_key)
	{
		const auto lock = std::unique_lock{ _mutex };

		const auto nameIt = _variables.find(a_namespace);
		if (nameIt == _variables.end()) {
			return false;
		}

		const auto keyIt = nameIt->second.find(a_key);
		if (keyIt == nameIt->second.end()) {
			return false;
		}

		nameIt->second.erase(keyIt);
		return true;
	}

	bool VarMap::Clear(const RE::BSFixedString& a_namespace)
	{
		const auto lock = std::unique_lock{ _mutex };

		const auto nameIt = _variables.find(a_namespace);
		if (nameIt == _variables.end()) {
			return false;
		}

		nameIt->second.clear();
		return true;
	}
}
