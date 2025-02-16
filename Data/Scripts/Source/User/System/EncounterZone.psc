Scriptname System:EncounterZone Const Hidden Native

;/
	Provides common functions for encounter zones.
/;

Struct Data
	int Flags
	Form Owner
	int OwnerRank
	Location ParentLocation
	int MinLevel
	int MaxLevel
EndStruct

Struct GameData
	int DetachTime
	int AttachTime
	int ResetTime
	int ZoneLevel
EndStruct

Data Function GetData(EncounterZone akEncounterZone) Global Native
Function SetData(EncounterZone akEncounterZone, Data akData) Global Native

GameData Function GetGameData(EncounterZone akEncounterZone) Global Native
Function SetGameData(EncounterZone akEncounterZone, GameData akGameData) Global Native


bool Function GetNeverResets(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x1)
EndFunction
Function SetNeverResets(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x1, abValue)
EndFunction

bool Function GetMatchesPCBelowMin(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x2)
EndFunction
Function SetMatchesPCBelowMin(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x2, abValue)
EndFunction

bool Function GetIsCombatBoundaryDisabled(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x4)
EndFunction
Function SetIsCombatBoundaryDisabled(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x4, abValue)
EndFunction

bool Function GetIsWorkshopZone(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x8)
EndFunction
Function SetIsWorkshopZone(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x8, abValue)
EndFunction
