#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/PreSaveGameSource.hpp"

namespace Internal::Events
{
	class PreSaveGameHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<PreSaveGameEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "PreSaveGameArgs">;

	public:
		PreSaveGameHandler(const ScriptReceivers::ScriptReceiver& a_receiver);
		~PreSaveGameHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const PreSaveGameEvent& a_event, RE::BSTEventSource<PreSaveGameEvent>*) override;

		void Register() override;
		void Unregister() override;
	};
}
