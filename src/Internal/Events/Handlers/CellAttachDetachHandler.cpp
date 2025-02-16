#include "Internal/Events/Handlers/CellAttachDetachHandler.hpp"

namespace Internal::Events
{
	CellAttachDetachHandler::CellAttachDetachHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
		const std::vector<const RE::BSScript::Variable*>& a_excludedObjects) :
		IEventHandler(a_receiver),
		_filter{ a_includedObjects, a_excludedObjects }
	{
		Register();
	}

	CellAttachDetachHandler::~CellAttachDetachHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl CellAttachDetachHandler::ProcessEvent(const RE::CellAttachDetachEvent& a_event, RE::BSTEventSource<RE::CellAttachDetachEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* object = a_event.cell;

		if (!_filter.Filter(object)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto isAttached = a_event.type == RE::CellAttachDetachEvent::EVENT_TYPE::kPreAttach ||
								a_event.type == RE::CellAttachDetachEvent::EVENT_TYPE::kPostAttach;
		const auto isPreProcess = a_event.type == RE::CellAttachDetachEvent::EVENT_TYPE::kPreAttach ||
								  a_event.type == RE::CellAttachDetachEvent::EVENT_TYPE::kPreDetach;

		auto args = EventArgs();
		args.insert("Object"sv, object);
		args.insert("IsAttached"sv, isAttached);
		args.insert("IsPreProcess"sv, isPreProcess);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void CellAttachDetachHandler::Register()
	{
		auto& eventSource = RE::CellAttachDetachEventSource::CellAttachDetachEventSourceSingleton::GetSingleton();
		eventSource.source.RegisterSink(this);
	}

	void CellAttachDetachHandler::Unregister()
	{
		auto& eventSource = RE::CellAttachDetachEventSource::CellAttachDetachEventSourceSingleton::GetSingleton();
		eventSource.source.UnregisterSink(this);
	}

}
