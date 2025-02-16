Scriptname System:Potion Const Hidden Native

;/
	Provides common functions for potions.
/;

Struct Data
	int Flags
	Sound CraftSound
	Sound ConsumeSound
	Spell Addiction
	float AddictionChance
	string AddictionName
	MagicItem:Entry[] Effects
EndStruct

Data Function GetData(Potion akPotion) Global Native
Function SetData(Potion akPotion, Data akData) Global Native


bool Function GetIsFood(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x2)
EndFunction
Function SetIsFood(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x2, abValue)
EndFunction

bool Function GetIsPoison(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x20000)
EndFunction
Function SetIsPoison(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x20000, abValue)
EndFunction

bool Function GetIsMedicine(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x40000)
EndFunction
Function SetIsMedicine(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x40000, abValue)
EndFunction
