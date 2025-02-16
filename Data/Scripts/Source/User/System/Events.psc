Scriptname System:Events Const Hidden Native

;/
	Provides an interface for receiving game-related events that persist for the entire game session.

	Notes:
	- Each event requires a receiver to specify whether the callback function is local or global.
	  See the script "System:ScriptReceivers" on how to create a receiver.
	- The `Var[]` filters support form types (int), mod names (string), references, base objects, keywords, factions, races and form lists (recursive).
	- For a list of all form types, see: https://github.com/alandtse/CommonLibF4/blob/814cbdb9ce9effb337d07c2ae6d4c13b5e7aa2aa/CommonLibF4/include/RE/Bethesda/TESForms.h#L196.

	Included Events:
	- OnUserEvent
	- OnDeleteGame
	- OnPostLoadGame
	- OnPostSaveGame
	- OnPreSaveGame
	- OnActorDeath
	- OnCombatStateChange
	- OnFurnitureEnterExit
	- OnItemEquipUnequip
	- OnLifeStateChange
	- OnLimbCripple
	- OnLocationEnterExit
	- OnActorValueChange
	- OnAnimationGraphEvent
	- OnContainerChange
	- OnDestructionStageChange
	- OnMagicEffectApply
	- OnObjectActivate
	- OnObjectGrabRelease
	- OnObjectHit
	- OnObjectLoadUnload
	- OnObjectOpenClose
	- OnTriggerEnterLeave
	- OnCrosshairRefChange
	- OnHUDColorUpdate
	- OnMenuModeEnterExit
	- OnMenuOpenClose
	- OnTutorialTrigger
	- OnButtonUpDown
	- OnCellAttachDetach
	- OnCellEnterExit
	- OnCellLoad
	- OnLocationLoad
	- OnLockPick (Not for Next-Gen)
	- OnPerkPointIncrease
	- OnTerminalHack (Not for Next-Gen)
	- OnPipBoyLightChange
	- OnPowerArmorLightChange (Not for Next-Gen)

	Example:

	Function OnGameLoad() Global
		Var[] includedValues = new Var[1]
		includedValues[0] = System:Form.GetTypeByTypeString("NPC_")

		System:Events.RegisterForCrosshairRefChange( \
			System:ScriptReceivers.CreateGlobalReceiver("MyNamespace:MyScript", "OnCrosshairRefChange"), \
			akIncludedObjects = includedValues)
	EndFunction

	Function OnCrosshairRefChange(System:Events:CrosshairRefChangeArgs akEvent) Global
		; Do something with the event data.
	EndFunction
/;

Import System:ScriptReceivers


bool Function IsRegisteredForAny(ScriptReceiver akReceiver) Global Native
bool Function UnregisterForAny(ScriptReceiver akReceiver) Global Native
bool Function UnregisterForAll(string asScriptName) Global Native


;/
	Function Signature:

	Function OnUserEvent(string asEventName, args...)
	EndFunction
/;

bool Function IsRegisteredForUserEvent(ScriptReceiver akReceiver, string asEventName = "") Global Native
bool Function RegisterForUserEvent(ScriptReceiver akReceiver, string asEventName) Global Native
bool Function UnregisterForUserEvent(ScriptReceiver akReceiver) Global Native
Function SendUserEvent(string asEventName, Var[] akArgs = none) Global Native


;/
	Function Signature:

	Function OnDeleteGame(System:Events:DeleteGameArgs akEvent)
	EndFunction
/;

Struct DeleteGameArgs
	string SaveName
EndStruct

