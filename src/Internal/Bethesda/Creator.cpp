#include "Internal/Bethesda/Creator.hpp"

#include "Internal/Bethesda/ObjectLock.hpp"

namespace Internal::Creator
{
	RE::BSTSmartPointer<RE::BSScript::Object> CreateObject(
		const RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo>& a_typeInfo,
		const Types::unordered_string_map<std::string_view, RE::BSScript::Variable>& a_properties)
	{
		if (!a_typeInfo) {
			return nullptr;
		}

		const auto variableCount = a_typeInfo->GetTotalNumVariables();

		auto* object = RE::malloc<RE::BSScript::Object>(sizeof(RE::BSScript::Object) + variableCount * sizeof(RE::BSScript::Variable));
		new (object) RE::BSScript::Object();

		const auto* state = GetDefaultState(a_typeInfo);
		const auto& stateName = state ? state->name : RE::BSFixedString();

		object->handle = RE::GameScript::HandlePolicy::EMPTY_HANDLE;
		object->type = a_typeInfo;
		object->currentState = stateName;
		object->constructed = true;
		object->initialized = true;
		object->valid = true;

		ForEachVariable(a_typeInfo, [&](const RE::BSScript::ObjectTypeInfo::VariableInfo& a_variableInfo, std::uint32_t a_index) noexcept {
			auto defaultValue = GetDefaultValue(a_variableInfo.type);
			object->variables[a_index] = std::move(defaultValue);
			return RE::BSContainer::ForEachResult::kContinue;
		});

		if (!a_properties.empty()) {
			ForEachProperty(a_typeInfo, [&](const RE::BSScript::ObjectTypeInfo::PropertyInfo& a_propertyInfo) noexcept {
				const auto nameIt = a_properties.find(a_propertyInfo.name);
				if (nameIt != a_properties.end() && nameIt->second) {
					object->variables[a_propertyInfo.info.autoVarIndex] = nameIt->second;
				}

				return RE::BSContainer::ForEachResult::kContinue;
			});
		}

		return RE::BSTSmartPointer(object);
	}

	RE::BSTSmartPointer<RE::BSScript::Object> CopyObject(
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_object)
	{
		if (!a_object || !a_object->type) {
			return nullptr;
		}

		const auto lock = ObjectLock(a_object);
		const auto variableCount = a_object->type->GetTotalNumVariables();

		auto* object = RE::malloc<RE::BSScript::Object>(sizeof(RE::BSScript::Object) + variableCount * sizeof(RE::BSScript::Variable));
		new (object) RE::BSScript::Object();

		object->handle = RE::GameScript::HandlePolicy::EMPTY_HANDLE;
		object->type = a_object->type;
		object->currentState = a_object->currentState;
		object->constructed = a_object->constructed;
		object->initialized = a_object->initialized;
		object->valid = a_object->valid;

		if (object->IsValid()) {
			for (auto i = 0ui32; i < variableCount; i++) {
				auto copy = Copier::DeepCopy(&a_object->variables[i]);
				object->variables[i] = std::move(copy);
			}
		}

		return RE::BSTSmartPointer(object);
	}

	RE::BSScript::Variable* GetVariableValue(
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_object,
		const RE::BSFixedString& a_name)
	{
		if (!a_object || a_name.empty()) {
			return nullptr;
		}

		const auto lock = ObjectLock(a_object);

		auto varIndex = 0ui32;
		for (auto* typeInfo = a_object->type.get(); typeInfo; typeInfo = typeInfo->GetParent()) {
			const auto* varIt = typeInfo->GetVariableIter();
			const auto count = typeInfo->GetNumVariables();

			for (auto i = 0ui32; i < count; i++, varIndex++) {
				const auto& varInfo = varIt[i];
				if (varInfo.name == a_name) {
					return &a_object->variables[varIndex];
				}
			}
		}

		return nullptr;
	}

	bool SetVariableValue(
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_object,
		const RE::BSFixedString& a_name,
		const RE::BSScript::Variable* a_value)
	{
		if (!a_object || a_name.empty()) {
			return false;
		}

		const auto lock = ObjectLock(a_object);

		auto* variable = ::Internal::Creator::GetVariableValue(a_object, a_name);
		if (!variable) {
			return false;
		}

		const auto isVar = variable->is<RE::BSScript::Variable>();
		if (!isVar && !Comparer::TypeEquals(variable, a_value)) {
			return false;
		}

		auto value = Copier::Copy(a_value);
		if (isVar) {
			value = Copier::ToVarPtr(std::move(value));
		}

		*variable = std::move(value);
		return true;
	}

