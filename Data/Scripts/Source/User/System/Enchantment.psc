Scriptname System:Enchantment Const Hidden Native

;/
	Provides common functions for enchantments.

	Notes:
	- For a list of all Enchantment Types, Cast Types and Target Types, see:
	  https://github.com/powerof3/CommonLibSSE/blob/e3626d228d60b92a82410accd475bffdd7245653/include/RE/M/MagicSystem.h#L10
/;

Struct Data
	int Flags
	int Type
	int CastType
	int TargetType
	float ChargeTime
	Enchantment BaseEnchantment
	FormList WornRestrictions
	MagicItem:Entry[] Effects
EndStruct

Data Function GetData(Enchantment akEnchantment) Global Native
Function SetData(Enchantment akEnchantment, Data akData) Global Native


bool Function GetHasManualCostCalc(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x1)
EndFunction
Function SetHasManualCostCalc(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x1, abValue)
EndFunction

bool Function GetHasExtendedDuration(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x8)
EndFunction
Function SetHasExtendedDuration(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x8, abValue)
EndFunction
