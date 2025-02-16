#include "Internal/Events/Handlers/CrosshairRefChangeHandler.hpp"

#include "Internal/Callbacks/CrosshairRefHandler.hpp"

namespace Internal::Events
{
	CrosshairRefChangeHandler::CrosshairRefChangeHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
		const std::vector<const RE::BSScript::Variable*>& a_excludedObjects) :
		IEventHandler(a_receiver),
		_filter{ a_includedObjects, a_excludedObjects }
	{
		Register();
	}

	CrosshairRefChangeHandler::~CrosshairRefChangeHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl CrosshairRefChangeHandler::ProcessEvent(const RE::ViewCasterUpdateEvent&, RE::BSTEventSource<RE::ViewCasterUpdateEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* refHandler = CrosshairRefHandler::GetSingleton();

		const auto previousRef = refHandler->GetPreviousRef();
		const auto currentRef = refHandler->GetCurrentRef();

		if (previousRef == currentRef) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto& selectedRef = currentRef ? currentRef : previousRef;

		const auto* objectRef = selectedRef.get().get();
		const auto* object = objectRef ? objectRef->GetBaseObject() : nullptr;

		if (!_filter.Filter(objectRef)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("ObjectRef"sv, objectRef);
		args.insert("Object"sv, object);
		args.insert("IsTargeted"sv, currentRef == selectedRef);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void CrosshairRefChangeHandler::Register()
	{
		RE::ViewCasterUpdateEvent::GetEventSource()->RegisterSink(this);
	}

	void CrosshairRefChangeHandler::Unregister()
	{
		RE::ViewCasterUpdateEvent::GetEventSource()->UnregisterSink(this);
	}
}
