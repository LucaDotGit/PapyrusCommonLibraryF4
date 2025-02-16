#pragma once

namespace System::Internal
{
	static constexpr auto SCRIPT_NAME = "System:Internal"sv;

	static std::string_view GetName(std::monostate)
	{
		return Plugin::NAME;
	}

	static ::Internal::Versions::Version GetVersion(std::monostate)
	{
		return ::Internal::Versions::MakeVersion(Plugin::VERSION);
	}

	static std::string GetVersionString(std::monostate)
	{
		return Plugin::VERSION.string();
	}

	static void LogWarning(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_message)
	{
		a_vm.PostError(a_message, a_stackID, RE::BSScript::ErrorLogger::Severity::kWarning);
	}

	static void LogError(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_message)
	{
		a_vm.PostError(a_message, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetName);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetVersion);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetVersionString);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, LogWarning);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, LogError);

		return true;
	}
}
