#include "Internal/Serialization/Serializer.hpp"

#include "Internal/Serialization/StringMap.hpp"

namespace Internal::Serialization::Serializer
{
	RE::BSScript::Variable ReadRecordVar(
		const F4SE::SerializationInterface* a_interface)
	{
		const auto type = ReadRecordT<Serialization::vm_type_t>(a_interface);
		auto value = RE::BSScript::Variable();

		switch (static_cast<RE::BSScript::TypeInfo::RawType>(type)) {
			case RE::BSScript::TypeInfo::RawType::kNone: {
				value = ReadRecordT<std::nullptr_t>(a_interface);
				break;
			}
			case RE::BSScript::TypeInfo::RawType::kBool: {
				value = ReadRecordT<bool>(a_interface);
				break;
			}
			case RE::BSScript::TypeInfo::RawType::kInt: {
				value = ReadRecordT<std::int32_t>(a_interface);
				break;
			}
			case RE::BSScript::TypeInfo::RawType::kFloat: {
				value = ReadRecordT<float>(a_interface);
				break;
			}
			case RE::BSScript::TypeInfo::RawType::kString: {
				value = ReadRecordString(a_interface);
				break;
			}
			case RE::BSScript::TypeInfo::RawType::kObject: {
				value = ReadRecordObject(a_interface);
				break;
			}
			case RE::BSScript::TypeInfo::RawType::kStruct: {
				value = ReadRecordStruct(a_interface);
				break;
			}
			case RE::BSScript::TypeInfo::RawType::kVar: {
				const auto var = ReadRecordVar(a_interface);
				value = Copier::CopyVar(&var);
				break;
			}
			case RE::BSScript::TypeInfo::RawType::kArrayBool:
			case RE::BSScript::TypeInfo::RawType::kArrayInt:
			case RE::BSScript::TypeInfo::RawType::kArrayFloat:
			case RE::BSScript::TypeInfo::RawType::kArrayString:
			case RE::BSScript::TypeInfo::RawType::kArrayObject:
			case RE::BSScript::TypeInfo::RawType::kArrayStruct:
			case RE::BSScript::TypeInfo::RawType::kArrayVar: {
				value = ReadRecordArray(a_interface, type);
				break;
			}
		}

		return value;
	}

	bool WriteRecordVar(
		const F4SE::SerializationInterface* a_interface,
		const RE::BSScript::Variable& a_value)
	{
		const auto type = static_cast<Serialization::vm_type_t>(a_value.GetType().GetRawType());
		if (!WriteRecordT(a_interface, type)) {
			return false;
		}

		switch (static_cast<RE::BSScript::TypeInfo::RawType>(type)) {
			case RE::BSScript::TypeInfo::RawType::kNone: {
				const auto value = RE::BSScript::get<std::nullptr_t>(a_value);
				return WriteRecordT(a_interface, value);
			}
			case RE::BSScript::TypeInfo::RawType::kBool: {
				const auto value = RE::BSScript::get<bool>(a_value);
				return WriteRecordT(a_interface, value);
			}
			case RE::BSScript::TypeInfo::RawType::kInt: {
				const auto value = RE::BSScript::get<std::int32_t>(a_value);
				return WriteRecordT(a_interface, value);
			}
			case RE::BSScript::TypeInfo::RawType::kFloat: {
				const auto value = RE::BSScript::get<float>(a_value);
				return WriteRecordT(a_interface, value);
			}
			case RE::BSScript::TypeInfo::RawType::kString: {
				const auto value = RE::BSScript::get<RE::BSFixedString>(a_value);
				return WriteRecordString(a_interface, value);
			}
			case RE::BSScript::TypeInfo::RawType::kObject: {
				const auto value = RE::BSScript::get<RE::BSScript::Object>(a_value);
				return WriteRecordObject(a_interface, value);
			}
			case RE::BSScript::TypeInfo::RawType::kStruct: {
				const auto value = RE::BSScript::get<RE::BSScript::Struct>(a_value);
				return WriteRecordStruct(a_interface, value);
			}
			case RE::BSScript::TypeInfo::RawType::kVar: {
				const auto* value = RE::BSScript::get<RE::BSScript::Variable>(a_value);
				const auto var = Copier::Copy(value);
				return WriteRecordVar(a_interface, var);
			}
			case RE::BSScript::TypeInfo::RawType::kArrayBool:
			case RE::BSScript::TypeInfo::RawType::kArrayInt:
			case RE::BSScript::TypeInfo::RawType::kArrayFloat:
			case RE::BSScript::TypeInfo::RawType::kArrayString:
			case RE::BSScript::TypeInfo::RawType::kArrayObject:
			case RE::BSScript::TypeInfo::RawType::kArrayStruct:
			case RE::BSScript::TypeInfo::RawType::kArrayVar: {
				const auto value = RE::BSScript::get<RE::BSScript::Array>(a_value);
				return WriteRecordArray(a_interface, value);
			}
			default: {
				return false;
			}
		}
	}

	RE::BSFixedString ReadRecordString(const F4SE::SerializationInterface* a_interface)
	{
		const auto index = ReadRecordT<Serialization::size_t>(a_interface);
		const auto string = StringMap::GetString(index);

		if (!string.has_value()) {
			logger::error("Serialization: Failed to read string from index {}"sv, index);
			assert(false);
			return {};
		}

		return string.value();
	}

	bool WriteRecordString(const F4SE::SerializationInterface* a_interface, const RE::BSFixedString& a_value)
	{
		const auto index = StringMap::GetIndex(a_value);
		if (!index.has_value()) {
			logger::error("Serialization: Failed to write string \"{}\""sv, a_value);
			assert(false);
			return false;
		}

		return WriteRecordT(a_interface, index.value_or(std::numeric_limits<Serialization::size_t>::max()));
	}

