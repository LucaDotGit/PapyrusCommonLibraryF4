Scriptname System:Projectile Const Hidden Native

;/
	Provides common functions for projectiles.

	Projectile Types:
	01	Missile
	02	Lobber
	04	Beam
	08	Flame
	16	Cone
	32	Barrier
	64	Arrow

	Sound Levels:
	00	Loud
	01	Normal
	02	Silent
	03	Very Loud
	04 	Quiet
/;

Struct Data
	int Flags
	int Type
	float Speed
	float Gravity
	float Range
	float ImpactForce
	int TracerFrequency
	float FadeDuration
	float ConeSpread
	float CollisionRadius
	float Lifetime
	float RelaunchInterval
	Light MuzzleFlashLight
	float MuzzleFlashDuration
	Light EffectLight
	Weapon SourceWeapon
	TextureSet Decal
	Sound PlayedSound
	Sound CountdownSound
	Sound DisarmSound
	int SoundLevel
	Explosion ExplosionObject
	float ExplosionTimer
	float ExplosionProximity
	CollisionLayer Layer
	Projectile VATSProjectile
EndStruct

Data Function GetData(Projectile akProjectile) Global Native
Function SetData(Projectile akProjectile, Data akData) Global Native


bool Function GetHasHitScan(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x1)
EndFunction
Function SetHasHitScan(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x1, abValue)
EndFunction

bool Function GetHasExplosion(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x2)
EndFunction
Function SetHasExplosion(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x2, abValue)
EndFunction

bool Function GetHasAltExplosionTrigger(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x4)
EndFunction
Function SetHasAltExplosionTrigger(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x4, abValue)
EndFunction

bool Function GetHasMuzzleFlash(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x8)
EndFunction
Function SetHasMuzzleFlash(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x8, abValue)
EndFunction

bool Function GetCanBeDisarmed(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x20)
EndFunction
Function SetCanBeDisarmed(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x20, abValue)
EndFunction

bool Function GetCanBePickedUp(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x40)
EndFunction
Function SetCanBePickedUp(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x40, abValue)
EndFunction

bool Function GetIsSupersonic(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x80)
EndFunction
Function SetIsSupersonic(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x80, abValue)
EndFunction

bool Function GetPinsLimbs(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x100)
EndFunction
Function SetPinsLimbs(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x100, abValue)
EndFunction

bool Function GetPassesSmallTransparent(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x200)
EndFunction
Function SetPassesSmallTransparent(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x200, abValue)
EndFunction

bool Function GetIsAimCorrectionDisabled(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x400)
EndFunction
Function SetIsAimCorrectionDisabled(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x400, abValue)
EndFunction

bool Function GetPenetratesGeometry(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x800)
EndFunction
Function SetPenetratesGeometry(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x800, abValue)
EndFunction

bool Function GetUpdatesContinuously(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x1000)
EndFunction
Function SetUpdatesContinuously(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x1000, abValue)
EndFunction

bool Function GetSeeksTarget(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x2000)
EndFunction
Function SetSeeksTarget(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x2000, abValue)
EndFunction
