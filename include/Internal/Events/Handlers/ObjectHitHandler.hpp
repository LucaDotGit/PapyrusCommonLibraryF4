#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class ObjectHitHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::TESHitEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "ObjectHitArgs">;
		using ObjectHitData = RE::BSScript::structure_wrapper<"System:Events", "ObjectHitData">;

	public:
		ObjectHitHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedSources,
			const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
			const std::vector<const RE::BSScript::Variable*>& a_includedTargets,
			const std::vector<const RE::BSScript::Variable*>& a_excludedTargets,
			const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
			const std::vector<const RE::BSScript::Variable*>& a_excludedObjects,
			const std::vector<const RE::BSScript::Variable*>& a_includedProjectiles,
			const std::vector<const RE::BSScript::Variable*>& a_excludedProjectiles,
			const std::vector<RE::BSFixedString>& a_includedMaterialNames,
			const std::vector<RE::BSFixedString>& a_excludedMaterialNames,
			RE::HitData::Flags a_includedFlags,
			RE::HitData::Flags a_excludedFlags);

		~ObjectHitHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::TESHitEvent& a_event, RE::BSTEventSource<RE::TESHitEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _sourceFilter;
		const VarFilter _targetFilter;
		const VarFilter _objectFilter;
		const VarFilter _projectileFilter;
		const Types::unordered_string_set<RE::BSFixedString> _includedMaterialNames;
		const Types::unordered_string_set<RE::BSFixedString> _excludedMaterialNames;
		const RE::HitData::Flags _includedFlags;
		const RE::HitData::Flags _excludedFlags;
	};
}