	RE::BSTSmartPointer<RE::BSScript::Object> ReadRecordObject(
		const F4SE::SerializationInterface* a_interface)
	{
		auto handle = ReadRecordT<RE::VMHandle>(a_interface);
		if (handle >= 0 || handle <= RE::GameScript::HandlePolicy::EMPTY_HANDLE) {
			return nullptr;
		}

		const auto resolvedHandle = a_interface->ResolveHandle(handle);
		if (!resolvedHandle.has_value()) {
			return nullptr;
		}

		handle = resolvedHandle.value();

		const auto vm = RE::GameVM::GetSingleton()->GetVM();
		const auto& handles = vm->GetObjectHandlePolicy();

		auto typeID = static_cast<RE::VMTypeID>(0);
		if (!handles.GetHandleType(handle, typeID)) {
			return nullptr;
		}

		auto typeInfo = RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo>();
		if (!vm->GetScriptObjectType(typeID, typeInfo)) {
			return nullptr;
		}

		auto object = RE::BSTSmartPointer<RE::BSScript::Object>();
		if (vm->FindBoundObject(handle, typeInfo->name.data(), false, object, false)) {
			return object;
		}

		if (!vm->CreateObject(typeInfo->name, object)) {
			return nullptr;
		}

		auto& bindings = vm->GetObjectBindPolicy();
		bindings.BindObject(object, handle);
		return object;
	}

	bool WriteRecordObject(
		const F4SE::SerializationInterface* a_interface,
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_object)
	{
		const auto handle = a_object ? a_object->handle : 0;
		return WriteRecordT(a_interface, handle);
	}

	RE::BSTSmartPointer<RE::BSScript::Struct> ReadRecordStruct(
		const F4SE::SerializationInterface* a_interface)
	{
		const auto vm = RE::GameVM::GetSingleton()->GetVM();

		const auto typeName = ReadRecordString(a_interface);
		const auto size = ReadRecordT<Serialization::size_t>(a_interface);

		if (typeName.empty()) {
			return nullptr;
		}

		auto structure = RE::BSTSmartPointer<RE::BSScript::Struct>();
		auto createdStruct = vm->CreateStruct(typeName, structure);

		const auto& typeInfo = structure->type;

		for (auto i = static_cast<Serialization::size_t>(0); i < size; i++) {
			auto name = ReadRecordString(a_interface);
			auto var = ReadRecordVar(a_interface);

			if (!createdStruct) {
				continue;
			}

			const auto nameIt = typeInfo->varNameIndexMap.find(name);
			if (nameIt == typeInfo->varNameIndexMap.end()) {
				continue;
			}

			const auto index = nameIt->second;
			if (Comparer::TypeEquals(&var, &structure->variables[index])) {
				structure->variables[index] = std::move(var);
			}
		}

		return structure;
	}

	bool WriteRecordStruct(
		const F4SE::SerializationInterface* a_interface,
		const RE::BSTSmartPointer<RE::BSScript::Struct>& a_struct)
	{
		if (!a_struct) {
			return WriteRecordString(a_interface, nullptr) &&
				   WriteRecordT(a_interface, static_cast<Serialization::size_t>(0));
		}

		const auto lock = RE::BSAutoLock{ a_struct->structLock };

		const auto& typeInfo = a_struct->type;
		if (!typeInfo) {
			return WriteRecordString(a_interface, nullptr) &&
				   WriteRecordT(a_interface, static_cast<Serialization::size_t>(0));
		}

		const auto& typeName = typeInfo->name;
		if (!WriteRecordString(a_interface, typeName)) {
			return false;
		}

		const auto size = static_cast<Serialization::size_t>(typeInfo->variables.size());
		if (!WriteRecordT(a_interface, size)) {
			return false;
		}

		for (const auto& [name, index] : typeInfo->varNameIndexMap) {
			if (!WriteRecordString(a_interface, name) ||
				!WriteRecordVar(a_interface, a_struct->variables[index])) {
				return false;
			}
		}

		return true;
	}

	RE::BSTSmartPointer<RE::BSScript::Array> ReadRecordArray(
		const F4SE::SerializationInterface* a_interface,
		Serialization::vm_type_t a_type)
	{
		const auto vm = RE::GameVM::GetSingleton()->GetVM();

		const auto size = ReadRecordT<Serialization::size_t>(a_interface);
		const auto type = static_cast<RE::BSScript::TypeInfo::RawType>(
			a_type - static_cast<Serialization::vm_type_t>(RE::BSScript::TypeInfo::RawType::kArrayStart));

		auto array = RE::BSTSmartPointer<RE::BSScript::Array>();
		auto createdArray = vm->CreateArray(type, size, array);

		for (auto i = static_cast<Serialization::size_t>(0); i < size; i++) {
			auto element = ReadRecordVar(a_interface);
			if (createdArray && Comparer::TypeEquals(&element, &array->elements[i])) {
				array->elements[i] = std::move(element);
			}
		}

		return array;
	}

	bool WriteRecordArray(
		const F4SE::SerializationInterface* a_interface,
		const RE::BSTSmartPointer<RE::BSScript::Array>& a_array)
	{
		if (!a_array) {
			return WriteRecordT(a_interface, static_cast<Serialization::size_t>(0));
		}

		const auto lock = RE::BSAutoLock{ a_array->elementsLock };

		const auto size = static_cast<Serialization::size_t>(a_array->size());
		if (!WriteRecordT(a_interface, size)) {
			return false;
		}

		for (auto i = static_cast<Serialization::size_t>(0); i < size; i++) {
			if (!WriteRecordVar(a_interface, a_array->elements[i])) {
				return false;
			}
		}

		return true;
	}
}
