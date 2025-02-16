#include "Internal/Bethesda/MessageBoxCallback.hpp"

namespace Internal
{
	MessageBoxCallback::MessageBoxCallback(const ScriptReceivers::ScriptReceiver& a_receiver) noexcept :
		IScriptReceiver(a_receiver)
	{
	}

	void MessageBoxCallback::operator()(std::uint8_t a_buttonIdx)
	{
		DispatchCall(a_buttonIdx);
	}
}
