#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/ObjectOpenCloseSource.hpp"

namespace Internal::Events
{
	class ObjectOpenCloseHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<ObjectOpenCloseEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "ObjectOpenCloseArgs">;

	public:
		ObjectOpenCloseHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedSources,
			const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
			const std::vector<const RE::BSScript::Variable*>& a_includedTargets,
			const std::vector<const RE::BSScript::Variable*>& a_excludedTargets);

		~ObjectOpenCloseHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const ObjectOpenCloseEvent& a_event, RE::BSTEventSource<ObjectOpenCloseEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _sourceFilter;
		const VarFilter _targetFilter;
	};
}
