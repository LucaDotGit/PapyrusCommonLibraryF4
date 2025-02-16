#pragma once

#include "Internal/Serialization/Types.hpp"

namespace Internal::Serialization::Serializer
{
	[[nodiscard]] RE::BSScript::Variable ReadRecordVar(
		const F4SE::SerializationInterface* a_interface);
	bool WriteRecordVar(
		const F4SE::SerializationInterface* a_interface,
		const RE::BSScript::Variable& a_value);

	template <typename T>
		requires std::is_trivially_copyable_v<T>
	[[nodiscard]] T ReadRecordT(const F4SE::SerializationInterface* a_interface)
	{
		auto value = T();
		a_interface->ReadRecordData(std::addressof(value), sizeof(value));
		return value;
	}

	template <typename T>
		requires std::is_trivially_copyable_v<std::remove_cvref_t<T>>
	bool WriteRecordT(const F4SE::SerializationInterface* a_interface, T&& a_value)
	{
		return a_interface->WriteRecordData(std::addressof(a_value), sizeof(a_value));
	}

	[[nodiscard]] RE::BSFixedString ReadRecordString(const F4SE::SerializationInterface* a_interface);
	bool WriteRecordString(const F4SE::SerializationInterface* a_interface, const RE::BSFixedString& a_value);

	[[nodiscard]] RE::BSTSmartPointer<RE::BSScript::Object> ReadRecordObject(
		const F4SE::SerializationInterface* a_interface);
	bool WriteRecordObject(
		const F4SE::SerializationInterface* a_interface,
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_object);

	[[nodiscard]] RE::BSTSmartPointer<RE::BSScript::Struct> ReadRecordStruct(
		const F4SE::SerializationInterface* a_interface);
	bool WriteRecordStruct(
		const F4SE::SerializationInterface* a_interface,
		const RE::BSTSmartPointer<RE::BSScript::Struct>& a_struct);

	[[nodiscard]] RE::BSTSmartPointer<RE::BSScript::Array> ReadRecordArray(
		const F4SE::SerializationInterface* a_interface,
		Serialization::vm_type_t a_type);
	bool WriteRecordArray(
		const F4SE::SerializationInterface* a_interface,
		const RE::BSTSmartPointer<RE::BSScript::Array>& a_array);
}
