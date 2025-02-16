#pragma once

namespace System::IO::File
{
	static constexpr auto SCRIPT_NAME = "System:IO:File"sv;

	static std::string ReadAllText(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto lock = std::shared_lock{ ::Internal::IOMutex::Get() };

		auto file = std::ifstream(path);
		if (!file) {
			return {};
		}

		return { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
	}

	static std::vector<std::string> ReadAllLines(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto lock = std::shared_lock{ ::Internal::IOMutex::Get() };

		auto file = std::ifstream(path);
		if (!file) {
			return {};
		}

		auto lines = std::vector<std::string>();
		for (auto line = std::string(); std::getline(file, line);) {
			lines.emplace_back(std::move(line));
		}

		return lines;
	}

	static bool WriteAllText(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_text)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto lock = std::unique_lock{ ::Internal::IOMutex::Get() };

		auto file = std::ofstream(path);
		file << a_text;

		return file.good();
	}

	static bool WriteAllLines(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::vector<std::string_view> a_lines)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto lock = std::unique_lock{ ::Internal::IOMutex::Get() };

		auto file = std::ofstream(path);
		for (const auto& line : a_lines) {
			file << line << std::endl;
		}

		return file.good();
	}

	static bool AppendAllText(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_text)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto lock = std::unique_lock{ ::Internal::IOMutex::Get() };

		auto file = std::ofstream(path, std::ios::app);
		file << a_text;

		return file.good();
	}

	static bool AppendAllLines(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::vector<std::string_view> a_lines)
	{
		const auto path = std::filesystem::path(a_path);
		if (!::Internal::Sandbox::IsInSandbox(path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto lock = std::unique_lock{ ::Internal::IOMutex::Get() };

		auto file = std::ofstream(path, std::ios::app);
		for (const auto& line : a_lines) {
			file << line << std::endl;
		}

		return file.good();
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

		auto isFileError = std::error_code();
		return std::filesystem::is_regular_file(path, isFileError);
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

		auto file = std::ofstream(path);
		return file.good();
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

		auto isFileError = std::error_code();
		if (!std::filesystem::is_regular_file(oldPath, isFileError)) {
			return false;
		}

		auto renameError = std::error_code();
		std::filesystem::rename(oldPath, newPath, renameError);
		return !renameError;
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

		auto isFileError = std::error_code();
		if (!std::filesystem::is_regular_file(oldPath, isFileError)) {
			return false;
		}

		constexpr auto OPTIONS = std::filesystem::copy_options::none;

		auto copyError = std::error_code();
		return std::filesystem::copy_file(oldPath, newPath, OPTIONS, copyError);
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

		auto isFileError = std::error_code();
		if (!std::filesystem::is_regular_file(path, isFileError)) {
			return false;
		}

		auto deleteError = std::error_code();
		return std::filesystem::remove(path, deleteError);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ReadAllText);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ReadAllLines);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, WriteAllText);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, WriteAllLines);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, AppendAllText);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, AppendAllLines);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Exists);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Create);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Move);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Copy);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Delete);

		return true;
	}
}
