#include "Internal/IO/JsonTypes.hpp"

namespace Internal::JsonTypes::detail
{
	RE::BSTSmartPointer<RE::BSScript::Struct> GetStruct(
		const json& a_node,
		const RE::BSTSmartPointer<RE::BSScript::StructTypeInfo>& a_typeInfo)
	{
		if (!a_typeInfo || a_node.empty() || !a_node.is_object()) {
			return nullptr;
		}

		const auto vm = RE::GameVM::GetSingleton()->GetVM();

		auto structure = RE::BSTSmartPointer<RE::BSScript::Struct>();
		if (!vm->CreateStruct(a_typeInfo->name, structure)) {
			return nullptr;
		}

		for (const auto& [key, value] : a_node.items()) {
			const auto keyIt = a_typeInfo->varNameIndexMap.find(RE::BSFixedString(key));
			if (keyIt == a_typeInfo->varNameIndexMap.end()) {
				continue;
			}

			auto& element = structure->variables[keyIt->second];
			auto var = value.get<RE::BSScript::Variable>();

			if (element.is<RE::BSScript::Variable>() && !var.is<RE::BSScript::Variable>()) {
				element = new RE::BSScript::Variable(var);
				continue;
			}

			if (Comparer::TypeEquals(&var, &element)) {
				element = std::move(var);
			}
		}

		return structure;
	}

	JsonTypes::json SetStruct(const RE::BSTSmartPointer<RE::BSScript::Struct>& a_struct)
	{
		if (!a_struct) {
			return nullptr;
		}

		const auto& typeInfo = a_struct->type;
		if (!typeInfo) {
			return nullptr;
		}

		const auto lock = RE::BSAutoLock{ a_struct->structLock };

		auto node = json::object();
		for (const auto& [field, index] : typeInfo->varNameIndexMap) {
			const auto key = std::string{ field.data(), field.size() };
			node[key] = a_struct->variables[index];
		}

		return node;
	}
}

NLOHMANN_JSON_NAMESPACE_BEGIN
void adl_serializer<RE::TESForm*>::to_json(json_t& a_node, const RE::TESForm* a_form)
{
	if (!a_form) {
		a_node = nullptr;
		return;
	}

	const auto* mod = a_form->GetFile(0);
	if (!mod) {
		a_node = nullptr;
		return;
	}

	a_node[MOD_NAME_KEY] = mod->filename;
	a_node[FORM_ID_KEY] = a_form->GetLocalFormID();
}

void adl_serializer<RE::TESForm*>::from_json(const json_t& a_node, RE::TESForm*& a_form)
{
	if (a_node.empty() || !a_node.is_object()) {
		a_form = nullptr;
		return;
	}

	const auto nameIt = a_node.find(MOD_NAME_KEY);
	if (nameIt == a_node.end() || !nameIt->is_string()) {
		a_form = nullptr;
		return;
	}

	const auto formIt = a_node.find(FORM_ID_KEY);
	if (formIt == a_node.end() || !formIt->is_number_unsigned()) {
		a_form = nullptr;
		return;
	}

	const auto name = nameIt->get<std::string_view>();
	const auto formID = formIt->get<std::uint32_t>();

	const auto* dataHandler = RE::TESDataHandler::GetSingleton();
	a_form = dataHandler->LookupForm(formID, name);
}

void adl_serializer<RE::BSTSmartPointer<RE::BSScript::Struct>>::to_json(
	json_t& a_node,
	const RE::BSTSmartPointer<RE::BSScript::Struct>& a_struct)
{
	if (!a_struct) {
		a_node = nullptr;
		return;
	}

	a_node[STRUCT_NAME_KEY] = a_struct->type->name;
	a_node[VARIABLES_KEY] = Internal::JsonTypes::detail::SetStruct(a_struct);
}

void adl_serializer<RE::BSTSmartPointer<RE::BSScript::Struct>>::from_json(
	const json_t& a_node,
	RE::BSTSmartPointer<RE::BSScript::Struct>& a_struct)
{
	if (a_node.empty() || !a_node.is_object()) {
		a_struct = nullptr;
		return;
	}

	const auto nameIt = a_node.find(STRUCT_NAME_KEY);
	if (nameIt == a_node.end() || !nameIt->is_string()) {
		a_struct = nullptr;
		return;
	}

	const auto varIt = a_node.find(VARIABLES_KEY);
	if (varIt == a_node.end() || !varIt->is_object()) {
		a_struct = nullptr;
		return;
	}

	const auto structName = nameIt->get<RE::BSFixedString>();
	const auto vm = RE::GameVM::GetSingleton()->GetVM();

	auto typeInfo = RE::BSTSmartPointer<RE::BSScript::StructTypeInfo>();
	if (!vm->GetScriptStructType(structName, typeInfo)) {
		a_struct = nullptr;
		return;
	}

	a_struct = Internal::JsonTypes::detail::GetStruct(varIt.value(), typeInfo);
}

void adl_serializer<RE::BSTSmartPointer<RE::BSScript::Array>>::to_json(
	json_t& a_node,
	const RE::BSTSmartPointer<RE::BSScript::Array>& a_array)
{
	if (!a_array) {
		a_node = nullptr;
		return;
	}

	const auto lock = RE::BSAutoLock{ a_array->elementsLock };

	a_node = json_t::array();
	a_node.get_ref<json_t::array_t&>().reserve(a_array->elements.size());

	for (const auto& element : a_array->elements) {
		a_node.push_back(element);
	}
}

