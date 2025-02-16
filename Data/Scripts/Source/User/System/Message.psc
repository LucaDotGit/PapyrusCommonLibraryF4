Scriptname System:Message Const Hidden Native

;/
	Provides common functions for messages.
/;

Struct Data
	int Flags
	Quest OwnerQuest
	int DisplayTime
	string InterfaceFile
	string ShortName
	string[] Buttons
EndStruct

Data Function GetData(Message akMessage) Global Native
Function SetData(Message akMessage, Data akData) Global Native


bool Function GetIsMessageBox(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x1)
EndFunction
Function SetIsMessageBox(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x1, abValue)
EndFunction

bool Function GetHasInitialDelay(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x2)
EndFunction
Function SetHasInitialDelay(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x2, abValue)
EndFunction


; Non-debug version of displaying a message box.
Function MessageBox(string asText) Global
	Var[] args = new Var[1]
	args[0] = asText
	Utility.CallGlobalFunction("Debug", "MessageBox", args)
EndFunction

; Non-debug version of displaying a notification.
Function Notification(string asText) Global
	Var[] args = new Var[1]
	args[0] = asText
	Utility.CallGlobalFunction("Debug", "Notification", args)
EndFunction

;/
	Notes:
	- Supports as many buttons as you want.

	Function Signature:

	Function OnButtonPress(int aiButtonIndex)
	EndFunction
/;
Function MessageBoxEx(ScriptReceivers:ScriptReceiver akReceiver, string asText, string[] akButtons = none) Global Native
