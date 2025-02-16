#include "Internal/Events/Handlers/LocationLoadHandler.hpp"

namespace Internal::Events
{
	LocationLoadHandler::LocationLoadHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
		const std::vector<const RE::BSScript::Variable*>& a_excludedObjects) :
		IEventHandler(a_receiver),
		_filter{ a_includedObjects, a_excludedObjects }
	{
		Register();
	}

	LocationLoadHandler::~LocationLoadHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl LocationLoadHandler::ProcessEvent(const LocationLoadEvent& a_event, RE::BSTEventSource<LocationLoadEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* object = a_event.location;

		if (!_filter.Filter(object)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("Object"sv, object);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void LocationLoadHandler::Register()
	{
		LocationLoadSource::GetEventSource()->RegisterSink(this);
	}

	void LocationLoadHandler::Unregister()
	{
		LocationLoadSource::GetEventSource()->UnregisterSink(this);
	}
}
