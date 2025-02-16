Scriptname System:Game Const Hidden Native

;/
	Provides common game-related functions.

	Notes:
	- The `Var[]` filters support form types (int), mod names (string), references, base objects, keywords, factions, races and form lists (recursive).
	- For a list of all form types, see:
	  https://github.com/alandtse/CommonLibF4/blob/814cbdb9ce9effb337d07c2ae6d4c13b5e7aa2aa/CommonLibF4/include/RE/Bethesda/TESForms.h#L196.
/;

Versions:Version Function GetVersion() Global Native
bool Function IsOldGen() Global Native
bool Function IsNextGen() Global Native

; Returns true the second time a save is loaded during a game session,
; including the initial load from the main menu.
bool Function IsPostGameStart() Global Native


;/
	Mod Functions

	Notes:
	- These functions are equivalent to the ones from F4SE,
	  but they are much faster.
/;

Struct ModInfo
	int Flags
	int Index
	string Name
EndStruct

bool Function IsModLoaded(string asModName) Global Native
ModInfo Function GetModByName(string asModName) Global Native
ModInfo[] Function GetLoadedMods() Global Native

bool Function IsModMaster(ModInfo akMod) Global
	return System:Operator.HasFlag(akMod.Flags, 0x1)
EndFunction
bool Function IsModLight(ModInfo akMod) Global
	return System:Operator.HasFlag(akMod.Flags, 0x200)
EndFunction


;/
	INI Functions

	Notes:
	- These functions work similar to the ones under the vanilla Utility script,
	  but they are much faster.
	- Some settings were moved to the empty section (""),
	  due to their keys being invalid.
	- Altering some settings may have no apparent effect.
/;

string[] Function GetINISections() Global Native
string[] Function GetINIKeys(string asSection) Global Native

bool Function ContainsINISection(string asSection) Global Native
bool Function ContainsINIKey(string asSection, string asKey) Global Native

bool Function GetINIBool(string asSection, string asKey, bool abDefault = false) Global Native
bool Function SetINIBool(string asSection, string asKey, bool abValue) Global Native

int Function GetINIChar(string asSection, string asKey, int acDefault = 0) Global Native
bool Function SetINIChar(string asSection, string asKey, int acValue) Global Native

int Function GetINIInt(string asSection, string asKey, int aiDefault = 0) Global Native
bool Function SetINIInt(string asSection, string asKey, int aiValue) Global Native

float Function GetINIFloat(string asSection, string asKey, float afDefault = 0.0) Global Native
bool Function SetINIFloat(string asSection, string asKey, float afValue) Global Native

string Function GetINIString(string asSection, string asKey, string asDefault = "") Global Native
bool Function SetINIString(string asSection, string asKey, string asValue) Global Native

Colors:Color Function GetINIColor(string asSection, string asKey) Global Native
bool Function SetINIColor(string asSection, string asKey, Colors:Color akValue) Global Native

bool Function SaveINISetting(string asSection, string asKey) Global Native


ObjectReference Function GetCurrentCrosshairRef() Global Native

;/
	Start of delayed functions.
/;

ObjectReference Function GetCurrentCommandTarget() Global Native
ObjectReference Function GetLastUsedPowerArmor() Global Native

ObjectReference[] Function GetAllMapMarkers() Global Native

; For more info, see: https://geckwiki.com/index.php?title=GetActorsByProcessingLevel.
Actor[] Function GetActorsByProcessLevel(int aiProcessLevel, Var[] akIncludedObjects = none, Var[] akExcludedObjects = none) Global Native

ObjectReference[] Function FindAllRefs( \
	Var[] akIncludedObjects = none, Var[] akExcludedObjects = none) Global Native
ObjectReference[] Function FindAllRefsInRange(Vectors:Vector3 akCenter, float afRadius, \
	Var[] akIncludedObjects = none, Var[] akExcludedObjects = none) Global Native
ObjectReference[] Function FindAllRefsInRangeFromRef(ObjectReference akOriginRef, float afRadius, \
	Var[] akIncludedObjects = none, Var[] akExcludedObjects = none) Global Native

Cell[] Function GetLoadedCells() Global Native
WorldSpace Function GetCurrentWorldSpace() Global Native

Function PlayMenuSound(Sound akSound) Global Native
Function PlayMenuSoundByID(string asEditorID) Global Native

Function PlayPipBoySound(Sound akSound) Global Native
Function PlayPipBoySoundByID(string asEditorID) Global Native

bool Function IsHolotapePlaying(Holotape akHolotape) Global Native
Function PlayHolotape(Holotape akHolotape) Global Native
bool Function PauseHolotape(Holotape akHolotape) Global Native

;/
	Camera States:
	-1	Invalid
	00	First Person
	01	Auto Vanity
	02	VATS
	03	Free
	04	Iron Sights
	05	Transition
	06	Tween
	07	Animated
	08	Third Person
	09	Furniture
	10	Mount
	11	Bleedout
	12	Dialogue
/;

int Function GetCameraState() Global Native
bool Function SetCameraState(int aiState) Global Native

bool Function GetIsTimeFrozen() Global Native
Function SetIsTimeFrozen(bool abValue) Global Native

;/
	Perk Point Functions

	Notes:
	- The values are clamped to unsigned 8-bit integers (0 - 255).
	- On Next-Gen, they do not fire the OnPerkPointIncrease event.
/;

int Function GetPerkPoints() Global Native
Function SetPerkPoints(int aiValue) Global Native
Function ModPerkPoints(int aiAmount) Global Native

;/
	End of delayed functions.
/;
