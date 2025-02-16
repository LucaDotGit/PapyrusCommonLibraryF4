#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class ContainerChangeHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::TESContainerChangedEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "ContainerChangeArgs">;

	public:
		ContainerChangeHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedSources,
			const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
			const std::vector<const RE::BSScript::Variable*>& a_includedTargets,
			const std::vector<const RE::BSScript::Variable*>& a_excludedTargets,
			const std::vector<const RE::BSScript::Variable*>& a_includedItems,
			const std::vector<const RE::BSScript::Variable*>& a_excludedItems);

		~ContainerChangeHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::TESContainerChangedEvent& a_event, RE::BSTEventSource<RE::TESContainerChangedEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _sourceFilter;
		const VarFilter _targetFilter;
		const VarFilter _itemFilter;
	};
}
