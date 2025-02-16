#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class ItemEquipUnequipHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::TESEquipEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "ItemEquipUnequipArgs">;

	public:
		ItemEquipUnequipHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedSources,
			const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
			const std::vector<const RE::BSScript::Variable*>& a_includedTargets,
			const std::vector<const RE::BSScript::Variable*>& a_excludedTargets);

		~ItemEquipUnequipHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::TESEquipEvent& a_event, RE::BSTEventSource<RE::TESEquipEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _sourceFilter;
		const VarFilter _targetFilter;
	};
}
