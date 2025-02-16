#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/TriggerEnterLeaveSource.hpp"

namespace Internal::Events
{
	class TriggerEnterLeaveHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<TriggerEnterLeaveEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "TriggerEnterLeaveArgs">;

	public:
		TriggerEnterLeaveHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedSources,
			const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
			const std::vector<const RE::BSScript::Variable*>& a_includedTargets,
			const std::vector<const RE::BSScript::Variable*>& a_excludedTargets);

		~TriggerEnterLeaveHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const TriggerEnterLeaveEvent& a_event, RE::BSTEventSource<TriggerEnterLeaveEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _sourceFilter;
		const VarFilter _targetFilter;
	};
}
