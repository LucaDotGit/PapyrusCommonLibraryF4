#pragma once

namespace System::ObjectReference
{
	static constexpr auto SCRIPT_NAME = "System:ObjectReference"sv;

	static constexpr auto NAME_KEY = "Name"sv;
	static constexpr auto TYPE_KEY = "Type"sv;

	static constexpr auto LINKED_DOOR_KEY = "LinkedDoor"sv;
	static constexpr auto POSITION_KEY = "Position"sv;
	static constexpr auto ROTATION_KEY = "Rotation"sv;

	static constexpr auto WARP_POSITION = false;

	using MapMarkerData = RE::BSScript::structure_wrapper<"System:ObjectReference", "MapMarkerData">;
	using DoorDestinationData = RE::BSScript::structure_wrapper<"System:ObjectReference", "DoorDestinationData">;

	static RE::TESBoundObject* GetBaseObject(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		return a_ref->GetBaseObject();
	}

	static void SetBaseObject(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::TESBoundObject* a_object)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_object) {
			a_vm.PostError(::Internal::Errors::FORM_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		F4SE::GetTaskInterface()->AddTask([&]() {
			a_ref->SetBaseObject(a_object);
		});
	}

	static ::Internal::Vectors::Vector3 GetPosition(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		return ::Internal::Vectors::MakeVector3(a_ref->GetPosition());
	}

	static void SetPosition(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		::Internal::Vectors::Vector3 a_position)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_position) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		const auto&& [x, y, z] = ::Internal::Vectors::GetVector3(a_position);
		const auto position = RE::NiPoint3A{ x, y, z };

		a_ref->SetPosition(position);
		a_ref->Update3DPosition(WARP_POSITION);
	}

	static ::Internal::Vectors::Vector3 GetRotation(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		return ::Internal::Vectors::MakeVector3(a_ref->GetRotation());
	}

	static void SetRotation(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		::Internal::Vectors::Vector3 a_rotation)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_rotation) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		const auto&& [x, y, z] = ::Internal::Vectors::GetVector3(a_rotation);
		const auto rotation = RE::NiPoint3A{ x, y, z };

		a_ref->SetRotation(rotation);
		a_ref->Update3DPosition(WARP_POSITION);
	}

	static RE::BGSLocation* GetLocationByMapMarker(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_markerRef)
	{
		if (!a_markerRef) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto* dataHandler = RE::TESDataHandler::GetSingleton();
		const auto& locations = dataHandler->GetFormArray<RE::BGSLocation>();

		for (auto* location : locations) {
			if (!location) {
				continue;
			}

			const auto lock = RE::BSAutoReadLock{ location->locker };

			const auto marker = location->worldLocMarker;
			if (marker && marker.get().get() == a_markerRef) {
				return location;
			}
		}

		return nullptr;
	}

	static MapMarkerData GetMapMarkerData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_markerRef)
	{
		if (!a_markerRef) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto extraList = a_markerRef->extraList;
		if (!extraList) {
			return nullptr;
		}

		const auto lock = RE::BSAutoReadLock{ extraList->extraRWLock };

		const auto* extraMarker = extraList->GetByType<RE::ExtraMapMarker>();
		const auto* markerData = extraMarker ? extraMarker->mapMarkerData : nullptr;

		if (!markerData) {
			return nullptr;
		}

		auto data = MapMarkerData();
		data.insert(NAME_KEY, markerData->fullName);
		data.insert(TYPE_KEY, markerData->type.underlying());

		return data;
	}

	static bool SetMapMarkerData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_markerRef,
		MapMarkerData a_data)
	{
		if (!a_markerRef) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto& extraList = a_markerRef->extraList;
		if (!extraList) {
			extraList = RE::make_smart<RE::ExtraDataList>();
		}

		const auto lock = RE::BSAutoWriteLock{ extraList->extraRWLock };

		auto* extraMarker = extraList->GetByType<RE::ExtraMapMarker>();
		auto hasData = extraMarker != nullptr;

		if (!hasData) {
			extraMarker = new RE::ExtraMapMarker();
		}

		auto*& data = extraMarker->mapMarkerData;
		if (!data) {
			data = new RE::MapMarkerData();
		}

		data->fullName = a_data.find<RE::BGSLocalizedString>(NAME_KEY).value_or(RE::BSFixedStringCS());
		data->type = a_data.find<RE::MapMarkerData::MARKER_TYPE>(TYPE_KEY).value_or(static_cast<RE::MapMarkerData::MARKER_TYPE>(-1));

		if (!hasData) {
			extraList->AddExtra(extraMarker);
		}

		return true;
	}

	static RE::TESObjectREFR* GetDroppedItemSource(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_itemRef)
	{
		if (!a_itemRef) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto extraList = a_itemRef->extraList;
		if (!extraList) {
			return nullptr;
		}

		const auto lock = RE::BSAutoReadLock{ extraList->extraRWLock };

		const auto* extraDropper = extraList->GetByType<RE::ExtraItemDropper>();
		if (!extraDropper) {
			return nullptr;
		}

		const auto& refHandle = extraDropper->handle;
		return refHandle ? refHandle.get().get() : nullptr;
	}

	static RE::TESObjectREFR* GetAshPileSource(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_itemRef)
	{
		if (!a_itemRef) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto extraList = a_itemRef->extraList;
		if (!extraList) {
			return nullptr;
		}

		const auto lock = RE::BSAutoReadLock{ extraList->extraRWLock };

		const auto* data = extraList->GetByType<RE::ExtraAshPileRef>();
		return data && data->handle ? data->handle.get().get() : nullptr;
	}

	static std::int32_t GetRefCount(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_itemRef)
	{
		if (!a_itemRef) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return 0;
		}

		const auto extraList = a_itemRef->extraList;
		if (!extraList) {
			return 1;
		}

		const auto lock = RE::BSAutoReadLock{ extraList->extraRWLock };

		const auto* data = extraList->GetByType<RE::ExtraCount>();
		return data ? data->count : 1;
	}

	static void SetRefCount(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_itemRef,
		std::int16_t a_count)
	{
		if (!a_itemRef) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		auto& extraList = a_itemRef->extraList;
		if (!extraList) {
			extraList = RE::make_smart<RE::ExtraDataList>();
		}

		const auto lock = RE::BSAutoWriteLock{ extraList->extraRWLock };

		auto* extraCount = extraList->GetByType<RE::ExtraCount>();
		if (extraCount) {
			extraCount->count = a_count;
			return;
		}

		extraCount = new RE::ExtraCount();
		extraCount->count = a_count;
		extraList->AddExtra(extraCount);
	}

	static DoorDestinationData GetDoorDestination(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_doorRef)
	{
		if (!a_doorRef) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto extraList = a_doorRef->extraList;
		if (!extraList) {
			return nullptr;
		}

		const auto lock = RE::BSAutoReadLock{ extraList->extraRWLock };

		const auto* extraTeleport = extraList->GetByType<RE::ExtraTeleport>();
		if (!extraTeleport) {
			return nullptr;
		}

		const auto* teleportData = extraTeleport->teleportData;
		if (!teleportData) {
			return nullptr;
		}

		const auto* linkedDoor = teleportData->linkedDoor ? teleportData->linkedDoor.get().get() : nullptr;

		auto position = ::Internal::Vectors::MakeVector3(teleportData->position);
		auto rotation = ::Internal::Vectors::MakeVector3(teleportData->rotation);

		auto data = DoorDestinationData();
		data.insert(LINKED_DOOR_KEY, linkedDoor);
		data.insert(POSITION_KEY, std::move(position));
		data.insert(ROTATION_KEY, std::move(rotation));

		return data;
	}

	static bool SetDoorDestination(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_doorRef,
		DoorDestinationData a_data)
	{
		if (!a_doorRef) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* linkedDoor = a_data.find<RE::TESObjectREFR*>(LINKED_DOOR_KEY).value_or(nullptr);
		if (!a_data) {
			a_vm.PostError("The linked door cannot be none"sv, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		const auto* baseObject = a_doorRef->GetBaseObject();
		if (!baseObject || !baseObject->Is<RE::TESObjectDOOR>()) {
			a_vm.PostError("The linked door is not a door"sv, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		if ((a_doorRef->formFlags & RE::TESObjectREFR::RecordFlags::kPersistent) == 0) {
			return false;
		}

		auto& extraList = linkedDoor->extraList;
		if (!extraList) {
			extraList = RE::make_smart<RE::ExtraDataList>();
		}

		const auto positionData = a_data.find<::Internal::Vectors::Vector3>(POSITION_KEY).value_or(nullptr);
		const auto rotationData = a_data.find<::Internal::Vectors::Vector3>(ROTATION_KEY).value_or(nullptr);

		const auto lock = RE::BSAutoWriteLock{ extraList->extraRWLock };

		auto* extraTeleport = extraList->GetByType<RE::ExtraTeleport>();
		auto hasData = extraTeleport != nullptr;

		if (!hasData) {
			extraTeleport = new RE::ExtraTeleport();
		}

		auto*& teleportData = extraTeleport->teleportData;
		if (!teleportData) {
			teleportData = new RE::DoorTeleportData();
		}

		constexpr auto DEFAULT_VECTOR = std::tuple<float, float, float>{ 999.0f, 999.0f, 999.0f };

		auto position = DEFAULT_VECTOR;
		auto rotation = DEFAULT_VECTOR;

		if (positionData) {
			position = ::Internal::Vectors::GetVector3(positionData);
		}

		if (rotationData) {
			rotation = ::Internal::Vectors::GetVector3(rotationData);
		}

		auto&& [x, y, z] = position;
		auto&& [rx, ry, rz] = rotation;

		teleportData->transitionCell = linkedDoor->parentCell;
		teleportData->linkedDoor = RE::ObjectRefHandle(linkedDoor);
		teleportData->position = { x, y, z };
		teleportData->rotation = { rx, ry, rz };

		if (!hasData) {
			extraList->AddExtra(extraTeleport);
		}

		return true;
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetBaseObject);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetBaseObject);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetPosition);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetPosition);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetRotation);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetRotation);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetLocationByMapMarker);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetMapMarkerData);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetMapMarkerData);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetDroppedItemSource);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetAshPileSource);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetRefCount);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetRefCount);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetDoorDestination);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetDoorDestination);

		return true;
	}
}
