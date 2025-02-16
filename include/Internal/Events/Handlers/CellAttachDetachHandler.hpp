#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	class CellAttachDetachHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<RE::CellAttachDetachEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "CellAttachDetachArgs">;

	public:
		CellAttachDetachHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
			const std::vector<const RE::BSScript::Variable*>& a_excludedObjects);

		~CellAttachDetachHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::CellAttachDetachEvent& a_event, RE::BSTEventSource<RE::CellAttachDetachEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _filter;
	};
}
