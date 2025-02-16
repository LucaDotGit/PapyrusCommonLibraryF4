#include "Internal/Structs/ScriptReceivers.hpp"

namespace Internal::ScriptReceivers
{
	static constexpr auto OBJECT_KEY = "Object"sv;
	static constexpr auto SCRIPT_NAME_KEY = "ObjectName"sv;
	static constexpr auto FUNCTION_NAME_KEY = "FunctionName"sv;

	ScriptReceiver MakeLocalReceiver(
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_object, const RE::BSFixedString& a_functionName) noexcept
	{
		auto receiver = ScriptReceiver();
		SetLocalReceiver(receiver, a_object, a_functionName);
		return receiver;
	}

	ScriptReceiver MakeGlobalReceiver(
		const RE::BSFixedString& a_scriptName, const RE::BSFixedString& a_functionName) noexcept
	{
		auto receiver = ScriptReceiver();
		SetGlobalReceiver(receiver, a_scriptName, a_functionName);
		return receiver;
	}

	std::tuple<RE::BSTSmartPointer<RE::BSScript::Object>, RE::BSFixedString> GetLocalReceiver(
		const ScriptReceiver& a_receiver) noexcept
	{
		return std::make_tuple(
			GetObject(a_receiver),
			GetFunctionName(a_receiver));
	}

	bool SetLocalReceiver(
		ScriptReceiver& a_receiver, const RE::BSTSmartPointer<RE::BSScript::Object>& a_object, const RE::BSFixedString& a_functionName) noexcept
	{
		return SetObject(a_receiver, a_object) &&
			   SetFunctionName(a_receiver, a_functionName);
	}

	std::tuple<RE::BSFixedString, RE::BSFixedString> GetGlobalReceiver(
		const ScriptReceiver& a_receiver) noexcept
	{
		return std::make_tuple(
			GetScriptName(a_receiver),
			GetFunctionName(a_receiver));
	}

	bool SetGlobalReceiver(
		ScriptReceiver& a_receiver, const RE::BSFixedString& a_scriptName, const RE::BSFixedString& a_functionName) noexcept
	{
		return SetScriptName(a_receiver, a_scriptName) &&
			   SetFunctionName(a_receiver, a_functionName);
	}

	std::tuple<RE::BSFixedString, RE::BSFixedString> GetNames(
		const ScriptReceiver& a_receiver) noexcept
	{
		return std::make_tuple(
			GetScriptName(a_receiver),
			GetFunctionName(a_receiver));
	}

	bool SetNames(
		ScriptReceiver& a_receiver, const RE::BSFixedString& a_scriptName, const RE::BSFixedString& a_functionName) noexcept
	{
		return SetScriptName(a_receiver, a_scriptName) &&
			   SetFunctionName(a_receiver, a_functionName);
	}

	RE::BSTSmartPointer<RE::BSScript::Object> GetObject(
		const ScriptReceiver& a_receiver) noexcept
	{
		return a_receiver.find<RE::BSTSmartPointer<RE::BSScript::Object>>(OBJECT_KEY).value_or(nullptr);
	}

	bool SetObject(
		ScriptReceiver& a_receiver, const RE::BSTSmartPointer<RE::BSScript::Object>& a_object) noexcept
	{
		return a_receiver.insert(OBJECT_KEY, a_object);
	}

	RE::BSFixedString GetScriptName(
		const ScriptReceiver& a_receiver) noexcept
	{
		return a_receiver.find<RE::BSFixedString>(SCRIPT_NAME_KEY).value_or(RE::BSFixedString());
	}

	bool SetScriptName(
		ScriptReceiver& a_receiver, const RE::BSFixedString& a_scriptName) noexcept
	{
		return a_receiver.insert(SCRIPT_NAME_KEY, a_scriptName);
	}

	RE::BSFixedString GetFunctionName(
		const ScriptReceiver& a_receiver) noexcept
	{
		return a_receiver.find<RE::BSFixedString>(FUNCTION_NAME_KEY).value_or(RE::BSFixedString());
	}

	bool SetFunctionName(
		ScriptReceiver& a_receiver, const RE::BSFixedString& a_functionName) noexcept
	{
		return a_receiver.insert(FUNCTION_NAME_KEY, a_functionName);
	}
}
