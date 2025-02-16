Scriptname System:Perk Const Hidden Native

;/
	Provides common functions for perks.

	Notes:
	- The entries are sorted by their priority.

	Entry Types:
	00	Quest
	01	Ability
	02	Entry Point

	Function Types:
	00	Invalid
	01	One Value
	02	Two Value
	03	Leveled List
	04	Activate Choice
	05	Spell
	06	Boolean Graph Variable
	07	Text
	08	Actor Value
/;

Struct Data
	bool IsTrait
	bool IsPlayable
	bool IsHidden
	int Level
	int RankCount
	Perk NextPerk
	Sound PlayedSound
	string InterfaceFile
	Entry[] Entries
EndStruct

Struct Entry
	int Rank
	int Priority
EndStruct

Struct QuestEntry
	int Stage
	Quest Object
EndStruct

Struct ValueTwoEntry
	float Value01
	float Value02
EndStruct

Struct ActorValueEntry
	ActorValue Object
	float Value
EndStruct

Data Function GetData(Perk akPerk) Global Native
Function SetData(Perk akPerk, Data akData) Global Native

int Function GetNthEntryType(Perk akPerk, int aiIndex) Global Native
int Function GetNthEntryFunctionType(Perk akPerk, int aiIndex) Global Native

QuestEntry Function GetNthQuestEntry(Perk akPerk, int aiIndex) Global Native
bool Function SetNthQuestEntry(Perk akPerk, int aiIndex, QuestEntry akEntry) Global Native

float Function GetNthEntryValue(Perk akPerk, int aiEntryIndex) Global Native
bool Function SetNthEntryValue(Perk akPerk, int aiEntryIndex, float afValue) Global Native

ValueTwoEntry Function GetNthValueTwoEntry(Perk akPerk, int aiIndex) Global Native
bool Function SetNthValueTwoEntry(Perk akPerk, int aiIndex, ValueTwoEntry akEntry) Global Native

LeveledItem Function GetNthEntryLeveledList(Perk akPerk, int aiIndex) Global Native
bool Function SetNthEntryLeveledList(Perk akPerk, int aiIndex, LeveledItem akLeveledList) Global Native

Spell Function GetNthEntrySpell(Perk akPerk, int aiIndex) Global Native
bool Function SetNthEntrySpell(Perk akPerk, int aiIndex, Spell akSpell) Global Native

string Function GetNthEntryText(Perk akPerk, int aiIndex) Global Native
bool Function SetNthEntryText(Perk akPerk, int aiIndex, string asText) Global Native

ActorValueEntry Function GetNthActorValueEntry(Perk akPerk, int aiIndex) Global Native
bool Function SetNthActorValueEntry(Perk akPerk, int aiIndex, ActorValueEntry akEntry) Global Native
