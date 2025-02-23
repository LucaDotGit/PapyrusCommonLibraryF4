#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class LockPickHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::LocksPicked::Event>
	{
	public:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "LockPickArgs">;

	public:
		LockPickHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
			const std::vector<const RE::BSScript::Variable*>& a_excludedObjects);

		~LockPickHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::LocksPicked::Event&, RE::BSTEventSource<RE::LocksPicked::Event>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _filter;
	};
}
