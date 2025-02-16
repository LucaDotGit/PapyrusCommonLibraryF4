Scriptname System:Explosion Const Hidden Native

;/
	Provides common functions for explosions.

	Sound Levels:
	00	Loud
	01	Normal
	02	Silent
	03	Very Loud
	04 	Quiet

	Stagger Magnitudes:
	00	None
	01	Small
	02	Medium
	03	Large
	04	Extra Large
/;

Struct Data
	int Flags
	Light UsedLight
	Sound Sound01
	Sound Sound02
	ImpactDataSet ImpactData
	Form PlacedObject
	float PlacedObjectAutoFadeDelay
	Projectile SpawnedProjectile
	Vectors:Vector3 SpawnPosition
	float ProjectileSpreadAngle
	int ProjectileCount
	float Force
	float Damage
	float InnerRadius
	float OuterRadius
	float ImageSpaceRadius
	float VerticalOffsetMult
	int SoundLevel
	int StaggerMagnitude
EndStruct

Data Function GetData(Explosion akExplosion) Global Native
Function SetData(Explosion akExplosion, Data akData) Global Native


bool Function GetAlwaysUsesWorldOrientation(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x2)
EndFunction
Function SetAlwaysUsesWorldOrientation(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x2, abValue)
EndFunction

bool Function GetAlwaysKnocksDown(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x4)
EndFunction
Function SetAlwaysKnocksDown(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x4, abValue)
EndFunction

bool Function GetKnocksDownByFormula(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x8)
EndFunction
Function SetKnocksDownByFormula(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x8, abValue)
EndFunction

bool Function GetIgnoresLOSCheck(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x10)
EndFunction
Function SetIgnoresLOSCheck(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x10, abValue)
EndFunction

bool Function GetPushesExplosionSourceRefOnly(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x20)
EndFunction
Function SetPushesExplosionSourceRefOnly(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x20, abValue)
EndFunction

bool Function GetIgnoresImageSpaceSwap(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x40)
EndFunction
Function SetIgnoresImageSpaceSwap(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x40, abValue)
EndFunction

bool Function GetHasChain(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x80)
EndFunction
Function SetHasChain(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x80, abValue)
EndFunction

bool Function GetHasNoControllerVibration(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x100)
EndFunction
Function SetHasNoControllerVibration(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x100, abValue)
EndFunction

bool Function GetPlacedObjectPersists(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x200)
EndFunction
Function SetPlacedObjectPersists(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x200, abValue)
EndFunction

bool Function GetSkipsUnderwaterTest(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x400)
EndFunction
Function SetSkipsUnderwaterTest(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x400, abValue)
EndFunction
