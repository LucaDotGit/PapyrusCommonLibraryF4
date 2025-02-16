#include "Internal/Events/Handlers/AnimationGraphEventHandler.hpp"

namespace Internal::Events
{
	AnimationGraphEventHandler::AnimationGraphEventHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
		const std::vector<const RE::BSScript::Variable*>& a_excludedObjects,
		const std::vector<RE::BSFixedString>& a_includedEventNames,
		const std::vector<RE::BSFixedString>& a_excludedEventNames,
		const std::vector<RE::BSFixedString>& a_includedPayloads,
		const std::vector<RE::BSFixedString>& a_excludedPayloads) :
		IEventHandler(a_receiver),
		_objectFilter{ a_includedObjects, a_excludedObjects },
		_includedEventNames{ a_includedEventNames.begin(), a_includedEventNames.end() },
		_excludedEventNames{ a_excludedEventNames.begin(), a_excludedEventNames.end() },
		_includedPayloads{ a_includedPayloads.begin(), a_includedPayloads.end() },
		_excludedPayloads{ a_excludedPayloads.begin(), a_excludedPayloads.end() }
	{
		Register();
	}

	AnimationGraphEventHandler::~AnimationGraphEventHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl AnimationGraphEventHandler::ProcessEvent(const AnimationGraphEvent& a_event, RE::BSTEventSource<AnimationGraphEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* objectRef = a_event.ref;
		const auto* object = objectRef ? objectRef->GetBaseObject() : nullptr;

		if (!_objectFilter.Filter(objectRef) ||
			!VarFilter::FilterByStrings(a_event.eventName, _includedEventNames, _excludedEventNames) ||
			!VarFilter::FilterByStrings(a_event.payload, _includedPayloads, _excludedPayloads)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("ObjectRef"sv, objectRef);
		args.insert("Object"sv, object);
		args.insert("EventName"sv, a_event.eventName);
		args.insert("Payload"sv, a_event.payload);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void AnimationGraphEventHandler::Register()
	{
		AnimationGraphEventSource::GetEventSource()->RegisterSink(this);
	}

	void AnimationGraphEventHandler::Unregister()
	{
		AnimationGraphEventSource::GetEventSource()->UnregisterSink(this);
	}
}
