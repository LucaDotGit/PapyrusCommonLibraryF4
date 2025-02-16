#include "Internal/Events/Handlers/ObjectLoadUnloadHandler.hpp"

namespace Internal::Events
{
	ObjectLoadUnloadHandler::ObjectLoadUnloadHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
		const std::vector<const RE::BSScript::Variable*>& a_excludedObjects) :
		IEventHandler(a_receiver),
		_filter{ a_includedObjects, a_excludedObjects }
	{
		Register();
	}

	ObjectLoadUnloadHandler::~ObjectLoadUnloadHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl ObjectLoadUnloadHandler::ProcessEvent(const RE::TESObjectLoadedEvent& a_event, RE::BSTEventSource<RE::TESObjectLoadedEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* objectRef = RE::TESForm::GetFormByID<RE::TESObjectREFR>(a_event.formID);
		const auto* object = objectRef ? objectRef->GetBaseObject() : nullptr;

		if (!_filter.Filter(objectRef)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("ObjectRef"sv, objectRef);
		args.insert("Object"sv, object);
		args.insert("IsLoaded"sv, a_event.loaded);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void ObjectLoadUnloadHandler::Register()
	{
		RE::TESObjectLoadedEvent::GetEventSource()->RegisterSink(this);
	}

	void ObjectLoadUnloadHandler::Unregister()
	{
		RE::TESObjectLoadedEvent::GetEventSource()->UnregisterSink(this);
	}
}
