#pragma once

namespace Internal::JsonTypes
{
	using json = nlohmann::basic_json<
		Types::json_map,
		std::vector,
		std::string,
		bool,
		std::int32_t,
		std::uint32_t,
		float>;

	namespace detail
	{
		[[nodiscard]] RE::BSTSmartPointer<RE::BSScript::Struct> GetStruct(
			const json& a_node,
			const RE::BSTSmartPointer<RE::BSScript::StructTypeInfo>& a_typeInfo);

		[[nodiscard]] json SetStruct(const RE::BSTSmartPointer<RE::BSScript::Struct>& a_struct);
	}
}

NLOHMANN_JSON_NAMESPACE_BEGIN
template <>
struct adl_serializer<RE::TESForm*> final
{
public:
	using json_t = Internal::JsonTypes::json;

public:
	static void to_json(json_t& a_node, const RE::TESForm*);
	static void from_json(const json_t& a_node, RE::TESForm*&);

private:
	inline static const auto FORM_MOD_NAME = "modName"s;
	inline static const auto FORMTYPE = "formID"s;
};

template <>
struct adl_serializer<RE::BSTSmartPointer<RE::BSScript::Struct>> final
{
public:
	using json_t = Internal::JsonTypes::json;

public:
	static void to_json(json_t& a_node, const RE::BSTSmartPointer<RE::BSScript::Struct>& a_struct);
	static void from_json(const json_t& a_node, RE::BSTSmartPointer<RE::BSScript::Struct>& a_struct);

private:
	inline static const auto STRUCT_NAME = "structName"s;
	inline static const auto STRUCT_VARIABLES = "variables"s;
};

template <>
struct adl_serializer<RE::BSTSmartPointer<RE::BSScript::Array>> final
{
public:
	using json_t = Internal::JsonTypes::json;

public:
	static void to_json(json_t& a_node, const RE::BSTSmartPointer<RE::BSScript::Array>& a_array);
	static void from_json(const json_t& a_node, RE::BSTSmartPointer<RE::BSScript::Array>& a_array);
};

template <>
struct adl_serializer<RE::BSScript::Variable> final
{
public:
	using json_t = Internal::JsonTypes::json;

public:
	static void to_json(json_t& a_node, const RE::BSScript::Variable& a_var);
	static void from_json(const json_t& a_node, RE::BSScript::Variable& a_var);
};
NLOHMANN_JSON_NAMESPACE_END
