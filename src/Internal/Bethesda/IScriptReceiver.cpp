#include "Internal/Bethesda/IScriptReceiver.hpp"

namespace Internal
{
	IScriptReceiver::IScriptReceiver(const ScriptReceivers::ScriptReceiver& a_receiver) noexcept :
		_object(ScriptReceivers::GetObject(a_receiver)),
		_scriptName(ScriptReceivers::GetScriptName(a_receiver)),
		_functionName(ScriptReceivers::GetFunctionName(a_receiver))
	{
	}

	bool IScriptReceiver::IsGlobal() const noexcept
	{
		return !_object;
	}

	bool IScriptReceiver::IsDispatchable() const
	{
		const auto vm = RE::GameVM::GetSingleton()->GetVM();
		return !vm->IsCompletelyFrozen();
	}

	const RE::BSTSmartPointer<RE::BSScript::Object>& IScriptReceiver::GetObject() const noexcept
	{
		return _object;
	}

	const RE::BSFixedString& IScriptReceiver::GetScriptName() const noexcept
	{
		return _scriptName;
	}

	const RE::BSFixedString& IScriptReceiver::GetFunctionName() const noexcept
	{
		return _functionName;
	}
}
