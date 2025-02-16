Scriptname System:Cell Const Hidden Native

;/
	Provides common non-delayed functions for cells.

	Notes:
	- The `Var[]` filters support form types (int), mod names (string), references, base objects, keywords, factions, races and form lists (recursive).
	- For a list of all form types, see:
	  https://github.com/alandtse/CommonLibF4/blob/814cbdb9ce9effb337d07c2ae6d4c13b5e7aa2aa/CommonLibF4/include/RE/Bethesda/TESForms.h#L196.
/;

Struct Data
	int FormFlags
	int Flags
EndStruct

Data Function GetData(Cell akCell) Global Native
Function SetData(Cell akCell, Data akData) Global Native

ObjectReference[] Function FindAllRefs(Cell akOriginCell, \
	Var[] akIncludedObjects = none, Var[] akExcludedObjects = none) Global Native
ObjectReference[] Function FindAllRefsInRange(Cell akOriginCell, Vectors:Vector3 akCenter, float afRadius, \
	Var[] akIncludedObjects = none, Var[] akExcludedObjects = none) Global Native
ObjectReference[] Function FindAllRefsInRangeFromRef(ObjectReference akOriginRef, float afRadius, \
	Var[] akIncludedObjects = none, Var[] akExcludedObjects = none) Global Native

bool Function GetIsInterior(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x1)
EndFunction
Function SetIsInterior(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x1, abValue)
EndFunction

bool Function GetHasWater(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x2)
EndFunction
Function SetHasWater(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x2, abValue)
EndFunction

bool Function GetCanFastTravel(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x4)
EndFunction
Function SetCanFastTravel(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x4, abValue)
EndFunction

bool Function GetHasNoLODWater(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x8)
EndFunction
Function SetHasNoLODWater(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x8, abValue)
EndFunction

bool Function GetIsPublic(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x20)
EndFunction
Function SetIsPublic(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x20, abValue)
EndFunction

bool Function GetIsHandChanged(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x40)
EndFunction
Function SetIsHandChanged(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x40, abValue)
EndFunction

bool Function GetShowsSky(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x80)
EndFunction
Function SetShowsSky(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x80, abValue)
EndFunction

bool Function GetUsesSkyLighting(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x100)
EndFunction
Function SetUsesSkyLighting(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x100, abValue)
EndFunction

bool Function GetHasExitWarning(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x200)
EndFunction
Function SetHasExitWarning(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x200, abValue)
EndFunction

bool Function GetIsHiddenFromInteriorList(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x400)
EndFunction
Function SetIsHiddenFromInteriorList(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x400, abValue)
EndFunction

bool Function GetUsesSunlightShadows(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x800)
EndFunction
Function SetUsesSunlightShadows(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x800, abValue)
EndFunction

bool Function GetHasDistantLODOnly(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x1000)
EndFunction
Function SetHasDistantLODOnly(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x1000, abValue)
EndFunction

bool Function GetCompanionsCannotFastTravel(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x2000)
EndFunction
Function SetCompanionsCannotFastTravel(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x2000, abValue)
EndFunction


bool Function GetIsOffLimits(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x20000)
EndFunction
Function SetIsOffLimits(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x20000, abValue)
EndFunction

bool Function GetCannotWait(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x80000)
EndFunction
Function SetCannotWait(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x80000, abValue)
EndFunction
