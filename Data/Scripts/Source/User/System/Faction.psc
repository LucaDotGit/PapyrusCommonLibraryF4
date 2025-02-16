Scriptname System:Faction Const Hidden Native

;/
	Provides common functions for factions.

	Combat Reactions:
	00	Neutral
	01	Enemy
	02	Ally
	03	Friend
/;

Struct Data
	int Flags
	Relation[] Relations
	ObjectReference ExteriorJailMarker
	ObjectReference CompanionWaitMarker
	ObjectReference StolenItemsContainer
	ObjectReference PlayerInventoryContainer
	FormList SharedCrimeFactions
	Outfit JailOutfit
	bool Arrests
	bool AttacksOnSight
	int MurderValue
	int AssaultValue
	int TrespassValue
	int PickpocketValue
	int EscapeValue
	float StealMult
	FormList MerchantTradeList
	ObjectReference MerchantContainer
	int MerchantStartHour
	int MerchantEndHour
	int MerchantRadius
	bool BuysStolenItems
	bool BuysNonStolenItems
	bool TradesEverything
EndStruct

Struct Relation
	Faction Object
	int Modifier
	int CombatReaction
EndStruct

Data Function GetData(Faction akFaction) Global Native
Function SetData(Faction akFaction, Data akData) Global Native

Relation Function CreateRelation(Faction akFaction, int aiModifier = 0, int aiCombatReaction = 0) Global
	Relation relation = new Relation
	relation.Object = akFaction
	relation.Modifier = aiModifier
	relation.CombatReaction = aiCombatReaction
	return relation
EndFunction


bool Function GetIsHiddenFromPC(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x1)
EndFunction
Function SetIsHiddenFromPC(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x1, abValue)
EndFunction

bool Function GetIsSpecialInCombat(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x2)
EndFunction
Function SetIsSpecialInCombat(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x2, abValue)
EndFunction

bool Function GetIsPlayerExpelled(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x4)
EndFunction
Function SetIsPlayerExpelled(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x4, abValue)
EndFunction

bool Function GetIsPlayerEnemy(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x8)
EndFunction
Function SetIsPlayerEnemy(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x8, abValue)
EndFunction

bool Function GetTracksCrimes(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x40)
EndFunction
Function SetTracksCrimes(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x40, abValue)
EndFunction

bool Function GetIgnoresMurder(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x80)
EndFunction
Function SetIgnoresMurder(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x80, abValue)
EndFunction

bool Function GetIgnoresAssault(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x100)
EndFunction
Function SetIgnoresAssault(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x100, abValue)
EndFunction

bool Function GetIgnoresStealing(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x200)
EndFunction
Function SetIgnoresStealing(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x200, abValue)
EndFunction

bool Function GetIgnoresTrespass(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x400)
EndFunction
Function SetIgnoresTrespass(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x400, abValue)
EndFunction

bool Function GetDoesNotReportMemberCrimes(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x800)
EndFunction
Function SetDoesNotReportMemberCrimes(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x800, abValue)
EndFunction

bool Function GetUsesDefaultCrimeValue(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x1000)
EndFunction
Function SetUsesDefaultCrimeValue(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x1000, abValue)
EndFunction

bool Function GetIgnoresPickpocketing(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x2000)
EndFunction
Function SetIgnoresPickpocketing(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x2000, abValue)
EndFunction

bool Function GetIsMerchant(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x4000)
EndFunction
Function SetIsMerchant(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x4000, abValue)
EndFunction

bool Function GetCanBeOwner(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x8000)
EndFunction
Function SetCanBeOwner(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x8000, abValue)
EndFunction