	RE::BSScript::Variable* GetAutoPropertyValue(
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_object,
		const RE::BSFixedString& a_name)
	{
		if (!a_object || a_name.empty()) {
			return nullptr;
		}

		const auto lock = ObjectLock(a_object);

		for (auto* typeInfo = a_object->type.get(); typeInfo; typeInfo = typeInfo->GetParent()) {
			const auto* propIt = typeInfo->GetPropertyIter();
			const auto count = typeInfo->GetNumProperties();

			for (auto i = 0ui32; i < count; i++) {
				const auto& property = propIt[i];
				if (property.name != a_name) {
					continue;
				}

				const auto varIndex = property.info.autoVarIndex;
				if (varIndex == std::numeric_limits<std::uint32_t>::max()) {
					return nullptr;
				}

				return &a_object->variables[varIndex];
			}
		}

		return nullptr;
	}

	bool SetAutoPropertyValue(
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_object,
		const RE::BSFixedString& a_name,
		const RE::BSScript::Variable* a_value)
	{
		if (!a_object || a_name.empty()) {
			return false;
		}

		const auto lock = ObjectLock(a_object);

		auto* property = GetAutoPropertyValue(a_object, a_name);
		if (!property) {
			return false;
		}

		const auto isVar = property->is<RE::BSScript::Variable>();
		if (!isVar && !Comparer::TypeEquals(property, a_value)) {
			return false;
		}

		auto value = Copier::Copy(a_value);
		if (isVar) {
			value = Copier::ToVarPtr(std::move(value));
		}

		*property = std::move(value);
		return true;
	}

	RE::BSScript::Variable GetDefaultValue(const RE::BSScript::TypeInfo& a_typeInfo) noexcept
	{
		auto value = RE::BSScript::Variable();
		auto* typeInfo = reinterpret_cast<RE::BSScript::TypeInfo*>(reinterpret_cast<std::uintptr_t>(&value) + 0x0);

		*typeInfo = a_typeInfo;
		return value;
	}

	RE::BSScript::ObjectTypeInfo::NamedStateInfo* GetDefaultState(
		const RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo>& a_typeInfo) noexcept
	{
		const auto count = a_typeInfo->GetNumNamedStates();
		if (count == 0) {
			return nullptr;
		}

		const auto index = a_typeInfo->initialState;
		auto* stateIt = a_typeInfo->GetNamedStateIter();

		return &stateIt[index];
	}

	RE::BSContainer::ForEachResult ForEachVariable(
		const RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo>& a_typeInfo,
		std::function<RE::BSContainer::ForEachResult(RE::BSScript::ObjectTypeInfo::VariableInfo&, std::uint32_t)> a_function) noexcept
	{
		auto varIndex = 0ui32;
		for (auto* typeInfo = a_typeInfo.get(); typeInfo; typeInfo = typeInfo->GetParent()) {
			auto* varIt = typeInfo->GetVariableIter();
			auto count = typeInfo->GetNumVariables();

			for (auto i = 0ui32; i < count; i++, varIndex++) {
				if (a_function(varIt[i], varIndex) == RE::BSContainer::ForEachResult::kStop) {
					return RE::BSContainer::ForEachResult::kStop;
				}
			}
		}

		return RE::BSContainer::ForEachResult::kContinue;
	}

	RE::BSContainer::ForEachResult ForEachProperty(
		const RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo>& a_typeInfo,
		std::function<RE::BSContainer::ForEachResult(RE::BSScript::ObjectTypeInfo::PropertyInfo&)> a_function) noexcept
	{
		for (auto* typeInfo = a_typeInfo.get(); typeInfo; typeInfo = typeInfo->GetParent()) {
			auto* propIt = typeInfo->GetPropertyIter();
			auto count = typeInfo->GetNumProperties();

			for (auto i = 0ui32; i < count; i++) {
				if (a_function(propIt[i]) == RE::BSContainer::ForEachResult::kStop) {
					return RE::BSContainer::ForEachResult::kStop;
				}
			}
		}

		return RE::BSContainer::ForEachResult::kContinue;
	}
}
