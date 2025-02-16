#pragma once

#include "Internal/Serialization/Types.hpp"

namespace Internal::Serialization::StringMap
{
	bool Load(const F4SE::SerializationInterface* a_interface,
		std::uint32_t a_recordType,
		std::uint32_t a_recordVersion,
		std::uint32_t a_recordLength);
	void Save(const F4SE::SerializationInterface* a_interface);
	void Revert(const F4SE::SerializationInterface* a_interface);

	[[nodiscard]] bool Contains(Serialization::size_t a_index);
	[[nodiscard]] bool Contains(const RE::BSFixedString& a_key);
	[[nodiscard]] std::optional<RE::BSFixedString> GetString(Serialization::size_t a_index);
	[[nodiscard]] std::optional<Serialization::size_t> GetIndex(const RE::BSFixedString& a_key);
	Serialization::size_t AddString(const RE::BSFixedString& a_key);
	bool AddVar(const RE::BSScript::Variable& a_var);
	void Clear();
}
