Scriptname System:WorldSpace Const Hidden Native

;/
	Provides common functions for world spaces.
/;

Struct Data
	int FormFlags
	int Flags
EndStruct

Data Function GetData(WorldSpace akWorldSpace) Global Native
Function SetData(WorldSpace akWorldSpace, Data akData) Global Native


bool Function GetIsSmallWorld(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x1)
EndFunction
Function SetIsSmallWorld(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x1, abValue)
EndFunction

bool Function GetCannotFastTravel(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x2)
EndFunction
Function SetCannotFastTravel(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x2, abValue)
EndFunction

bool Function GetHasNoLODWater(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x8)
EndFunction
Function SetHasNoLODWater(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x8, abValue)
EndFunction

bool Function GetHasNoLandscape(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x10)
EndFunction
Function SetHasNoLandscape(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x10, abValue)
EndFunction

bool Function GetHasNoSky(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x20)
EndFunction
Function SetHasNoSky(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x20, abValue)
EndFunction

bool Function GetHasFixedDimensions(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x40)
EndFunction
Function SetHasFixedDimensions(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x40, abValue)
EndFunction

bool Function GetHasNoGrass(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x80)
EndFunction
Function SetHasNoGrass(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x80, abValue)
EndFunction


bool Function GetCannotWait(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x8000)
EndFunction
Function SetCannotWait(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x8000, abValue)
EndFunction
