#pragma once

#include "Internal/Bethesda/VarMap.hpp"

namespace Internal::Serialization
{
	class SaveVarMap final
		: public REX::Singleton<SaveVarMap>,
		  public VarMap
	{
	public:
		void Setup();
		void Hash();
		bool Load(const F4SE::SerializationInterface* a_interface,
			std::uint32_t a_recordType,
			std::uint32_t a_recordVersion,
			std::uint32_t a_recordLength);
		void Save(const F4SE::SerializationInterface* a_interface) const;
		void Revert(const F4SE::SerializationInterface* a_interface);

	public:
		[[nodiscard]] bool IsNamespaceValid(const RE::BSFixedString& a_namespace) const;
		bool SetPairs(const RE::BSFixedString& a_namespace, const std::vector<Pairs::Pair>& a_pairs) override;
		bool SetValue(const RE::BSFixedString& a_namespace, const RE::BSFixedString& a_key, const RE::BSScript::Variable* a_value) override;

	private:
		Types::unordered_string_set<RE::BSFixedString> _validNamespaces;
	};
}
