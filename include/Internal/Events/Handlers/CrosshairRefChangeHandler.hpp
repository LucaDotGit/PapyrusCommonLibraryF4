#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class CrosshairRefChangeHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::ViewCasterUpdateEvent>
	{
	public:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "CrosshairRefChangeArgs">;

	public:
		CrosshairRefChangeHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
			const std::vector<const RE::BSScript::Variable*>& a_excludedObjects);

		~CrosshairRefChangeHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::ViewCasterUpdateEvent&, RE::BSTEventSource<RE::ViewCasterUpdateEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _filter;
	};
}
