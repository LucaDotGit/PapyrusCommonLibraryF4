#pragma once

#include "Internal/Bethesda/ScriptUtils.hpp"

namespace Internal
{
	class IScriptReceiver
	{
	public:
		explicit IScriptReceiver(const ScriptReceivers::ScriptReceiver& a_receiver) noexcept;
		virtual ~IScriptReceiver() noexcept = default;

	public:
		[[nodiscard]] bool IsGlobal() const noexcept;
		[[nodiscard]] bool IsDispatchable() const;

		[[nodiscard]] const RE::BSTSmartPointer<RE::BSScript::Object>& GetObject() const noexcept;
		[[nodiscard]] const RE::BSFixedString& GetScriptName() const noexcept;
		[[nodiscard]] const RE::BSFixedString& GetFunctionName() const noexcept;

	public:
		template <typename... Args>
		bool DispatchCall(Args&&... a_args) const
		{
			return IsGlobal() ? ScriptUtils::DispatchStaticCall(GetScriptName(), GetFunctionName(), std::forward<Args>(a_args)...)
							  : ScriptUtils::DispatchMethodCall(GetObject(), GetFunctionName(), std::forward<Args>(a_args)...);
		}

		template <RE::BSScript::detail::array T>
			requires std::is_same_v<typename T::value_type, RE::BSScript::Variable>
		bool DispatchAppliedCall(const T& a_args) const
		{
			return IsGlobal() ? ScriptUtils::DispatchAppliedStaticCall(GetScriptName(), GetFunctionName(), a_args)
							  : ScriptUtils::DispatchAppliedMethodCall(GetObject(), GetFunctionName(), a_args);
		}

	private:
		const RE::BSTSmartPointer<RE::BSScript::Object> _object;
		const RE::BSFixedString _scriptName;
		const RE::BSFixedString _functionName;
	};
}
