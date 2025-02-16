#pragma once

namespace Internal::ScriptUtils
{
	static const auto CALLBACK = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>();

	template <typename... Args>
	bool DispatchMethodCall(
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_object,
		const RE::BSFixedString& a_functionName,
		Args&&... a_args)
	{
		const auto vm = RE::GameVM::GetSingleton()->GetVM();
		return vm->DispatchMethodCall(
			a_object,
			a_functionName,
			CALLBACK,
			std::forward<Args>(a_args)...);
	}

	template <typename... Args>
	bool DispatchStaticCall(
		const RE::BSFixedString& a_scriptName,
		const RE::BSFixedString& a_functionName,
		Args&&... a_args)
	{
		const auto vm = RE::GameVM::GetSingleton()->GetVM();
		return vm->DispatchStaticCall(
			a_scriptName,
			a_functionName,
			CALLBACK,
			std::forward<Args>(a_args)...);
	}

	template <RE::BSScript::detail::array T>
		requires std::is_same_v<typename std::remove_cv_t<T>::value_type, RE::BSScript::Variable>
	bool DispatchAppliedMethodCall(
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_object,
		const RE::BSFixedString& a_functionName,
		const T& a_args)
	{
		const auto vm = RE::GameVM::GetSingleton()->GetVM();
		return vm->DispatchAppliedMethodCall(
			a_object,
			a_functionName,
			CALLBACK,
			a_args);
	}

	template <RE::BSScript::detail::array T>
		requires std::is_same_v<typename std::remove_cv_t<T>::value_type, RE::BSScript::Variable>
	bool DispatchAppliedStaticCall(
		const RE::BSFixedString& a_scriptName,
		const RE::BSFixedString& a_functionName,
		const T& a_args)
	{
		const auto vm = RE::GameVM::GetSingleton()->GetVM();
		return vm->DispatchAppliedStaticCall(
			a_scriptName,
			a_functionName,
			CALLBACK,
			a_args);
	}
}
