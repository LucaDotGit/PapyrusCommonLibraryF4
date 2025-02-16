#include "Internal/Events/Registration.hpp"

namespace Internal::Events::Registration
{
	bool IsRegisteredForAny(const ScriptReceivers::ScriptReceiver& a_receiver)
	{
		if (!a_receiver) {
			return false;
		}

		const auto lock = std::shared_lock{ Mutex };
		return Handlers.contains(ScriptReceivers::GetScriptName(a_receiver));
	}

	bool UnregisterForAny(const ScriptReceivers::ScriptReceiver& a_receiver)
	{
		if (!a_receiver) {
			return false;
		}

		const auto lock = std::unique_lock{ Mutex };

		const auto scriptIt = Handlers.find(ScriptReceivers::GetScriptName(a_receiver));
		if (scriptIt == Handlers.end()) {
			return false;
		}

		const auto funcIt = scriptIt->second.find(ScriptReceivers::GetFunctionName(a_receiver));
		if (funcIt == scriptIt->second.end()) {
			return false;
		}

		scriptIt->second.erase(funcIt);
		if (scriptIt->second.empty()) {
			Handlers.erase(scriptIt);
		}

		return true;
	}

	bool UnregisterForAll(const RE::BSFixedString& a_scriptName)
	{
		const auto lock = std::unique_lock{ Mutex };

		const auto scriptIt = Handlers.find(a_scriptName);
		if (scriptIt == Handlers.end()) {
			return false;
		}

		Handlers.erase(scriptIt);
		return true;
	}
}
