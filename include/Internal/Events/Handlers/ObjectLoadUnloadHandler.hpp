#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class ObjectLoadUnloadHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::TESObjectLoadedEvent>
	{
	public:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "ObjectLoadUnloadArgs">;

	public:
		ObjectLoadUnloadHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
			const std::vector<const RE::BSScript::Variable*>& a_excludedObjects);

		~ObjectLoadUnloadHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::TESObjectLoadedEvent& a_event, RE::BSTEventSource<RE::TESObjectLoadedEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _filter;
	};
}