void adl_serializer<RE::BSTSmartPointer<RE::BSScript::Array>>::from_json(
	const json_t& a_node,
	RE::BSTSmartPointer<RE::BSScript::Array>& a_array)
{
	if (a_node.empty() || !a_node.is_array()) {
		a_array = nullptr;
		return;
	}

	const auto defaultType = RE::BSScript::TypeInfo(RE::BSScript::TypeInfo::RawType::kVar);

	const auto size = static_cast<std::uint32_t>(a_node.size());
	const auto vm = RE::GameVM::GetSingleton()->GetVM();

	if (!vm->CreateArray(defaultType, size, a_array)) {
		a_array = nullptr;
		return;
	}

	auto currentType = std::optional<RE::BSScript::TypeInfo>();

	for (auto i = 0ui32; i < size; i++) {
		auto element = a_node[i].get<RE::BSScript::Variable>();
		if (!element) {
			continue;
		}

		if (!currentType.has_value()) {
			currentType = element.GetType();
		}
		else if (!Internal::Comparer::TypeEquals(element.GetType(), currentType.value())) {
			currentType = defaultType;
		}

		a_array->elements[i] = std::move(element);
	}

	a_array->elementType = currentType.value_or(defaultType);
}

void adl_serializer<RE::BSScript::Variable*>::to_json(
	json_t& a_node,
	const RE::BSScript::Variable* a_var)
{
	if (!a_var || !*a_var) {
		a_node = nullptr;
		return;
	}

	a_node[VARIABLE_KEY] = *a_var;
}

void adl_serializer<RE::BSScript::Variable*>::from_json(
	const json_t& a_node,
	RE::BSScript::Variable*& a_var)
{
	if (a_node.empty() || !a_node.is_object()) {
		a_var = nullptr;
		return;
	}

	const auto varIt = a_node.find(VARIABLE_KEY);
	if (varIt == a_node.end()) {
		a_var = nullptr;
		return;
	}

	auto value = varIt->get<RE::BSScript::Variable>();
	a_var = new RE::BSScript::Variable(value);
}

void adl_serializer<RE::BSScript::Variable>::to_json(
	json_t& a_node,
	const RE::BSScript::Variable& a_var)
{
	if (!a_var) {
		a_node = nullptr;
		return;
	}

	using raw_type_t = RE::BSScript::TypeInfo::RawType;

	switch (a_var.GetType().GetRawType()) {
		case raw_type_t::kBool: {
			a_node = RE::BSScript::get<bool>(a_var);
			break;
		}
		case raw_type_t::kInt: {
			a_node = RE::BSScript::get<std::int32_t>(a_var);
			break;
		}
		case raw_type_t::kFloat: {
			a_node = RE::BSScript::get<float>(a_var);
			break;
		}
		case raw_type_t::kString: {
			a_node = RE::BSScript::get<RE::BSFixedString>(a_var);
			break;
		}
		case raw_type_t::kObject: {
			a_node = RE::BSScript::UnpackVariable<RE::TESForm>(a_var);
			break;
		}
		case raw_type_t::kStruct: {
			a_node = RE::BSScript::get<RE::BSScript::Struct>(a_var);
			break;
		}
		case raw_type_t::kVar: {
			a_node = RE::BSScript::get<RE::BSScript::Variable>(a_var);
			break;
		}
		case raw_type_t::kArrayBool:
		case raw_type_t::kArrayInt:
		case raw_type_t::kArrayFloat:
		case raw_type_t::kArrayString:
		case raw_type_t::kArrayObject:
		case raw_type_t::kArrayStruct:
		case raw_type_t::kArrayVar: {
			a_node = RE::BSScript::get<RE::BSScript::Array>(a_var);
			break;
		}
		default: {
			a_node = nullptr;
			break;
		}
	}
}

void adl_serializer<RE::BSScript::Variable>::from_json(
	const json_t& a_node,
	RE::BSScript::Variable& a_var)
{
	if (a_node.empty()) {
		a_var = nullptr;
		return;
	}

	a_var = RE::BSScript::Variable();

	switch (a_node.type()) {
		case json_t::value_t::boolean: {
			a_var = a_node.get<bool>();
			break;
		}
		case json_t::value_t::number_integer: {
			a_var = a_node.get<std::int32_t>();
			break;
		}
		case json_t::value_t::number_unsigned: {
			a_var = a_node.get<std::uint32_t>();
			break;
		}
		case json_t::value_t::number_float: {
			a_var = a_node.get<float>();
			break;
		}
		case json_t::value_t::string: {
			a_var = a_node.get<RE::BSFixedString>();
			break;
		}
		case json::value_t::object: {
			auto* var = a_node.get<RE::BSScript::Variable*>();
			if (var) {
				a_var = var;
				break;
			}

			const auto* form = a_node.get<RE::TESForm*>();
			if (form) {
				RE::BSScript::PackVariable(a_var, form);
				break;
			}

			const auto structure = a_node.get<RE::BSTSmartPointer<RE::BSScript::Struct>>();
			if (structure) {
				a_var = structure;
				break;
			}
			break;
		}
		case json::value_t::array: {
			a_var = a_node.get<RE::BSTSmartPointer<RE::BSScript::Array>>();
			break;
		}
		default: {
			a_var = nullptr;
			break;
		}
	}
}
NLOHMANN_JSON_NAMESPACE_END
