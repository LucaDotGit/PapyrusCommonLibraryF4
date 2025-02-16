#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/CellLoadSource.hpp"

namespace Internal::Events
{
	class CellLoadHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<CellLoadEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "CellLoadArgs">;

	public:
		CellLoadHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
			const std::vector<const RE::BSScript::Variable*>& a_excludedObjects);

		~CellLoadHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const CellLoadEvent& a_event, RE::BSTEventSource<CellLoadEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _filter;
	};
}
