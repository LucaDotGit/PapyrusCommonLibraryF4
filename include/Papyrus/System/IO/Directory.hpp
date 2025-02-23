#pragma once

#include "Internal/IO/Wildcards.hpp"

namespace System::IO::Directory
{
	static constexpr auto SCRIPT_NAME = "System:IO:Directory"sv;

	static std::vector<std::string> GetEntriesImpl(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID,
		std::string_view a_path,
		std::string_view a_searchPattern,
		bool a_recursive,
		std::function<bool(const std::filesystem::directory_entry&)> a_predicate)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto lock = std::shared_lock{ ::Internal::IOMutex::Get() };

		auto isDirError = std::error_code();
		if (!std::filesystem::is_directory(path, isDirError)) {
			return {};
		}

		auto entryError = std::error_code();
		auto entries = std::vector<std::string>();

		const auto iterateContent = [&](const auto& a_iterator) {
			for (const std::filesystem::directory_entry& dirEntry : a_iterator) {
				if (!a_predicate(dirEntry)) {
					continue;
				}

				const auto& entryPath = dirEntry.path();
				if (a_searchPattern.empty() || ::Internal::Wildcards::IsMatch(entryPath.filename().string(), a_searchPattern)) {
					entries.emplace_back(entryPath.string());
				}
			}
		};

		constexpr auto DIR_OPTIONS = std::filesystem::directory_options::skip_permission_denied;

		if (a_recursive) {
			const auto iterator = std::filesystem::recursive_directory_iterator(path, DIR_OPTIONS, entryError);
			if (entryError) {
				return {};
			}

			iterateContent(iterator);
		}
		else {
			const auto iterator = std::filesystem::directory_iterator(path, DIR_OPTIONS, entryError);
			if (entryError) {
				return {};
			}

			iterateContent(iterator);
		}

		return entries;
	}

	static std::vector<std::string> GetDirectories(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string a_searchPattern,
		bool a_recursive)
	{
		return GetEntriesImpl(a_vm, a_stackID, a_path, a_searchPattern, a_recursive, [](const std::filesystem::directory_entry& a_entry) {
			auto isDirError = std::error_code();
			return a_entry.is_directory(isDirError);
		});
	}

	static std::vector<std::string> GetFiles(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string a_searchPattern,
		bool a_recursive)
	{
		return GetEntriesImpl(a_vm, a_stackID, a_path, a_searchPattern, a_recursive, [](const std::filesystem::directory_entry& a_entry) {
			auto isDirError = std::error_code();
			return a_entry.is_regular_file(isDirError);
		});
	}

	static bool Exists(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto lock = std::shared_lock{ ::Internal::IOMutex::Get() };

		auto isDirError = std::error_code();
		return std::filesystem::is_directory(path, isDirError);
	}

	static bool Create(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto lock = std::unique_lock{ ::Internal::IOMutex::Get() };

		auto createError = std::error_code();
		return std::filesystem::create_directories(path, createError);
	}

	static bool Move(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_oldPath,
		std::string_view a_newPath)
	{
		const auto oldPath = std::filesystem::path(a_oldPath);
		if (!::Internal::Sandbox::IsInSandbox(oldPath)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX_OLD_PATH, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto newPath = std::filesystem::path(a_newPath);
		if (!::Internal::Sandbox::IsInSandbox(newPath)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX_NEW_PATH, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto lock = std::unique_lock{ ::Internal::IOMutex::Get() };

		auto isDirError = std::error_code();
		if (!std::filesystem::is_directory(oldPath, isDirError)) {
			return false;
		}

		auto moveError = std::error_code();
		std::filesystem::rename(oldPath, newPath, moveError);
		return !moveError;
	}

	static bool Copy(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_oldPath,
		std::string_view a_newPath)
	{
		const auto oldPath = std::filesystem::path(a_oldPath);
		if (!::Internal::Sandbox::IsInSandbox(oldPath)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX_OLD_PATH, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto newPath = std::filesystem::path(a_newPath);
		if (!::Internal::Sandbox::IsInSandbox(newPath)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX_NEW_PATH, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto lock = std::unique_lock{ ::Internal::IOMutex::Get() };

		auto isDirError = std::error_code();
		if (!std::filesystem::is_directory(oldPath, isDirError)) {
			return false;
		}

		constexpr auto OPTIONS = std::filesystem::copy_options::recursive;

		auto copyError = std::error_code();
		std::filesystem::copy(oldPath, newPath, OPTIONS, copyError);
		return !copyError;
	}

	static bool Delete(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto lock = std::unique_lock{ ::Internal::IOMutex::Get() };

		auto isDirError = std::error_code();
		if (!std::filesystem::is_directory(path, isDirError)) {
			return false;
		}

		auto deleteError = std::error_code();
		return std::filesystem::remove_all(path, deleteError) > 0;
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetDirectories);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetFiles);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Exists);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Create);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Move);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Copy);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Delete);

		return true;
	}
}
