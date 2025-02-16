Scriptname System:MagicEffect Const Hidden Native

;/
	Provides common functions for magic effects.

	Notes:
	- For Archetypes, Cast Types and Target Types, see:
	  https://github.com/powerof3/CommonLibSSE/blob/e3626d228d60b92a82410accd475bffdd7245653/include/RE/M/MagicSystem.h#L10
/;

Struct Data
	int Flags
	int Archetype
	int CastType
	int TargetType
	ActorValue PrimaryValue
	ActorValue SecondaryValue
	float SecondaryValueWeight
	ActorValue ResistValue
	Perk ApplyingPerk
	float TaperCurve
	float TaperWeight
	float TaperDuration
	float BaseCost
	float SkillUsageMult
	VisualEffect HitVisuals
	VisualEffect EnchantVisuals
	ArtObject CastingArt
	Light CastingLight
	ArtObject HitArt
	EffectShader HitShader
	ArtObject EnchantArt
	EffectShader EnchantShader
	Projectile EffectProjectile
	ImpactDataSet ImpactData
	Explosion EffectExplosion
	ImageSpaceModifier ImageSpaceMod
	int SpellArea
	float SpellChargeTime
	float AIScore
	float AIDelayTime
	Spell EquipAbility
	string Description
EndStruct

Data Function GetData(MagicEffect akMagicEffect) Global Native
Function SetData(MagicEffect akMagicEffect, Data akData) Global Native


bool Function GetIsHostile(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x1)
EndFunction
Function SetIsHostile(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x1, abValue)
EndFunction

bool Function GetIsRecoverable(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x2)
EndFunction
Function SetIsRecoverable(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x2, abValue)
EndFunction

bool Function GetIsDetrimental(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x4)
EndFunction
Function SetIsDetrimental(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x4, abValue)
EndFunction

bool Function GetSnapsToNavMesh(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x8)
EndFunction
Function SetSnapsToNavMesh(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x8, abValue)
EndFunction

bool Function GetHasNoHitEvent(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x10)
EndFunction
Function SetHasNoHitEvent(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x10, abValue)
EndFunction

bool Function GetDispelsWithKeywords(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x100)
EndFunction
Function SetDispelsWithKeywords(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x100, abValue)
EndFunction

bool Function GetHasNoDuration(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x200)
EndFunction
Function SetHasNoDuration(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x200, abValue)
EndFunction

bool Function GetHasNoMagnitude(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x400)
EndFunction
Function SetHasNoMagnitude(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x400, abValue)
EndFunction

bool Function GetHasNoArea(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x800)
EndFunction
Function SetHasNoArea(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x800, abValue)
EndFunction

bool Function GetObjectPersists(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x1000)
EndFunction
Function SetObjectPersists(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x1000, abValue)
EndFunction

bool Function GetHasGoryVisuals(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x4000)
EndFunction
Function SetHasGoryVisuals(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x4000, abValue)
EndFunction

bool Function GetIsHiddenInUI(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x8000)
EndFunction
Function SetIsHiddenInUI(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x8000, abValue)
EndFunction

bool Function GetCannotRecast(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x20000)
EndFunction
Function SetCannotRecast(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x20000, abValue)
EndFunction

bool Function GetPowerAffectsMagnitude(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x200000)
EndFunction
Function SetPowerAffectsMagnitude(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x200000, abValue)
EndFunction

bool Function GetPowerAffectsDuration(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x400000)
EndFunction
Function SetPowerAffectsDuration(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x400000, abValue)
EndFunction

bool Function GetIsPainless(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x4000000)
EndFunction
Function SetIsPainless(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x4000000, abValue)
EndFunction

bool Function GetHasNoHitEffect(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x8000000)
EndFunction
Function SetHasNoHitEffect(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x8000000, abValue)
EndFunction

bool Function GetHasNoDeathDispel(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x10000000)
EndFunction
Function SetHasNoDeathDispel(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x10000000, abValue)
EndFunction
