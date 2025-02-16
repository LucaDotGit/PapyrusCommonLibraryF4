Scriptname System:MovementType Const Hidden Native

;/
	Provides common functions for movement types.
/;

Struct Data
	string Name
	Entry Left
	Entry Right
	Entry Forward
	Entry Backward
	Entry Pitch
	Entry Roll
	Entry Yaw
	float FloatHeight
	float FlightAngleGain
EndStruct

Struct Entry
	float Standing
	float Walking
	float Running
	float Sprinting
EndStruct

Data Function GetData(MovementType akMovementType) Global Native
Function SetData(MovementType akMovementType, Data akData) Global Native

Entry Function CreateEntry(float afStanding = 0.0, float afWalking = 0.0, float afRunning = 0.0, float afSprinting = 0.0) Global
	Entry entry = new Entry
	entry.Standing = afStanding
	entry.Walking = afWalking
	entry.Running = afRunning
	entry.Sprinting = afSprinting
	return entry
EndFunction
