Scriptname System:ObjectReference Const Hidden Native

;/
	Provides common functions for object references.

	Notes:
	- For a list of all map marker types, see:
	  https://github.com/shad0wshayd3-FO4/CommonLibF4/blob/01d7eeef39fd5d812595062a53af7a40e9f3e401/CommonLibF4/include/RE/Bethesda/BSExtraData.h#L383
/;

;/
	Start of delayed functions.
/;

bool Function GetIsHarvested(ObjectReference akRef) Global
	return System:Form.HasFlag(akRef, 0x2000)
EndFunction
Function SetIsHarvested(ObjectReference akRef, bool abValue) Global
	akRef.SetHarvested(abValue)
EndFunction

Form Function GetBaseObject(ObjectReference akRef) Global Native
Function SetBaseObject(ObjectReference akRef, Form akObject) Global Native

Vectors:Vector3 Function GetPosition(ObjectReference akRef) Global Native
Function SetPosition(ObjectReference akRef, Vectors:Vector3 akPosition) Global Native

Vectors:Vector3 Function GetRotation(ObjectReference akRef) Global Native
Function SetRotation(ObjectReference akRef, Vectors:Vector3 akRotation) Global Native

;/
	End of delayed functions.
/;

Location Function GetLocationByMapMarker(ObjectReference akMarkerRef) Global Native

Struct MapMarkerData
	string Name
	int Type
EndStruct

MapMarkerData Function GetMapMarkerData(ObjectReference akMarkerRef) Global Native
bool Function SetMapMarkerData(ObjectReference akMarkerRef, MapMarkerData akData) Global Native

ObjectReference Function GetDroppedItemSource(ObjectReference akItemRef) Global Native
ObjectReference Function GetAshPileSource(ObjectReference akAshPileRef) Global Native

; It is used for item stacks.
int Function GetRefCount(ObjectReference akRef) Global Native
Function SetRefCount(ObjectReference akRef, int aiValue) Global Native

Struct DoorDestinationData
	ObjectReference LinkedDoor
	Vectors:Vector3 Position
	Vectors:Vector3 Rotation
EndStruct

DoorDestinationData Function GetDoorDestination(ObjectReference akDoorRef) Global Native
bool Function SetDoorDestination(ObjectReference akDoorRef, DoorDestinationData akData) Global Native
