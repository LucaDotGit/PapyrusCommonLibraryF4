#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/PostSaveGameSource.hpp"

namespace Internal::Events
{
	class PostSaveGameHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<PostSaveGameEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "PostSaveGameArgs">;

	public:
		PostSaveGameHandler(const ScriptReceivers::ScriptReceiver& a_receiver);
		~PostSaveGameHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const PostSaveGameEvent& a_event, RE::BSTEventSource<PostSaveGameEvent>*) override;

		void Register() override;
		void Unregister() override;
	};
}
