#pragma once

#include "Internal/IO/JsonTypes.hpp"

namespace Internal::JsonParser
{
	using json_t = JsonTypes::json;

	[[nodiscard]] std::optional<json_t::json_pointer> GetPointer(std::string_view a_key) noexcept;

	[[nodiscard]] std::optional<json_t> Read(const std::filesystem::path& a_path) noexcept;
	bool Write(const std::filesystem::path& a_path, const json_t& a_root) noexcept;

	[[nodiscard]] bool Contains(const std::filesystem::path& a_path, std::string_view a_key) noexcept;
	bool Remove(const std::filesystem::path& a_path, std::string_view a_key) noexcept;
	bool Clear(const std::filesystem::path& a_path, std::string_view a_key) noexcept;

	template <typename T>
	[[nodiscard]] T GetT(const std::filesystem::path& a_path, std::string_view a_key, T a_default) noexcept
	{
		const auto pointer = GetPointer(a_key);
		if (!pointer.has_value()) {
			return a_default;
		}

		const auto root = Read(a_path);
		if (!root.has_value()) {
			return a_default;
		}

		try {
			return root->value(pointer.value(), a_default);
		}
		catch (const std::exception&) {
			return a_default;
		}
	}

	template <typename T>
	bool SetT(const std::filesystem::path& a_path, std::string_view a_key, T&& a_value) noexcept
	{
		const auto pointer = GetPointer(a_key);
		if (!pointer.has_value()) {
			return false;
		}

		auto root = Read(a_path);
		if (!root.has_value()) {
			root = json_t();
		}

		try {
			root->operator[](pointer.value()) = std::forward<T>(a_value);
		}
		catch (const std::exception&) {
			return false;
		}

		return Write(a_path, root.value());
	}

	[[nodiscard]] RE::BSTSmartPointer<RE::BSScript::Struct> GetStruct(
		const std::filesystem::path& a_path,
		std::string_view a_key,
		const RE::BSTSmartPointer<RE::BSScript::StructTypeInfo>& a_typeInfo);
	bool SetStruct(
		const std::filesystem::path& a_path,
		std::string_view a_key,
		const RE::BSTSmartPointer<RE::BSScript::Struct>& a_struct);

	[[nodiscard]] std::vector<RE::BSTSmartPointer<RE::BSScript::Struct>> GetStructArray(
		const std::filesystem::path& a_path,
		std::string_view a_key,
		const RE::BSTSmartPointer<RE::BSScript::StructTypeInfo>& a_typeInfo);
	bool SetStructArray(
		const std::filesystem::path& a_path,
		std::string_view a_key,
		const std::vector<RE::BSTSmartPointer<RE::BSScript::Struct>>& a_structs);

	[[nodiscard]] const RE::BSScript::Variable* GetVar(
		const std::filesystem::path& a_path,
		std::string_view a_key);
	bool SetVar(
		const std::filesystem::path& a_path,
		std::string_view a_key,
		const RE::BSScript::Variable* a_var);

	[[nodiscard]] std::vector<const RE::BSScript::Variable*> GetVarArray(
		const std::filesystem::path& a_path,
		std::string_view a_key);
	bool SetVarArray(
		const std::filesystem::path& a_path,
		std::string_view a_key,
		const std::vector<const RE::BSScript::Variable*>& a_array);
}
