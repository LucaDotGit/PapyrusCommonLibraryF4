#pragma once

#include "Internal/Events/IEventHandler.hpp"

#include "Internal/Events/Sources/AnimationGraphEventSource.hpp"

namespace Internal::Events
{
	class AnimationGraphEventHandler final
		: public IEventHandler,
		  public RE::BSTEventSink<AnimationGraphEvent>
	{
	private:
		using EventArgs = RE::BSScript::structure_wrapper<"System:Events", "AnimationGraphEventArgs">;

	public:
		AnimationGraphEventHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
			const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
			const std::vector<const RE::BSScript::Variable*>& a_excludedObjects,
			const std::vector<RE::BSFixedString>& a_includedEventNames,
			const std::vector<RE::BSFixedString>& a_excludedEventNames,
			const std::vector<RE::BSFixedString>& a_includedPayloads,
			const std::vector<RE::BSFixedString>& a_excludedPayloads);

		~AnimationGraphEventHandler() override;

	private:
		RE::BSEventNotifyControl ProcessEvent(const AnimationGraphEvent& a_event, RE::BSTEventSource<AnimationGraphEvent>*) override;

		void Register() override;
		void Unregister() override;

	private:
		const VarFilter _objectFilter;
		const Types::unordered_string_set<RE::BSFixedString> _includedEventNames;
		const Types::unordered_string_set<RE::BSFixedString> _excludedEventNames;
		const Types::unordered_string_set<RE::BSFixedString> _includedPayloads;
		const Types::unordered_string_set<RE::BSFixedString> _excludedPayloads;
	};
}
