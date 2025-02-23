#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/LimbCrippleSource.hpp"

namespace Internal::Events
{
	class LimbCrippleHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<LimbCrippleEvent>
	{
	public:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "LimbCrippleArgs">;

	public:
		LimbCrippleHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedSources,
			const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
			const std::vector<const RE::BSScript::Variable*>& a_includedLimbs,
			const std::vector<const RE::BSScript::Variable*>& a_excludedLimbs);

		~LimbCrippleHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const LimbCrippleEvent& a_event, RE::BSTEventSource<LimbCrippleEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _sourceFilter;
		const VarFilter _limbFilter;
	};
}
