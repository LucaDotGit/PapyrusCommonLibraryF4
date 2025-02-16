Scriptname System:Form Const Hidden Native

;/
	Provides common functions for forms, the base type of all game objects.

	Notes:
	- Any created or copied form is not stored in the save file and persists only for the current game session.
	- You can get type IDs by type strings.
	  Example: System:Form.GetTypeByTypeString("ARMO") -> 29
	- The `Var[]` filters support form types (int), mod names (string), references, base objects, keywords, factions, races and form lists (recursive).
	- For a list of all form types, see:
	  https://github.com/alandtse/CommonLibF4/blob/814cbdb9ce9effb337d07c2ae6d4c13b5e7aa2aa/CommonLibF4/include/RE/Bethesda/TESForms.h#L196.
	- For a list of all base object form flags, see:
	  https://github.com/powerof3/CommonLibSSE/blob/e3626d228d60b92a82410accd475bffdd7245653/include/RE/T/TESForm.h#L51.
	- For a list of all reference form flags, see:
	  https://github.com/powerof3/CommonLibSSE/blob/e3626d228d60b92a82410accd475bffdd7245653/include/RE/T/TESObjectREFR.h#L146.
/;

Form Function Create(int aiType) Global Native
Form Function Copy(Form akForm) Global Native

bool Function HasFlag(Form akForm, int auFlag) Global Native
int Function GetFlags(Form akForm) Global Native
Function SetFlags(Form akForm, int auFlags) Global Native
Function SetFlag(Form akForm, int auFlag, bool abSet) Global Native


;/
	Start of non-delayed functions.
/;

; This function is equivalent to ObjectReference.IsCreated,
; but now it works for all form types and it is much faster.
bool Function IsCreated(Form akForm) Global Native

int Function GetType(Form akForm) Global Native
int Function GetTypeByTypeString(string asType) Global Native
string Function GetTypeString(Form akForm) Global Native
string Function GetTypeStringByType(int aiType) Global Native
string Function GetScriptName(Form akForm) Global Native

bool Function IsInMod(Form akForm, string asModName) Global Native
string Function GetModName(Form akForm, bool abLastModified = false) Global Native

;/
	EditorID Functions

	Notes:
	- Exterior cells are not supported.
/;

int Function GetLocalFormID(Form akForm) Global Native
string Function GetEditorID(Form akForm) Global Native
bool Function SetEditorID(Form akForm, string asEditorID) Global Native
Form Function GetByEditorID(string asEditorID) Global Native

Form[] Function GetAllByType(int aiType, string asModName = "") Global Native
Form[] Function FindAllByType(Form[] akForms, int aiType) Global Native
Form[] Function FindAllByModName(Form[] akForms, string asModName) Global Native

;/
	End of non-delayed functions.
/;


Form[] Function FindAllByFilter(Form[] akForms, Var[] akIncludedObjects = none, Var[] akExcludedObjects = none) Global Native
Form[] Function FindAllByFlag(Form[] akForms, int aiFlag, bool abIsSet) Global Native

bool Function ContainsKeywordString(Form akForm, string asEditorID) Global Native
bool Function HasKeywordString(Form akForm, string asEditorID) Global Native
Keyword[] Function GetKeywords(Form akForm) Global Native

; For: Too many to list
string Function GetName(Form akForm) Global Native
bool Function SetName(Form akForm, string asName) Global Native

; For:	ActorValue, Ammo, Armor, Book, Class, CollisionLayer, ConstructibleObject, Message, ObjectMod,
; 		Perk, Potion, Race, Shout, Spell and Weapon
string Function GetDescription(Form akForm) Global Native

; For:	Ammo, Book, Component, Holotape, Ingredient, Light, MiscObject and Scroll
int Function GetValue(Form akForm) Global Native
bool Function SetValue(Form akForm, int aiValue) Global Native

; For:	Ammo, Book, Container, Holotape, Ingredient, Light, MiscObject, Potion and Scroll
float Function GetWeight(Form akForm) Global Native
bool Function SetWeight(Form akForm, float afWeight) Global Native

Struct PropertyEntry
	ActorValue Object
	float Value
EndStruct

; For:	Activator, ActorBase, Class, Container, Light, Race, Static
PropertyEntry[] Function GetProperties(Form akForm) Global Native
bool Function SetProperties(Form akForm, PropertyEntry[] akProperties) Global Native

; For:	Armor, Ingredient, Light, Potion, Shout, Spell and Weapon
EquipSlot Function GetEquipType(Form akForm) Global Native
bool Function SetEquipType(Form akForm, EquipSlot aeEquipType) Global Native

Struct PickupPutdownSounds
	Sound PickupSound
	Sound PutdownSound
EndStruct

; For:	Ammo, Armor, Book, ConstructibleObject, Holotape, Ingredient, MiscObject, Potion, Scroll and Weapon
PickupPutdownSounds Function GetPickupPutdownSounds(Form akForm) Global Native
bool Function SetPickupPutdownSounds(Form akForm, PickupPutdownSounds akSounds) Global Native

; For:	Component and Potion
Sound Function GetCraftSound(Form akForm) Global Native
bool Function SetCraftSound(Form akForm, Sound akSound) Global Native

; For:	Armor, ArmorAddon (Form) and ActorBase
Race Function GetRace(Form akForm) Global Native
bool Function SetRace(Form akForm, Race akRace) Global Native

; For:	Activator, Container, Door and ActorBase
Terminal Function GetTerminal(Form akForm) Global Native
bool Function SetTerminal(Form akForm, Terminal akTerminal) Global Native

Struct MaterialSwapModel
	MatSwap Object
	float ColorIndex
EndStruct

; For:	Activator, AddonNode (Form), Ammo, AnimObject (Form), ArtObject, Book, Container, Door, HeadPart, Ingredient,
; 		LeveledCharacter (Form), Light, MiscObject, ObjectMod, Potion, Scroll, Static, StaticCollection, Tree and Weapon
MaterialSwapModel Function GetMaterialSwapModel(Form akForm) Global Native
bool Function SetMaterialSwapModel(Form akForm, MaterialSwapModel akModel) Global Native
