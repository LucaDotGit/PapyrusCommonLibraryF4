#pragma once

#include "Internal/Bethesda/Creator.hpp"

namespace System::ScriptObject
{
	static constexpr auto SCRIPT_NAME = "System:ScriptObject"sv;

	static RE::BSTSmartPointer<RE::BSScript::Object> Create(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BSFixedString a_scriptName,
		std::vector<::Internal::Pairs::Pair> a_properties)
	{
		auto typeInfo = RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo>();
		if (!a_vm.GetScriptObjectType(a_scriptName, typeInfo)) {
			a_vm.PostError(fmt::format(::Internal::Errors::SCRIPT_NAME_NOT_FOUND, a_scriptName),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto properties = ::Internal::Types::unordered_string_map<std::string_view, RE::BSScript::Variable>();
		properties.reserve(a_properties.size());

		for (const auto& property : a_properties) {
			if (!property) {
				continue;
			}

			const auto&& [name, value] = ::Internal::Pairs::GetPair(property);
			properties[name] = ::Internal::Copier::Copy(value);
		}

		return ::Internal::Creator::CreateObject(typeInfo, properties);
	}

	static RE::BSTSmartPointer<RE::BSScript::Object> Copy(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BSTSmartPointer<RE::BSScript::Object> a_object)
	{
		if (!a_object) {
			a_vm.PostError(::Internal::Errors::SCRIPT_OBJECT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		return ::Internal::Creator::CopyObject(a_object);
	}

	static bool Exists(RE::BSScript::IVirtualMachine& a_vm, std::uint32_t, std::monostate,
		RE::BSFixedString a_scriptName)
	{
		auto typeInfo = RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo>();
		return a_vm.GetScriptObjectType(a_scriptName, typeInfo);
	}

	static bool IsLoaded(RE::BSScript::IVirtualMachine& a_vm, std::uint32_t, std::monostate,
		RE::BSFixedString a_scriptName)
	{
		auto typeInfo = RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo>();
		return a_vm.GetScriptObjectTypeNoLoad(a_scriptName, typeInfo);
	}

	static bool IsRegisteredForRemoteEvent(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BSTSmartPointer<RE::BSScript::Object> a_object,
		RE::BSTSmartPointer<RE::BSScript::Object> a_sender,
		RE::BSFixedString a_eventName)
	{
		if (!a_object || !a_sender) {
			a_vm.PostError(::Internal::Errors::SCRIPT_OBJECT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto* vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();

		const auto lock = RE::BSAutoLock{ vm->eventRelayLock };
		const auto scriptIt = vm->eventRelays.find(a_sender->handle);

		if (scriptIt == vm->eventRelays.end()) {
			return false;
		}

		const auto& eventRelay = scriptIt->second;
		const auto eventIt = eventRelay->events.find(a_eventName);

		if (eventIt == eventRelay->events.end()) {
			return false;
		}

		const auto& targetList = eventIt->second;
		return targetList->targets.contains(a_object);
	}

	static bool IsInstanceOf(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BSTSmartPointer<RE::BSScript::Object> a_object,
		RE::BSFixedString a_scriptName)
	{
		if (!a_object) {
			a_vm.PostError(::Internal::Errors::SCRIPT_OBJECT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto thisTypeInfo = a_object->type;
		if (!thisTypeInfo) {
			return false;
		}

		if (thisTypeInfo->name == a_scriptName) {
			return true;
		}

		for (auto parent = thisTypeInfo->parentTypeInfo; parent; parent = parent->parentTypeInfo) {
			if (parent->name == a_scriptName) {
				return true;
			}
		}

		return false;
	}

	static RE::BSFixedString GetName(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BSTSmartPointer<RE::BSScript::Object> a_object)
	{
		if (!a_object) {
			a_vm.PostError(::Internal::Errors::SCRIPT_OBJECT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		return a_object->type->name;
	}

	static RE::BSFixedString GetParentName(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BSTSmartPointer<RE::BSScript::Object> a_object)
	{
		if (!a_object) {
			a_vm.PostError(::Internal::Errors::SCRIPT_OBJECT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto* parent = a_object->type->GetParent();
		return parent ? parent->name : nullptr;
	}

	static const RE::BSScript::Variable* GetVariableValue(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BSTSmartPointer<RE::BSScript::Object> a_object,
		RE::BSFixedString a_name)
	{
		if (!a_object) {
			a_vm.PostError(::Internal::Errors::SCRIPT_OBJECT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto* var = ::Internal::Creator::GetVariableValue(a_object, a_name);
		if (!var) {
			a_vm.PostError(fmt::format("The variable \"{}\" does not exist", a_name),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		return ::Internal::Copier::CopyVar(var);
	}

	static bool SetVariableValue(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BSTSmartPointer<RE::BSScript::Object> a_object,
		RE::BSFixedString a_name,
		const RE::BSScript::Variable* a_value)
	{
		if (!a_object) {
			a_vm.PostError(::Internal::Errors::SCRIPT_OBJECT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::Creator::SetVariableValue(a_object, a_name, a_value);
	}

	static const RE::BSScript::Variable* GetAutoPropertyValue(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BSTSmartPointer<RE::BSScript::Object> a_object,
		RE::BSFixedString a_name)
	{
		if (!a_object) {
			a_vm.PostError(::Internal::Errors::SCRIPT_OBJECT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto* property = ::Internal::Creator::GetAutoPropertyValue(a_object, a_name);
		if (!property) {
			a_vm.PostError(fmt::format("The auto property \"{}\" does not exist", a_name),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		return ::Internal::Copier::CopyVar(property);
	}

	static bool SetAutoPropertyValue(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BSTSmartPointer<RE::BSScript::Object> a_object,
		RE::BSFixedString a_name,
		const RE::BSScript::Variable* a_value)
	{
		if (!a_object) {
			a_vm.PostError(::Internal::Errors::SCRIPT_OBJECT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::Creator::SetAutoPropertyValue(a_object, a_name, a_value);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Create);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Copy);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Exists);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsLoaded);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsInstanceOf);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForRemoteEvent);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetName);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetParentName);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetVariableValue);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetVariableValue);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetAutoPropertyValue);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetAutoPropertyValue);

		return true;
	}
}