bool Function IsRegisteredForDeleteGame(ScriptReceiver akReceiver) Global Native
bool Function RegisterForDeleteGame(ScriptReceiver akReceiver) Global Native
bool Function UnregisterForDeleteGame(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnPostLoadGame(System:Events:PostLoadGameArgs akEvent)
	EndFunction
/;

Struct PostLoadGameArgs
	bool IsSucceeded
EndStruct

bool Function IsRegisteredForPostLoadGame(ScriptReceiver akReceiver) Global Native
bool Function RegisterForPostLoadGame(ScriptReceiver akReceiver) Global Native
bool Function UnregisterForPostLoadGame(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnPostSaveGame(System:Events:PostSaveGameArgs akEvent)
	EndFunction
/;

Struct PostSaveGameArgs
	string SaveName
EndStruct

bool Function IsRegisteredForPostSaveGame(ScriptReceiver akReceiver) Global Native
bool Function RegisterForPostSaveGame(ScriptReceiver akReceiver) Global Native
bool Function UnregisterForPostSaveGame(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnPreSaveGame(System:Events:PreSaveGameArgs akEvent)
	EndFunction
/;

Struct PreSaveGameArgs
	string SaveName
EndStruct

bool Function IsRegisteredForPreSaveGame(ScriptReceiver akReceiver) Global Native
bool Function RegisterForPreSaveGame(ScriptReceiver akReceiver) Global Native
bool Function UnregisterForPreSaveGame(ScriptReceiver akReceiver) Global Native


;/
	Notes:
	- The "IsDead" field is set to true if the target died and false if they are dying.

	Function Signature:

	Function OnActorDeath(System:Events:ActorDeathArgs akEvent)
	EndFunction
/;

Struct ActorDeathArgs
	Actor SourceActor
	Actor TargetActor
	ActorBase Source
	ActorBase Target
	bool IsDead
EndStruct

bool Function IsRegisteredForActorDeath(ScriptReceiver akReceiver) Global Native
bool Function RegisterForActorDeath(ScriptReceiver akReceiver, \
									Var[] akIncludedSources = none, Var[] akExcludedSources = none, \
									Var[] akIncludedTargets = none, Var[] akExcludedTargets = none) Global Native
bool Function UnregisterForActorDeath(ScriptReceiver akReceiver) Global Native


;/
	Combat States:
	00	Not In Combat
	01	In Combat
	02	Searching

	Function Signature:

	Function OnCombatStateChange(System:Events:CombatStateChangeArgs akEvent)
	EndFunction
/;

Struct CombatStateChangeArgs
	Actor SourceActor
	Actor TargetActor
	ActorBase Source
	ActorBase Target
	int SetState
EndStruct

bool Function IsRegisteredForCombatStateChange(ScriptReceiver akReceiver) Global Native
bool Function RegisterForCombatStateChange(ScriptReceiver akReceiver, \
											Var[] akIncludedSources = none, Var[] akExcludedSources = none, \
											Var[] akIncludedTargets = none, Var[] akExcludedTargets = none, \
											int[] akIncludedStates = none, int[] akExcludedStates = none) Global Native
bool Function UnregisterForCombatStateChange(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnFurnitureEnterExit(System:Events:FurnitureEnterExitArgs akEvent)
	EndFunction
/;

Struct FurnitureEnterExitArgs
	Actor SourceActor
	ObjectReference TargetRef
	ActorBase Source
	Furniture Target
	bool IsEntered
EndStruct

bool Function IsRegisteredForFurnitureEnterExit(ScriptReceiver akReceiver) Global Native
bool Function RegisterForFurnitureEnterExit(ScriptReceiver akReceiver, \
											Var[] akIncludedSources = none, Var[] akExcludedSources = none, \
											Var[] akIncludedTargets = none, Var[] akExcludedTargets = none) Global Native
bool Function UnregisterForFurnitureEnterExit(ScriptReceiver akReceiver) Global Native


;/
	Notes:
	- The "TargetRef" field may be none for non-persistent objects. Use "Target" instead.

	Function Signature:

	Function OnItemEquipUnequip(System:Events:ItemEquipUnequipArgs akEvent)
	EndFunction
/;

Struct ItemEquipUnequipArgs
	Actor SourceActor
	ObjectReference TargetRef
	ActorBase Source
	Form Target
	bool IsEquipped
EndStruct

bool Function IsRegisteredForItemEquipUnequip(ScriptReceiver akReceiver) Global Native
bool Function RegisterForItemEquipUnequip(ScriptReceiver akReceiver, \
											Var[] akIncludedSources = none, Var[] akExcludedSources = none, \
											Var[] akIncludedTargets = none, Var[] akExcludedTargets = none) Global Native
bool Function UnregisterForItemEquipUnequip(ScriptReceiver akReceiver) Global Native


;/
	Actor Life States:
	00	Alive
	01	Dying
	02	Dead
	03	Unconscious
	04	Reanimate
	05	Recycle
	06	Restrained
	07	Essential Down
	08	Bleedout

	Function Signature:

	Function OnLifeStateChange(System:Events:LifeStateChangeArgs akEvent)
	EndFunction
/;

Struct LifeStateChangeArgs
	Actor SourceActor
	ActorBase Source
	int OldState
	int NewState
EndStruct

bool Function IsRegisteredForLifeStateChange(ScriptReceiver akReceiver) Global Native
bool Function RegisterForLifeStateChange(ScriptReceiver akReceiver, \
												Var[] akIncludedSources = none, Var[] akExcludedSources = none, \
												int[] akIncludedOldStates = none, int[] akExcludedOldStates = none, \
												int[] akIncludedNewStates = none, int[] akExcludedNewStates = none) Global Native
bool Function UnregisterForLifeStateChange(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnLimbCripple(System:Events:LimbCrippleArgs akEvent)
	EndFunction
/;

Struct LimbCrippleArgs
	Actor SourceActor
	ActorBase Source
	ActorValue Limb
	bool IsCrippled
EndStruct

bool Function IsRegisteredForLimbCripple(ScriptReceiver akReceiver) Global Native
bool Function RegisterForLimbCripple(ScriptReceiver akReceiver, \
											Var[] akIncludedSources = none, Var[] akExcludedSources = none, \
											Var[] akIncludedLimbs = none, Var[] akExcludedLimbs = none) Global Native
bool Function UnregisterForLimbCripple(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnLocationEnterExit(System:Events:LocationEnterExitArgs akEvent)
	EndFunction
/;

Struct LocationEnterExitArgs
	Actor SourceActor
	ActorBase Source
	Location OldLocation
	Location NewLocation
EndStruct

bool Function IsRegisteredForLocationEnterExit(ScriptReceiver akReceiver) Global Native
bool Function RegisterForLocationEnterExit(ScriptReceiver akReceiver, \
												Var[] akIncludedSources = none, Var[] akExcludedSources = none, \
												Var[] akIncludedOldLocations = none, Var[] akExcludedOldLocations = none, \
												Var[] akIncludedNewLocations = none, Var[] akExcludedNewLocations = none) Global Native
bool Function UnregisterForLocationEnterExit(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnActorValueChange(System:Events:ActorValueChangeArgs akEvent)
	EndFunction
/;

Struct ActorValueChangeArgs
	ObjectReference ObjectRef
	Form Object
	ActorValue ValueHolder
	float OldValue
	float NewValue
EndStruct

bool Function IsRegisteredForActorValueChange(ScriptReceiver akReceiver) Global Native
bool Function RegisterForActorValueChange(ScriptReceiver akReceiver, \
											Var[] akIncludedObjects = none, Var[] akExcludedObjects = none, \
											Var[] akIncludedActorValues = none, Var[] akExcludedActorValues = none) Global Native
bool Function UnregisterForActorValueChange(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnAnimationGraphEvent(System:Events:AnimationGraphEventArgs akEvent)
	EndFunction
/;

Struct AnimationGraphEventArgs
	ObjectReference ObjectRef
	Form Object
	string EventName
	string Payload
EndStruct

bool Function IsRegisteredForAnimationGraphEvent(ScriptReceiver akReceiver) Global Native
bool Function RegisterForAnimationGraphEvent(ScriptReceiver akReceiver, \
											Var[] akIncludedObjects = none, Var[] akExcludedObjects = none, \
											string[] akIncludedEventNames = none, string[] akExcludedEventNames = none, \
											string[] akIncludedPayloads = none, string[] akExcludedPayloads = none) Global Native
bool Function UnregisterForAnimationGraphEvent(ScriptReceiver akReceiver) Global Native


;/
	Notes:
	- The "SourceRef" field may be none when the item came from the world.

	Function Signature:

	Function OnContainerChange(System:Events:ContainerChangeArgs akEvent)
	EndFunction
/;

Struct ContainerChangeArgs
	ObjectReference SourceRef
	ObjectReference TargetRef
	ObjectReference ItemRef
	Form Source
	Form Target
	Form Item
	int ItemCount
EndStruct

bool Function IsRegisteredForContainerChange(ScriptReceiver akReceiver) Global Native
bool Function RegisterForContainerChange(ScriptReceiver akReceiver, \
											Var[] akIncludedSources = none, Var[] akExcludedSources = none, \
											Var[] akIncludedTargets = none, Var[] akExcludedTargets = none, \
											Var[] akIncludedItems = none, Var[] akExcludedItems = none) Global Native
bool Function UnregisterForContainerChange(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnDestructionStageChange(System:Events:DestructionStageChangeArgs akEvent)
	EndFunction
/;

Struct DestructionStageChangeArgs
	ObjectReference ObjectRef
	Form Object
	int OldStage
	int NewStage
EndStruct

bool Function IsRegisteredForDestructionStageChange(ScriptReceiver akReceiver) Global Native
bool Function RegisterForDestructionStageChange(ScriptReceiver akReceiver, \
														Var[] akIncludedObjects = none, Var[] akExcludedObjects = none, \
														int[] akIncludedOldStages = none, int[] akExcludedOldStages = none, \
														int[] akIncludedNewStages = none, int[] akExcludedNewStages = none) Global Native
bool Function UnregisterForDestructionStageChange(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnMagicEffectApply(System:Events:MagicEffectApplyArgs akEvent)
	EndFunction
/;

Struct MagicEffectApplyArgs
	ObjectReference SourceRef
	ObjectReference TargetRef
	Form Source
	Form Target
	MagicEffect Effect
EndStruct

bool Function IsRegisteredForMagicEffectApply(ScriptReceiver akReceiver) Global Native
bool Function RegisterForMagicEffectApply(ScriptReceiver akReceiver, \
											Var[] akIncludedSources = none, Var[] akExcludedSources = none, \
											Var[] akIncludedTargets = none, Var[] akExcludedTargets = none, \
											Var[] akIncludedEffects = none, Var[] akExcludedEffects = none) Global Native
bool Function UnregisterForMagicEffectApply(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnObjectActivate(System:Events:ObjectActivateArgs akEvent)
	EndFunction
/;

Struct ObjectActivateArgs
	ObjectReference SourceRef
	ObjectReference TargetRef
	Form Source
	Form Target
EndStruct

bool Function IsRegisteredForObjectActivate(ScriptReceiver akReceiver) Global Native
bool Function RegisterForObjectActivate(ScriptReceiver akReceiver, \
										Var[] akIncludedSources = none, Var[] akExcludedSources = none, \
										Var[] akIncludedTargets = none, Var[] akExcludedTargets = none) Global Native
bool Function UnregisterForObjectActivate(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnObjectGrabRelease(System:Events:ObjectGrabReleaseArgs akEvent)
	EndFunction
/;

Struct ObjectGrabReleaseArgs
	ObjectReference ObjectRef
	Form Object
	bool IsGrabbed
EndStruct

bool Function IsRegisteredForObjectGrabRelease(ScriptReceiver akReceiver) Global Native
bool Function RegisterForObjectGrabRelease(ScriptReceiver akReceiver, \
											Var[] akIncludedObjects = none, Var[] akExcludedObjects = none) Global Native
bool Function UnregisterForObjectGrabRelease(ScriptReceiver akReceiver) Global Native


;/
	Notes:
	- The "SourceProjectileRef" field may be none when not hitting actors.
	- The "HitData" field may be none when no hit data is available, e.g. when not hitting actors.
	- For a list of all event data flags,
	  see: https://github.com/alandtse/CommonLibF4/blob/814cbdb9ce9effb337d07c2ae6d4c13b5e7aa2aa/CommonLibF4/include/RE/Bethesda/Events.h#L684

	Stagger Magnitudes:
	00	None
	01	Small
	02	Medium
	03	Large
	04	Extra Large

	Function Signature:

	Function OnObjectHit(System:Events:ObjectHitArgs akEvent)
	EndFunction
/;

Struct ObjectHitArgs
	ObjectReference SourceRef
	ObjectReference TargetRef
	Form Source
	Form Target
	Form SourceObject
	ObjectReference SourceProjectileRef
	Projectile SourceProjectile
	string MaterialName
	ObjectHitData HitData
EndStruct

Struct ObjectHitData
	int Flags
	float BaseDamage
	float TotalDamage
	float PhysicalDamage
	float LimbDamage
	float BlockedDamageMult
	float ResistedPhysicalDamage
	float ResistedTypedDamage
	float ReflectedDamage
	float SneakAttackMult
	float CriticalDamageMult
	float BonusHealthDamageMult
	float PushBackMult
	int StaggerMagnitude
EndStruct

bool Function IsRegisteredForObjectHit(ScriptReceiver akReceiver) Global Native
bool Function RegisterForObjectHit(ScriptReceiver akReceiver, \
									Var[] akIncludedSources = none, Var[] akExcludedSources = none, \
									Var[] akIncludedTargets = none, Var[] akExcludedTargets = none, \
									Var[] akIncludedObjects = none, Var[] akExcludedObjects = none, \
									Var[] akIncludedProjectiles = none, Var[] akExcludedProjectiles = none, \
									string[] akIncludedMaterialNames = none, string[] akExcludedMaterialNames = none, \
									int aiIncludedFlags = 0, int aiExcludedFlags = 0) Global Native
bool Function UnregisterForObjectHit(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnObjectLoadUnload(System:Events:ObjectLoadUnloadArgs akEvent)
	EndFunction
/;

Struct ObjectLoadUnloadArgs
	ObjectReference ObjectRef
	Form Object
	bool IsLoaded
EndStruct

bool Function IsRegisteredForObjectLoadUnload(ScriptReceiver akReceiver) Global Native
bool Function RegisterForObjectLoadUnload(ScriptReceiver akReceiver, \
											Var[] akIncludedObjects = none, Var[] akExcludedObjects = none) Global Native
bool Function UnregisterForObjectLoadUnload(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnObjectOpenClose(System:Events:ObjectOpenCloseArgs akEvent)
	EndFunction
/;

Struct ObjectOpenCloseArgs
	ObjectReference SourceRef
	ObjectReference TargetRef
	Form Source
	Form Target
	bool IsOpened
EndStruct

bool Function IsRegisteredForObjectOpenClose(ScriptReceiver akReceiver) Global Native
bool Function RegisterForObjectOpenClose(ScriptReceiver akReceiver, \
										Var[] akIncludedSources = none, Var[] akExcludedSources = none, \
										Var[] akIncludedTargets = none, Var[] akExcludedTargets = none) Global Native
bool Function UnregisterForObjectOpenClose(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnTriggerEnterLeave(System:Events:TriggerEnterLeaveArgs akEvent)
	EndFunction
/;

Struct TriggerEnterLeaveArgs
	ObjectReference SourceRef
	ObjectReference TargetRef
	Form Source
	Activator Target
	bool IsEntered
EndStruct

bool Function IsRegisteredForTriggerEnterLeave(ScriptReceiver akReceiver) Global Native
bool Function RegisterForTriggerEnterLeave(ScriptReceiver akReceiver, \
											Var[] akIncludedSources = none, Var[] akExcludedSources = none, \
											Var[] akIncludedTargets = none, Var[] akExcludedTargets = none) Global Native
bool Function UnregisterForTriggerEnterLeave(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnCrosshairRefChange(System:Events:CrosshairRefChangeArgs akEvent)
	EndFunction
/;

Struct CrosshairRefChangeArgs
	ObjectReference ObjectRef
	Form Object
	bool IsTargeted
EndStruct

bool Function IsRegisteredForCrosshairRefChange(ScriptReceiver akReceiver) Global Native
bool Function RegisterForCrosshairRefChange(ScriptReceiver akReceiver, \
											Var[] akIncludedObjects = none, Var[] akExcludedObjects = none) Global Native
bool Function UnregisterForCrosshairRefChange(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnHUDColorUpdate(System:Events:HUDColorUpdateArgs akEvent)
	EndFunction
/;

Struct HUDColorUpdateArgs
	Colors:Color Color
EndStruct

bool Function IsRegisteredForHUDColorUpdate(ScriptReceiver akReceiver) Global Native
bool Function RegisterForHUDColorUpdate(ScriptReceiver akReceiver) Global Native
bool Function UnregisterForHUDColorUpdate(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnMenuModeEnterExit(System:Events:MenuModeEnterExitArgs akEvent)
	EndFunction
/;

Struct MenuModeEnterExitArgs
	string MenuName
	bool IsEntered
EndStruct

bool Function IsRegisteredForMenuModeEnterExit(ScriptReceiver akReceiver) Global Native
bool Function RegisterForMenuModeEnterExit(ScriptReceiver akReceiver, \
										string[] akIncludedMenuNames = none, string[] akExcludedMenuNames = none) Global Native
bool Function UnregisterForMenuModeEnterExit(ScriptReceiver akReceiver) Global Native


;/
	Notes:
	- For a list of all menu names, see: https://falloutck.uesp.net/wiki/Menu.

	Function Signature:

	Function OnMenuOpenClose(System:Events:MenuOpenCloseArgs akEvent)
	EndFunction
/;

Struct MenuOpenCloseArgs
	string MenuName
	bool IsOpened
EndStruct

bool Function IsRegisteredForMenuOpenClose(ScriptReceiver akReceiver) Global Native
bool Function RegisterForMenuOpenClose(ScriptReceiver akReceiver, \
										string[] akIncludedMenuNames = none, string[] akExcludedMenuNames = none) Global Native
bool Function UnregisterForMenuOpenClose(ScriptReceiver akReceiver) Global Native


;/
	Notes:
	- For a list of all tutorial events, see: https://falloutck.uesp.net/wiki/OnTutorialEvent_-_ScriptObject.

	Function Signature:

	Function OnTutorialTrigger(System:Events:TutorialTriggerArgs akEvent)
	EndFunction
/;

Struct TutorialTriggerArgs
	string EventName
	Message SentMessage
EndStruct

bool Function IsRegisteredForTutorialTrigger(ScriptReceiver akReceiver) Global Native
bool Function RegisterForTutorialTrigger(ScriptReceiver akReceiver, \
											string[] akIncludedEventNames = none, string[] akExcludedEventNames = none) Global Native
bool Function UnregisterForTutorialTrigger(ScriptReceiver akReceiver) Global Native


;/
	Notes:
	- The event fires in both game and menu mode.
	- For a list of most button codes, see: https://falloutck.uesp.net/wiki/DirectX_Scan_Codes.
	- For a list of most control names, see: https://falloutck.uesp.net/wiki/GetMappedKey_-_Input.

	Device Types:
	00	Keyboard
	01	Mouse
	02	Gamepad

	Mouse Button Codes:
	00	Left Click
	01	Right Click
	02	Middle Click
	03	Mouse Click 3
	04	Mouse Click 4

	Controller Button Codes:
	266	D-Pad Up
	267	D-Pad Down
	268	D-Pad Left
	269	D-Pad Right
	270	Start
	271	Back
	272	Left Thumb
	273	Right Thumb
	274	Left Shoulder
	275	Right Shoulder
	276	A
	277	B
	278	X
	279	Y
	280	Left Trigger
	281	Right Trigger

	Function Signature:

	Function OnButtonUpDown(System:Events:ButtonUpDownArgs akEvent)
	EndFunction
/;

Struct ButtonUpDownArgs
	int DeviceType
	int ButtonCode
	string ControlName
	float AnalogValue
	float HeldSeconds
EndStruct

bool Function IsRegisteredForButtonUpDown(ScriptReceiver akReceiver) Global Native
bool Function RegisterForButtonUpDown(ScriptReceiver akReceiver, \
										int[] akIncludedDeviceTypes = none, int[] akExcludedDeviceTypes = none, \
										int[] akIncludedButtonCodes = none, int[] akExcludedButtonCodes = none, \
										string[] akIncludedControlNames = none, string[] akExcludedControlNames = none) Global Native
bool Function UnregisterForButtonUpDown(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnCellAttachDetach(System:Events:CellAttachDetachArgs akEvent)
	EndFunction
/;

Struct CellAttachDetachArgs
	Cell Object
	bool IsAttached
	bool IsPreProcess
EndStruct

bool Function IsRegisteredForCellAttachDetach(ScriptReceiver akReceiver) Global Native
bool Function RegisterForCellAttachDetach(ScriptReceiver akReceiver, \
											Var[] akIncludedObjects = none, Var[] akExcludedObjects = none) Global Native
bool Function UnregisterForCellAttachDetach(ScriptReceiver akReceiver) Global Native


;/
	Notes:
	- This event will only fire for the player.

	Function Signature:

	Function OnCellEnterExit(System:Events:CellEnterExitArgs akEvent)
	EndFunction
/;

Struct CellEnterExitArgs
	Actor SourceActor
	Cell Object
	bool IsEntered
EndStruct

bool Function IsRegisteredForCellEnterExit(ScriptReceiver akReceiver) Global Native
bool Function RegisterForCellEnterExit(ScriptReceiver akReceiver, \
										Var[] akIncludedObjects = none, Var[] akExcludedObjects = none) Global Native
bool Function UnregisterForCellEnterExit(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnCellLoad(System:Events:CellLoadArgs akEvent)
	EndFunction
/;

Struct CellLoadArgs
	Cell Object
EndStruct

bool Function IsRegisteredForCellLoad(ScriptReceiver akReceiver) Global Native
bool Function RegisterForCellLoad(ScriptReceiver akReceiver, \
									Var[] akIncludedObjects = none, Var[] akExcludedObjects = none) Global Native
bool Function UnregisterForCellLoad(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnLocationLoad(System:Events:LocationLoadArgs akEvent)
	EndFunction
/;

Struct LocationLoadArgs
	Location Object
EndStruct

bool Function IsRegisteredForLocationLoad(ScriptReceiver akReceiver) Global Native
bool Function RegisterForLocationLoad(ScriptReceiver akReceiver, \
										Var[] akIncludedObjects = none, Var[] akExcludedObjects = none) Global Native
bool Function UnregisterForLocationLoad(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnLockPick(System:Events:LockPickArgs akEvent)
	EndFunction
/;

Struct LockPickArgs
	ObjectReference ObjectRef
	Form Object
	int LockLevel
EndStruct

bool Function IsRegisteredForLockPick(ScriptReceiver akReceiver) Global Native
bool Function RegisterForLockPick(ScriptReceiver akReceiver, \
									Var[] akIncludedObjects = none, Var[] akExcludedObjects = none) Global Native
bool Function UnregisterForLockPick(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnPerkPointIncrease(System:Events:PerkPointIncreaseArgs akEvent)
	EndFunction
/;

Struct PerkPointIncreaseArgs
	int Amount
EndStruct

bool Function IsRegisteredForPerkPointIncrease(ScriptReceiver akReceiver) Global Native
bool Function RegisterForPerkPointIncrease(ScriptReceiver akReceiver) Global Native
bool Function UnregisterForPerkPointIncrease(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnTerminalHack(System:Events:TerminalHackArgs akEvent)
	EndFunction
/;

Struct TerminalHackArgs
	ObjectReference ObjectRef
	Terminal Object
	int LockLevel
EndStruct

bool Function IsRegisteredForTerminalHack(ScriptReceiver akReceiver) Global Native
bool Function RegisterForTerminalHack(ScriptReceiver akReceiver, \
										Var[] akIncludedObjects = none, Var[] akExcludedObjects = none) Global Native
bool Function UnregisterForTerminalHack(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnPipBoyLightChange(System:Events:PipBoyLightChangeArgs akEvent)
	EndFunction
/;

Struct PipBoyLightChangeArgs
	bool IsOn
EndStruct

bool Function IsRegisteredForPipBoyLightChange(ScriptReceiver akReceiver) Global Native
bool Function RegisterForPipBoyLightChange(ScriptReceiver akReceiver) Global Native
bool Function UnregisterForPipBoyLightChange(ScriptReceiver akReceiver) Global Native


;/
	Function Signature:

	Function OnPowerArmorLightChange(System:Events:PowerArmorLightChangeArgs akEvent)
	EndFunction
/;

Struct PowerArmorLightChangeArgs
	bool IsOn
EndStruct

bool Function IsRegisteredForPowerArmorLightChange(ScriptReceiver akReceiver) Global Native
bool Function RegisterForPowerArmorLightChange(ScriptReceiver akReceiver) Global Native
bool Function UnregisterForPowerArmorLightChange(ScriptReceiver akReceiver) Global Native
