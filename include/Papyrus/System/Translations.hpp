#pragma once

#include "Internal/Bethesda/Translator.hpp"

namespace System::Translations
{
	static constexpr auto SCRIPT_NAME = "System:Translations"sv;

	static std::string_view GetLanguageCode(std::monostate)
	{
		return ::Internal::Translator::GetLanguageCode();
	}

	static bool Contains(std::monostate,
		std::string_view a_key)
	{
		return ::Internal::Translator::Contains(a_key);
	}

	static std::string GetValue(std::monostate,
		std::string_view a_key,
		std::string a_default)
	{
		return ::Internal::Translator::GetString(a_key).value_or(a_default);
	}

	static bool SetValue(std::monostate,
		std::string_view a_key,
		std::string_view a_value)
	{
		return ::Internal::Translator::SetString(a_key, a_value);
	}

	static bool Add(std::monostate,
		std::string_view a_key,
		std::string_view a_value)
	{
		return ::Internal::Translator::Add(a_key, a_value);
	}

	static bool Remove(std::monostate,
		std::string_view a_key)
	{
		return ::Internal::Translator::Remove(a_key);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetLanguageCode);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Contains);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetValue);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetValue);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Add);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Remove);

		return true;
	}
}
