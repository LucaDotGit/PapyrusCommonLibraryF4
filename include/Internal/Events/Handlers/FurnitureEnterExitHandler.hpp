#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class FurnitureEnterExitHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::TESFurnitureEvent>
	{
	public:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "FurnitureEnterExitArgs">;

	public:
		FurnitureEnterExitHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedSources,
			const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
			const std::vector<const RE::BSScript::Variable*>& a_includedTargets,
			const std::vector<const RE::BSScript::Variable*>& a_excludedTargets);

		~FurnitureEnterExitHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::TESFurnitureEvent& a_event, RE::BSTEventSource<RE::TESFurnitureEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _sourceFilter;
		const VarFilter _targetFilter;
	};
}
