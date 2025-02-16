#include "Internal/Events/Handlers/CellLoadHandler.hpp"

namespace Internal::Events
{
	CellLoadHandler::CellLoadHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
		const std::vector<const RE::BSScript::Variable*>& a_excludedObjects) :
		IEventHandler(a_receiver),
		_filter{ a_includedObjects, a_excludedObjects }
	{
		Register();
	}

	CellLoadHandler::~CellLoadHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl CellLoadHandler::ProcessEvent(const CellLoadEvent& a_event, RE::BSTEventSource<CellLoadEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* object = a_event.cell;

		if (!_filter.Filter(object)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("Object"sv, object);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void CellLoadHandler::Register()
	{
		CellLoadSource::GetEventSource()->RegisterSink(this);
	}

	void CellLoadHandler::Unregister()
	{
		CellLoadSource::GetEventSource()->UnregisterSink(this);
	}
}
