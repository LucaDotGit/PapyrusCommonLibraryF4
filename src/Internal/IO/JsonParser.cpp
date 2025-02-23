#include "Internal/IO/JsonParser.hpp"

namespace Internal::JsonParser
{
	using json_t = JsonTypes::json;

	static constexpr auto KEY_SEPARATOR = '/';

	static constexpr auto ALLOW_EXCEPTIONS = true;
	static constexpr auto IGNORE_COMMENTS = true;
	static constexpr auto ENSURE_ASCII = false;

	static const auto PARSER_CALLBACK = json_t::parser_callback_t();
	static constexpr auto ERROR_HANDLER = json_t::error_handler_t::replace;

	static constexpr auto INDENT_COUNT = 1;
	static constexpr auto INDENT_CHAR = '\t';

	std::optional<json_t::json_pointer> GetPointer(std::string_view a_key) noexcept
	{
		try {
			const auto key = a_key.starts_with(KEY_SEPARATOR) ? std::string(a_key) : KEY_SEPARATOR + std::string(a_key);
			return json_t::json_pointer(key);
		}
		catch (const std::exception&) {
			return std::nullopt;
		}
	}

	std::optional<json_t> Read(const std::filesystem::path& a_path) noexcept
	{
		try {
			const auto lock = std::shared_lock{ Internal::IOMutex::Get() };

			auto reader = std::ifstream(a_path);
			reader.exceptions(Internal::Errors::IO_FLAGS);

			return json_t::parse(reader, PARSER_CALLBACK, ALLOW_EXCEPTIONS, IGNORE_COMMENTS);
		}
		catch (const std::exception&) {
			return std::nullopt;
		}
	}

	bool Write(const std::filesystem::path& a_path, const json_t& a_root) noexcept
	{
		try {
			const auto lock = std::unique_lock{ Internal::IOMutex::Get() };

			auto writer = std::ofstream(a_path);
			writer.exceptions(Internal::Errors::IO_FLAGS);

			writer << a_root.dump(INDENT_COUNT, INDENT_CHAR, ENSURE_ASCII, ERROR_HANDLER);
			return writer.good();
		}
		catch (const std::exception&) {
			return false;
		}
	}

	bool Contains(const std::filesystem::path& a_path, std::string_view a_key) noexcept
	{
		const auto pointer = GetPointer(a_key);
		if (!pointer.has_value()) {
			return false;
		}

		const auto root = Read(a_path);
		if (!root.has_value()) {
			return false;
		}

		try {
			root->at(pointer.value());
			return true;
		}
		catch (const std::exception&) {
			return false;
		}
	}

	bool Remove(const std::filesystem::path& a_path, std::string_view a_key) noexcept
	{
		auto pointer = GetPointer(a_key);
		if (!pointer.has_value()) {
			return false;
		}

		auto root = Read(a_path);
		if (!root.has_value()) {
			return false;
		}

		try {
			auto& node = root->at(pointer->parent_pointer());
			node.erase(pointer->back());
		}
		catch (const std::exception&) {
			return false;
		}

		return Write(a_path, root.value());
	}

	bool Clear(const std::filesystem::path& a_path, std::string_view a_key) noexcept
	{
		auto pointer = GetPointer(a_key);
		if (!pointer.has_value()) {
			return false;
		}

		auto root = Read(a_path);
		if (!root.has_value()) {
			return false;
		}

		try {
			auto& node = root->at(pointer.value());
			node.clear();
		}
		catch (const std::exception&) {
			return false;
		}

		return Write(a_path, root.value());
	}

	RE::BSTSmartPointer<RE::BSScript::Struct> GetStruct(
		const std::filesystem::path& a_path,
		std::string_view a_key,
		const RE::BSTSmartPointer<RE::BSScript::StructTypeInfo>& a_typeInfo)
	{
		if (!a_typeInfo) {
			return nullptr;
		}

		const auto node = GetT(a_path, a_key, json_t());
		return JsonTypes::detail::GetStruct(node, a_typeInfo);
	}

	bool SetStruct(
		const std::filesystem::path& a_path,
		std::string_view a_key,
		const RE::BSTSmartPointer<RE::BSScript::Struct>& a_struct)
	{
		const auto node = JsonTypes::detail::SetStruct(a_struct);
		return SetT(a_path, a_key, node);
	}

	std::vector<RE::BSTSmartPointer<RE::BSScript::Struct>> GetStructArray(
		const std::filesystem::path& a_path,
		std::string_view a_key,
		const RE::BSTSmartPointer<RE::BSScript::StructTypeInfo>& a_typeInfo)
	{
		if (!a_typeInfo) {
			return {};
		}

		const auto node = GetT(a_path, a_key, json_t::array());

		auto array = std::vector<RE::BSTSmartPointer<RE::BSScript::Struct>>();
		array.reserve(node.size());

		for (const auto& element : node) {
			const auto structure = JsonTypes::detail::GetStruct(element, a_typeInfo);
			array.push_back(structure);
		}

		return array;
	}

	bool SetStructArray(
		const std::filesystem::path& a_path,
		std::string_view a_key,
		const std::vector<RE::BSTSmartPointer<RE::BSScript::Struct>>& a_structs)
	{
		auto array = json_t::array();
		array.get_ref<json_t::array_t&>().reserve(a_structs.size());

		for (const auto& structure : a_structs) {
			const auto value = JsonTypes::detail::SetStruct(structure);
			array.push_back(value);
		}

		return SetT(a_path, a_key, array);
	}

	const RE::BSScript::Variable* GetVar(
		const std::filesystem::path& a_path,
		std::string_view a_key)
	{
		const auto var = GetT(a_path, a_key, RE::BSScript::Variable());
		return new RE::BSScript::Variable(var);
	}

	bool SetVar(
		const std::filesystem::path& a_path,
		std::string_view a_key,
		const RE::BSScript::Variable* a_var)
	{
		if (!a_var) {
			return false;
		}

		const auto node = json_t(*a_var);
		return SetT(a_path, a_key, node);
	}

	std::vector<const RE::BSScript::Variable*> GetVarArray(
		const std::filesystem::path& a_path,
		std::string_view a_key)
	{
		const auto node = GetT(a_path, a_key, json_t::array());

		auto array = std::vector<const RE::BSScript::Variable*>();
		array.reserve(node.size());

		for (const auto& element : node) {
			const auto var = element.get<RE::BSScript::Variable>();
			const auto* value = new RE::BSScript::Variable(var);
			array.push_back(value);
		}

		return array;
	}

	bool SetVarArray(
		const std::filesystem::path& a_path,
		std::string_view a_key,
		const std::vector<const RE::BSScript::Variable*>& a_array)
	{
		auto array = json_t::array();
		array.get_ref<json_t::array_t&>().reserve(a_array.size());

		for (const auto* var : a_array) {
			auto value = var ? json_t(*var) : nullptr;
			array.push_back(std::move(value));
		}

		return SetT(a_path, a_key, array);
	}
}
