#pragma once

#include "Internal/Bethesda/IScriptReceiver.hpp"

namespace Internal::Events
{
	class IEventHandler
		: public IScriptReceiver
	{
	public:
		explicit IEventHandler(const ScriptReceivers::ScriptReceiver& a_receiver) :
			IScriptReceiver(a_receiver)
		{
		}

	protected:
		virtual void Register() = 0;
		virtual void Unregister() = 0;
	};
}
