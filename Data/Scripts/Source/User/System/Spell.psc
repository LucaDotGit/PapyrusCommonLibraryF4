Scriptname System:Spell Const Hidden Native

;/
	Provides common functions for spells.

	For a list of all Spell Types, Cast Types and Target Types, see:
	https://github.com/powerof3/CommonLibSSE/blob/e3626d228d60b92a82410accd475bffdd7245653/include/RE/M/MagicSystem.h#L10
/;

Struct Data
	int Flags
	int Type
	int CastType
	int TargetType
	float Range
	float ChargeTime
	float CastDuration
	Perk CastingPerk
	MagicItem:Entry[] Effects
EndStruct

Data Function GetData(Spell akSpell) Global Native
Function SetData(Spell akSpell, Data akData) Global Native


bool Function GetHasManualCostCalc(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x1)
EndFunction
Function SetHasManualCostCalc(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x1, abValue)
EndFunction

bool Function GetIsPCStartSpell(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x20000)
EndFunction
Function SetIsPCStartSpell(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x20000, abValue)
EndFunction

bool Function GetIsInstantCast(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x40000)
EndFunction
Function SetIsInstantCast(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x40000, abValue)
EndFunction

bool Function GetAreaEffectIgnoresLOS(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x80000)
EndFunction
Function SetAreaEffectIgnoresLOS(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x80000, abValue)
EndFunction

bool Function GetIgnoresResist(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x100000)
EndFunction
Function SetIgnoresResist(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x100000, abValue)
EndFunction

bool Function GetHasNoAbsorbReflect(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x200000)
EndFunction
Function SetHasNoAbsorbReflect(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x200000, abValue)
EndFunction

bool Function GetHasNoDualCastMods(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x800000)
EndFunction
Function SetHasNoDualCastMods(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x800000, abValue)
EndFunction
