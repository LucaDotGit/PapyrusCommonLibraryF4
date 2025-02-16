#pragma once

#include "Internal/Bethesda/IScriptReceiver.hpp"

namespace Internal
{
	class MessageBoxCallback final
		: public IScriptReceiver,
		  public RE::IMessageBoxCallback
	{
	public:
		MessageBoxCallback(const ScriptReceivers::ScriptReceiver& a_receiver) noexcept;

	public:
		void operator()(std::uint8_t a_buttonIdx) override;
	};
}
