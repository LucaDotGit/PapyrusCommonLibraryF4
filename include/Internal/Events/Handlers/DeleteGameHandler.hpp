#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/DeleteGameSource.hpp"

namespace Internal::Events
{
	class DeleteGameHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<DeleteGameEvent>
	{
	public:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "DeleteGameArgs">;

	public:
		DeleteGameHandler(const ScriptReceivers::ScriptReceiver& a_receiver);
		~DeleteGameHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const DeleteGameEvent& a_event, RE::BSTEventSource<DeleteGameEvent>*) override;

		void Register() override;
		void Unregister() override;
	};
}
