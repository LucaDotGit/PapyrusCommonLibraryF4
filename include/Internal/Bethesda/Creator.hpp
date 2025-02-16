#pragma once

namespace Internal::Creator
{
	[[nodiscard]] RE::BSTSmartPointer<RE::BSScript::Object> CreateObject(
		const RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo>& a_typeInfo,
		const Types::unordered_string_map<std::string_view, RE::BSScript::Variable>& a_properties = {});

	[[nodiscard]] RE::BSTSmartPointer<RE::BSScript::Object> CopyObject(
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_object);

	[[nodiscard]] RE::BSScript::Variable* GetVariableValue(
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_object,
		const RE::BSFixedString& a_name);
	bool SetVariableValue(
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_object,
		const RE::BSFixedString& a_name,
		const RE::BSScript::Variable* a_value);

	[[nodiscard]] RE::BSScript::Variable* GetAutoPropertyValue(
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_object,
		const RE::BSFixedString& a_name);
	bool SetAutoPropertyValue(
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_object,
		const RE::BSFixedString& a_name,
		const RE::BSScript::Variable* a_value);

	[[nodiscard]] RE::BSScript::Variable GetDefaultValue(const RE::BSScript::TypeInfo& a_typeInfo) noexcept;
	[[nodiscard]] RE::BSScript::ObjectTypeInfo::NamedStateInfo* GetDefaultState(
		const RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo>& a_typeInfo) noexcept;

	RE::BSContainer::ForEachResult ForEachVariable(
		const RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo>& a_typeInfo,
		std::function<RE::BSContainer::ForEachResult(RE::BSScript::ObjectTypeInfo::VariableInfo&, std::uint32_t)> a_function) noexcept;

	RE::BSContainer::ForEachResult ForEachProperty(
		const RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo>& a_typeInfo,
		std::function<RE::BSContainer::ForEachResult(RE::BSScript::ObjectTypeInfo::PropertyInfo&)> a_function) noexcept;
}
