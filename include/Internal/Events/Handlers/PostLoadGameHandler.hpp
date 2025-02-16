#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/PostLoadGameSource.hpp"

namespace Internal::Events
{
	class PostLoadGameHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<PostLoadGameEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "PostLoadGameArgs">;

	public:
		PostLoadGameHandler(const ScriptReceivers::ScriptReceiver& a_receiver);
		~PostLoadGameHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const PostLoadGameEvent& a_event, RE::BSTEventSource<PostLoadGameEvent>*) override;

		void Register() override;
		void Unregister() override;
	};
}
