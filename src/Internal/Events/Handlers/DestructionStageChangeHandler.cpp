#include "Internal/Events/Handlers/DestructionStageChangeHandler.hpp"

namespace Internal::Events
{
	DestructionStageChangeHandler::DestructionStageChangeHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
		const std::vector<const RE::BSScript::Variable*>& a_excludedObjects,
		const std::vector<std::uint32_t>& a_includedOldStages,
		const std::vector<std::uint32_t>& a_excludedOldStages,
		const std::vector<std::uint32_t>& a_includedNewStages,
		const std::vector<std::uint32_t>& a_excludedNewStages) :
		IEventHandler(a_receiver),
		_filter{ a_includedObjects, a_excludedObjects },
		_includedOldStages{ a_includedOldStages.begin(), a_includedOldStages.end() },
		_excludedOldStages{ a_excludedOldStages.begin(), a_excludedOldStages.end() },
		_includedNewStages{ a_includedNewStages.begin(), a_includedNewStages.end() },
		_excludedNewStages{ a_excludedNewStages.begin(), a_excludedNewStages.end() }
	{
		Register();
	}

	DestructionStageChangeHandler::~DestructionStageChangeHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl DestructionStageChangeHandler::ProcessEvent(const DestructionStageChangeEvent& a_event, RE::BSTEventSource<DestructionStageChangeEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* objectRef = a_event.ref;
		const auto* object = objectRef ? objectRef->GetBaseObject() : nullptr;

		if (!VarFilter::FilterByT(a_event.oldStage, _includedOldStages, _excludedOldStages) ||
			!VarFilter::FilterByT(a_event.newStage, _includedNewStages, _excludedNewStages) ||
			!_filter.Filter(objectRef)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto args = EventArgs();
		args.insert("ObjectRef"sv, objectRef);
		args.insert("Object"sv, object);
		args.insert("OldStage"sv, a_event.oldStage);
		args.insert("NewStage"sv, a_event.newStage);

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void DestructionStageChangeHandler::Register()
	{
		DestructionStageChangeSource::GetEventSource()->RegisterSink(this);
	}

	void DestructionStageChangeHandler::Unregister()
	{
		DestructionStageChangeSource::GetEventSource()->UnregisterSink(this);
	}
}
