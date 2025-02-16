#include "Internal/Events/Handlers/ObjectGrabReleaseHandler.hpp"

namespace Internal::Events
{
	ObjectGrabReleaseHandler::ObjectGrabReleaseHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
		const std::vector<const RE::BSScript::Variable*>& a_excludedObjects) :
		IEventHandler(a_receiver),
		_filter{ a_includedObjects, a_excludedObjects }
	{
		Register();
	}

	ObjectGrabReleaseHandler::~ObjectGrabReleaseHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl ObjectGrabReleaseHandler::ProcessEvent(const ObjectGrabReleaseEvent& a_event, RE::BSTEventSource<ObjectGrabReleaseEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* objectRef = a_event.ref;
		const auto* object = objectRef ? objectRef->GetBaseObject() : nullptr;

		if (!_filter.Filter(objectRef)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("ObjectRef"sv, objectRef);
		args.insert("Object"sv, object);
		args.insert("IsGrabbed"sv, a_event.isGrabbed);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void ObjectGrabReleaseHandler::Register()
	{
		ObjectGrabReleaseSource::GetEventSource()->RegisterSink(this);
	}

	void ObjectGrabReleaseHandler::Unregister()
	{
		ObjectGrabReleaseSource::GetEventSource()->UnregisterSink(this);
	}
}
