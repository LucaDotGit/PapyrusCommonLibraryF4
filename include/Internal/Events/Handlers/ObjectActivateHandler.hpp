#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class ObjectActivateHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::TESActivateEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "ObjectActivateArgs">;

	public:
		ObjectActivateHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedSources,
			const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
			const std::vector<const RE::BSScript::Variable*>& a_includedTargets,
			const std::vector<const RE::BSScript::Variable*>& a_excludedTargets);

		~ObjectActivateHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::TESActivateEvent& a_event, RE::BSTEventSource<RE::TESActivateEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _sourceFilter;
		const VarFilter _targetFilter;
	};
}
