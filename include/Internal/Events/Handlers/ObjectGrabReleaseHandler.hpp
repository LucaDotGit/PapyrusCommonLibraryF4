#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/ObjectGrabReleaseSource.hpp"

namespace Internal::Events
{
	class ObjectGrabReleaseHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<ObjectGrabReleaseEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "ObjectGrabReleaseArgs">;

	public:
		ObjectGrabReleaseHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
			const std::vector<const RE::BSScript::Variable*>& a_excludedObjects);

		~ObjectGrabReleaseHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const ObjectGrabReleaseEvent& a_event, RE::BSTEventSource<ObjectGrabReleaseEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _filter;
	};
}
