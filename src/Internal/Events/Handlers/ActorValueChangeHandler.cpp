#include "Internal/Events/Handlers/ActorValueChangeHandler.hpp"

namespace Internal::Events
{
	ActorValueChangeHandler::ActorValueChangeHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
		const std::vector<const RE::BSScript::Variable*>& a_excludedObjects,
		const std::vector<const RE::BSScript::Variable*>& a_includedActorValues,
		const std::vector<const RE::BSScript::Variable*>& a_excludedActorValues) :
		IEventHandler(a_receiver),
		_objectFilter{ a_includedObjects, a_excludedObjects },
		_actorValueFilter{ a_includedActorValues, a_excludedActorValues }
	{
		Register();
	}

	ActorValueChangeHandler::~ActorValueChangeHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl ActorValueChangeHandler::ProcessEvent(const ActorValueChangeEvent& a_event, RE::BSTEventSource<ActorValueChangeEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* objectRef = a_event.ref;
		const auto* object = objectRef ? objectRef->GetBaseObject() : nullptr;

		if (!_objectFilter.Filter(objectRef) ||
			!_actorValueFilter.Filter(a_event.valueHolder)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("ObjectRef"sv, objectRef);
		args.insert("Object"sv, object);
		args.insert("ValueHolder"sv, a_event.valueHolder);
		args.insert("OldValue"sv, a_event.oldValue);
		args.insert("NewValue"sv, a_event.newValue);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void ActorValueChangeHandler::Register()
	{
		ActorValueChangeSource::GetEventSource()->RegisterSink(this);
	}

	void ActorValueChangeHandler::Unregister()
	{
		ActorValueChangeSource::GetEventSource()->UnregisterSink(this);
	}
}
