#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/DestructionStageChangeSource.hpp"

namespace Internal::Events
{
	class DestructionStageChangeHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<DestructionStageChangeEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "DestructionStageChangeArgs">;

	public:
		DestructionStageChangeHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
			const std::vector<const RE::BSScript::Variable*>& a_excludedObjects,
			const std::vector<std::uint32_t>& a_includedOldStages,
			const std::vector<std::uint32_t>& a_excludedOldStages,
			const std::vector<std::uint32_t>& a_includedNewStages,
			const std::vector<std::uint32_t>& a_excludedNewStages);

		~DestructionStageChangeHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const DestructionStageChangeEvent& a_event, RE::BSTEventSource<DestructionStageChangeEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _filter;
		const std::unordered_set<std::uint32_t> _includedOldStages;
		const std::unordered_set<std::uint32_t> _excludedOldStages;
		const std::unordered_set<std::uint32_t> _includedNewStages;
		const std::unordered_set<std::uint32_t> _excludedNewStages;
	};
}
