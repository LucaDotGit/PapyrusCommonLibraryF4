Scriptname System:MagicItem Const Hidden

;/
	Provides shared data for potions, spells and enchantments.
/;

Struct Entry
	MagicEffect Effect
	float Magnitude
	int Area
	int Duration
EndStruct

Entry Function CreateEntry(MagicEffect akEffect, float afMagnitude = 0.0, int aiArea = 0, int aiDuration = 0) Global
	Entry entry = new Entry
	entry.Effect = akEffect
	entry.Magnitude = afMagnitude
	entry.Area = aiArea
	entry.Duration = aiDuration
	return entry
EndFunction
