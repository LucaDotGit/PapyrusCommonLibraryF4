Scriptname System:Activator Const Hidden Native

;/
	Provides common functions for activators.
/;

Struct Data
	int FormFlags
	int Flags
	Sound LoopSound
	Sound ActivateSound
	WaterType Water
EndStruct

Data Function GetData(Activator akActivator) Global Native
Function SetData(Activator akActivator, Data akData) Global Native


bool Function GetHasNoDisplacement(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x1)
EndFunction
Function SetHasNoDisplacement(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x1, abValue)
EndFunction

bool Function GetIsIgnoredBySandbox(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x2)
EndFunction
Function SetIsIgnoredBySandbox(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x2, abValue)
EndFunction

bool Function GetIsProceduralWater(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x4)
EndFunction
Function SetIsProceduralWater(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x4, abValue)
EndFunction

bool Function GetIsLODWater(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x8)
EndFunction
Function SetIsLODWater(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x8, abValue)
EndFunction

bool Function GetIsRadio(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x10)
EndFunction
Function SetIsRadio(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x10, abValue)
EndFunction


bool Function GetHasTreeLOD(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x40)
EndFunction
Function SetHasTreeLOD(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x40, abValue)
EndFunction

bool Function GetMustUpdateAnims(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x100)
EndFunction
Function SetMustUpdateAnims(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x100, abValue)
EndFunction

bool Function GetIsHiddenFromLocalMap(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x200)
EndFunction
Function SetIsHiddenFromLocalMap(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x200, abValue)
EndFunction

bool Function GetHasDistantLOD(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x8000)
EndFunction
Function SetHasDistantLOD(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x8000, abValue)
EndFunction

bool Function GetHasRandomAnimStart(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x10000)
EndFunction
Function SetHasRandomAnimStart(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x10000, abValue)
EndFunction

bool Function GetIsDangerous(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x20000)
EndFunction
Function SetIsDangerous(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x20000, abValue)
EndFunction

bool Function GetIgnoresObjectInteraction(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x100000)
EndFunction
Function SetIgnoresObjectInteraction(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x100000, abValue)
EndFunction

bool Function GetIsMarker(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x800000)
EndFunction
Function SetIsMarker(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x800000, abValue)
EndFunction

bool Function GetIsObstacle(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x2000000)
EndFunction
Function SetIsObstacle(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x2000000, abValue)
EndFunction

bool Function GetHasNavMeshFilter(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x4000000)
EndFunction
Function SetHasNavMeshFilter(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x4000000, abValue)
EndFunction

bool Function GetHasNavMeshBoundingBox(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x8000000)
EndFunction
Function SetHasNavMeshBoundingBox(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x8000000, abValue)
EndFunction

bool Function GetIsUsableByChildren(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x20000000)
EndFunction
Function SetIsUsableByChildren(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x20000000, abValue)
EndFunction

bool Function GetHasNavMeshGround(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x40000000)
EndFunction
Function SetHasNavMeshGround(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x40000000, abValue)
EndFunction
