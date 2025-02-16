#pragma once

namespace Internal::ScriptReceivers
{
	using ScriptReceiver = RE::BSScript::structure_wrapper<"System:ScriptReceivers", "ScriptReceiver">;

	[[nodiscard]] ScriptReceiver MakeLocalReceiver(
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_object, const RE::BSFixedString& a_functionName) noexcept;
	[[nodiscard]] ScriptReceiver MakeGlobalReceiver(
		const RE::BSFixedString& a_scriptName, const RE::BSFixedString& a_functionName) noexcept;

	[[nodiscard]] std::tuple<RE::BSTSmartPointer<RE::BSScript::Object>, RE::BSFixedString> GetLocalReceiver(
		const ScriptReceiver& a_receiver) noexcept;
	bool SetLocalReceiver(
		ScriptReceiver& a_receiver, const RE::BSTSmartPointer<RE::BSScript::Object>& a_object, const RE::BSFixedString& a_functionName) noexcept;

	[[nodiscard]] std::tuple<RE::BSFixedString, RE::BSFixedString> GetGlobalReceiver(
		const ScriptReceiver& a_receiver) noexcept;
	bool SetGlobalReceiver(
		ScriptReceiver& a_receiver, const RE::BSFixedString& a_scriptName, const RE::BSFixedString& a_functionName) noexcept;

	[[nodiscard]] std::tuple<RE::BSFixedString, RE::BSFixedString> GetNames(
		const ScriptReceiver& a_receiver) noexcept;
	bool SetNames(
		ScriptReceiver& a_receiver, const RE::BSFixedString& a_scriptName, const RE::BSFixedString& a_functionName) noexcept;

	[[nodiscard]] RE::BSTSmartPointer<RE::BSScript::Object> GetObject(
		const ScriptReceiver& a_receiver) noexcept;
	bool SetObject(
		ScriptReceiver& a_receiver, const RE::BSTSmartPointer<RE::BSScript::Object>& a_object) noexcept;

	[[nodiscard]] RE::BSFixedString GetScriptName(
		const ScriptReceiver& a_receiver) noexcept;
	bool SetScriptName(
		ScriptReceiver& a_receiver, const RE::BSFixedString& a_scriptName) noexcept;

	[[nodiscard]] RE::BSFixedString GetFunctionName(
		const ScriptReceiver& a_receiver) noexcept;
	bool SetFunctionName(
		ScriptReceiver& a_receiver, const RE::BSFixedString& a_functionName) noexcept;
}
