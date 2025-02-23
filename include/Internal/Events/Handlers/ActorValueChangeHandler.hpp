#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/ActorValueChangeSource.hpp"

namespace Internal::Events
{
	class ActorValueChangeHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<ActorValueChangeEvent>
	{
	public:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "ActorValueChangeArgs">;

	public:
		ActorValueChangeHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
			const std::vector<const RE::BSScript::Variable*>& a_excludedObjects,
			const std::vector<const RE::BSScript::Variable*>& a_includedActorValues,
			const std::vector<const RE::BSScript::Variable*>& a_excludedActorValues);

		~ActorValueChangeHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const ActorValueChangeEvent& a_event, RE::BSTEventSource<ActorValueChangeEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _objectFilter;
		const VarFilter _actorValueFilter;
	};
}
