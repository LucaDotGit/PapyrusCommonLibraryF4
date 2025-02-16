Scriptname System:Container Const Hidden Native

;/
	Provides common functions for containers.
/;

Struct Data
	int FormFlags
	int Flags
	Sound OpenSound
	Sound CloseSound
	Sound TakeAllSound
	Entry[] Items
EndStruct

Struct Entry
	Form Item
	int Count
	Form Owner
EndStruct

Data Function GetData(Container akContainer) Global Native
Function SetData(Container akContainer, Data akData) Global Native

Entry Function CreateEntry(Form akItem, int aiCount = 1, Form akOwner = none) Global
	Entry item = new Entry
	item.Item = akItem
	item.Count = aiCount
	item.Owner = akOwner
	return item
EndFunction


bool Function GetAllowsSoundOnAnim(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x1)
EndFunction
Function SetAllowsSoundOnAnim(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x1, abValue)
EndFunction

bool Function GetRespawns(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x2)
EndFunction
Function SetRespawns(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x2, abValue)
EndFunction

bool Function GetShowsOwner(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x4)
EndFunction
Function SetShowsOwner(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x4, abValue)
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

bool Function GetHasNavMeshGround(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x40000000)
EndFunction
Function SetHasNavMeshGround(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x40000000, abValue)
EndFunction
