#include "Internal/Runners/CommandRunner.hpp"

namespace Internal::CommandRunner
{
	static const auto PATH = std::filesystem::path(L"Data\\PCL\\Commands"s);
	static const auto EXTENSION = std::filesystem::path(L".txt"s);

	static auto Commands = std::map<std::string, std::string>();

	static void Execute(std::string_view a_command)
	{
		auto* log = RE::ConsoleLog::GetSingleton();
		auto compiler = RE::ScriptCompiler();

		auto* scriptFactory = RE::ConcreteFormFactory<RE::Script>::GetFormFactory();
		auto* script = scriptFactory->Create();

		auto buffer = log->buffer;

		script->SetText(a_command);
		script->CompileAndRun(&compiler, RE::COMPILER_NAME::kSystemWindow, nullptr);

		if (!script->header.isCompiled) {
			logger::warn("Command Runner: Failed to compile command \"{}\""sv, a_command);
		}

		log->buffer = std::move(buffer);
		delete script;
	}

	static void Dispose()
	{
		logger::debug("Command Runner: Dispose"sv);

		Commands.clear();
	}

	void Setup()
	{
		logger::debug("Command Runner: Setup"sv);

		constexpr auto DIR_OPTIONS = std::filesystem::directory_options::skip_permission_denied;

		auto entryError = std::error_code();
		for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(PATH, DIR_OPTIONS, entryError)) {
			const auto& filePath = dirEntry.path();
			if (filePath.extension() != EXTENSION) {
				continue;
			}

			auto isFileError = std::error_code();
			if (!dirEntry.is_regular_file(isFileError)) {
				continue;
			}

			auto file = std::ifstream(filePath);
			if (!file) {
				logger::warn("Command Runner: Failed to load file \"{}\""sv, filePath.string());
				continue;
			}

			const auto fileName = filePath.stem().string();
			Commands[fileName] = { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };

			logger::debug("Command Runner: Loaded file \"{}\""sv, filePath.string());
		}
	}

	void Run()
	{
		logger::debug("Command Runner: Run"sv);

		for (const auto& [file, commands] : Commands) {
			logger::debug("Command Runner: Executing file \"{}\""sv, file);
			Execute(commands);
		}

		Dispose();
	}
}
