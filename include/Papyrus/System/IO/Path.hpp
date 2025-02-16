#pragma once

namespace System::IO::Path
{
	static constexpr auto SCRIPT_NAME = "System:IO:Path"sv;

	static constinit auto INVALID_PATH_CHARS = []() noexcept {
		constexpr auto START_COUNT = 1i8;
		constexpr auto CONTROL_COUNT = 32i8;

		auto chars = std::array<char, START_COUNT + CONTROL_COUNT>{ '|' };
		for (auto i = 0i8; i < CONTROL_COUNT; i++) {
			chars[START_COUNT + i] = i;
		}

		return chars;
	}();

	static constinit auto INVALID_FILE_NAME_CHARS = []() noexcept {
		constexpr auto START_COUNT = 9i8;
		constexpr auto CONTROL_COUNT = 32i8;

		auto chars = std::array<char, START_COUNT + CONTROL_COUNT>{ '\\', '/', ':', '*', '?', '"', '<', '>', '|' };
		for (auto i = 0i8; i < CONTROL_COUNT; i++) {
			chars[START_COUNT + i] = i;
		}

		return chars;
	}();

	static std::string_view CurrentDirectory(std::monostate)
	{
		return "."sv;
	}

	static std::string_view ParentDirectory(std::monostate)
	{
		return ".."sv;
	}

	static std::string_view ExtensionSeparator(std::monostate)
	{
		return "."sv;
	}

	static std::string_view DirectorySeparator(std::monostate)
	{
		return "\\"sv;
	}

	static std::string_view AltDirectorySeparator(std::monostate)
	{
		return "/"sv;
	}

	static std::vector<std::string> GetInvalidPathChars(std::monostate)
	{
		auto chars = std::vector<std::string>();
		chars.reserve(INVALID_PATH_CHARS.size());

		for (const auto character : INVALID_PATH_CHARS) {
			chars.emplace_back(character, 1);
		}

		return chars;
	}

	static std::vector<std::string> GetInvalidFileNameChars(std::monostate)
	{
		auto chars = std::vector<std::string>();
		chars.reserve(INVALID_FILE_NAME_CHARS.size());

		for (const auto character : INVALID_FILE_NAME_CHARS) {
			chars.emplace_back(character, 1);
		}

		return chars;
	}

	static bool IsInSandbox(std::monostate,
		std::string_view a_path)
	{
		const auto path = std::filesystem::path(a_path);
		return ::Internal::Sandbox::IsInSandbox(path);
	}

	static bool Equals(std::monostate,
		std::string_view a_path1,
		std::string_view a_path2)
	{
		const auto path1 = std::filesystem::path(a_path1);
		const auto path2 = std::filesystem::path(a_path2);
		return path1 == path2;
	}

	static std::int32_t Compare(std::monostate,
		std::string_view a_path1,
		std::string_view a_path2)
	{
		const auto path1 = std::filesystem::path(a_path1);
		const auto path2 = std::filesystem::path(a_path2);
		return path1.compare(path2);
	}

	static std::string GetParent(std::monostate,
		std::string_view a_path)
	{
		const auto path = std::filesystem::path(a_path);
		return path.parent_path().string();
	}

	static std::string GetRelative(std::monostate,
		std::string_view a_path,
		std::string_view a_relative)
	{
		const auto path = std::filesystem::path(a_path);
		const auto relative = std::filesystem::path(a_relative);
		return relative.lexically_relative(path).lexically_normal().string();
	}

	static std::string GetDirectoryName(std::monostate,
		std::string_view a_path)
	{
		const auto path = std::filesystem::path(a_path);
		return path.parent_path().string();
	}

	static std::string GetFileName(std::monostate,
		std::string_view a_path)
	{
		const auto path = std::filesystem::path(a_path);
		return path.filename().string();
	}

	static std::string GetFileNameWithoutExtension(std::monostate,
		std::string_view a_path)
	{
		const auto path = std::filesystem::path(a_path);
		return path.stem().string();
	}

	static std::string GetExtension(std::monostate,
		std::string_view a_path)
	{
		const auto path = std::filesystem::path(a_path);
		return path.extension().string();
	}

	static std::string ChangeFileName(std::monostate,
		std::string_view a_path,
		std::string_view a_fileName)
	{
		auto path = std::filesystem::path(a_path);
		const auto fileName = std::filesystem::path(a_fileName);

		path.replace_filename(fileName);
		return path.string();
	}

	static std::string ChangeExtension(std::monostate,
		std::string_view a_path,
		std::string_view a_extension)
	{
		auto path = std::filesystem::path(a_path);
		const auto extension = std::filesystem::path(a_extension);

		path.replace_extension(extension);
		return path.string();
	}

	static std::string TrimEndingSeparator(std::monostate,
		std::string_view a_path)
	{
		const auto path = std::filesystem::path(a_path);
		return path.has_filename() ? path.string() : path.parent_path().string();
	}

	static std::string Normalize(std::monostate,
		std::string_view a_path)
	{
		const auto path = std::filesystem::path(a_path);
		return path.lexically_normal().string();
	}

	static std::vector<std::string> Split(std::monostate,
		std::string_view a_path)
	{
		const auto path = std::filesystem::path(a_path);

		auto result = std::vector<std::string>();
		for (const auto& part : path) {
			result.emplace_back(part.string());
		}

		return result;
	}

	static std::string Join(std::monostate,
		std::vector<std::string_view> a_paths)
	{
		auto result = std::filesystem::path();
		for (const auto& path : a_paths) {
			result /= path;
		}

		return result.string();
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, CurrentDirectory);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ParentDirectory);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ExtensionSeparator);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, DirectorySeparator);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, AltDirectorySeparator);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetInvalidPathChars);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetInvalidFileNameChars);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsInSandbox);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Equals);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Compare);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetParent);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetRelative);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetDirectoryName);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetFileName);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetFileNameWithoutExtension);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetExtension);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ChangeFileName);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ChangeExtension);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, TrimEndingSeparator);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Normalize);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Split);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Join);

		return true;
	}
}
