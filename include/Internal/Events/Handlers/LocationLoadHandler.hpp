#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/LocationLoadSource.hpp"

namespace Internal::Events
{
	class LocationLoadHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<LocationLoadEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "LocationLoadArgs">;

	public:
		LocationLoadHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
			const std::vector<const RE::BSScript::Variable*>& a_excludedObjects);

		~LocationLoadHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const LocationLoadEvent& a_event, RE::BSTEventSource<LocationLoadEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _filter;
	};
}
