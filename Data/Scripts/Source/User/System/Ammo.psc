Scriptname System:Ammo Const Hidden Native

;/
	Provides common functions for ammo.
/;

Struct Data
	int Flags
	Projectile UsedProjectile
	int Health
	float Damage
	string ShortName
EndStruct

Data Function GetData(Ammo akAmmo) Global Native
Function SetData(Ammo akAmmo, Data akData) Global Native


bool Function GetIgnoresNormalWeaponResist(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x1)
EndFunction
Function SetIgnoresNormalWeaponResist(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x1, abValue)
EndFunction

bool Function GetIsNonPlayable(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x2)
EndFunction
Function SetIsNonPlayable(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x2, abValue)
EndFunction

bool Function GetHasCountBased3D(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x4)
EndFunction
Function SetHasCountBased3D(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x4, abValue)
EndFunction
