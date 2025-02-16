#pragma once

namespace Internal
{
	class VarMap
	{
	public:
		VarMap() noexcept = default;
		virtual ~VarMap() noexcept = default;

	public:
		[[nodiscard]] virtual std::vector<RE::BSFixedString> GetNamespaces() const;
		[[nodiscard]] virtual std::vector<RE::BSFixedString> GetKeys(const RE::BSFixedString& a_namespace) const;
		[[nodiscard]] virtual std::vector<const RE::BSScript::Variable*> GetValues(const RE::BSFixedString& a_namespace) const;

		[[nodiscard]] virtual std::vector<Pairs::Pair> GetPairs(const RE::BSFixedString& a_namespace) const;
		virtual bool SetPairs(const RE::BSFixedString& a_namespace, const std::vector<Pairs::Pair>& a_pairs);

		[[nodiscard]] virtual bool ContainsNamespace(const RE::BSFixedString& a_namespace) const;
		[[nodiscard]] virtual bool ContainsKey(const RE::BSFixedString& a_namespace, const RE::BSFixedString& a_key) const;

		[[nodiscard]] virtual const RE::BSScript::Variable* GetValue(
			const RE::BSFixedString& a_namespace,
			const RE::BSFixedString& a_key) const;
		[[nodiscard]] virtual const RE::BSScript::Variable* GetValueOrDefault(
			const RE::BSFixedString& a_namespace,
			const RE::BSFixedString& a_key,
			const RE::BSScript::Variable* a_default) const;
		virtual bool SetValue(
			const RE::BSFixedString& a_namespace,
			const RE::BSFixedString& a_key,
			const RE::BSScript::Variable* a_value);

		[[nodiscard]] virtual std::vector<const RE::BSScript::Variable*> GetArray(
			const RE::BSFixedString& a_namespace,
			const RE::BSFixedString& a_key) const;
		virtual bool SetArray(
			const RE::BSFixedString& a_namespace,
			const RE::BSFixedString& a_key,
			const std::vector<const RE::BSScript::Variable*>& a_values);

		virtual bool Remove(const RE::BSFixedString& a_namespace, const RE::BSFixedString& a_key);
		virtual bool Clear(const RE::BSFixedString& a_namespace);

	protected:
		mutable std::shared_mutex _mutex;
		Types::unordered_string_map<RE::BSFixedString, Types::unordered_string_map<RE::BSFixedString, RE::BSScript::Variable>> _variables;
	};
}
