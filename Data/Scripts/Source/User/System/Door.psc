Scriptname System:Door Const Hidden Native

;/
	Provides common functions for doors.
/;

Struct Data
	int FormFlags
	int Flags
	Sound OpenSound
	Sound CloseSound
	Sound LoopSound
	string AltOpenText
	string AltCloseText
EndStruct

Data Function GetData(Door akDoor) Global Native
Function SetData(Door akDoor, Data akData) Global Native


bool Function GetIsAutomatic(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x2)
EndFunction
Function SetIsAutomatic(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x2, abValue)
EndFunction

bool Function GetIsHidden(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x4)
EndFunction
Function SetIsHidden(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x4, abValue)
EndFunction

bool Function GetIsUsedMinimally(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x8)
EndFunction
Function SetIsUsedMinimally(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x8, abValue)
EndFunction

bool Function GetIsSlidable(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x10)
EndFunction
Function SetIsSlidable(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x10, abValue)
EndFunction

bool Function GetCannotOpenInCombatSearch(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x20)
EndFunction
Function SetCannotOpenInCombatSearch(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x20, abValue)
EndFunction

bool Function GetHasNoDestinationText(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x40)
EndFunction
Function SetHasNoDestinationText(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x40, abValue)
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

bool Function GetIsMarker(Data akData) Global
	return System:Operator.HasFlag(akData.FormFlags, 0x800000)
EndFunction
Function SetIsMarker(Data akData, bool abValue) Global
	akData.FormFlags = System:Operator.SetFlag(akData.FormFlags, 0x800000, abValue)
EndFunction
