#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/LocationEnterExitSource.hpp"

namespace Internal::Events
{
	class LocationEnterExitHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<LocationEnterExitEvent>
	{
	public:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "LocationEnterExitArgs">;

	public:
		LocationEnterExitHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedSources,
			const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
			const std::vector<const RE::BSScript::Variable*>& a_includedOldLocations,
			const std::vector<const RE::BSScript::Variable*>& a_excludedOldLocations,
			const std::vector<const RE::BSScript::Variable*>& a_includedNewLocations,
			const std::vector<const RE::BSScript::Variable*>& a_excludedNewLocations);

		~LocationEnterExitHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const LocationEnterExitEvent& a_event, RE::BSTEventSource<LocationEnterExitEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _sourceFilter;
		const VarFilter _oldLocationFilter;
		const VarFilter _newLocationFilter;
	};
}
