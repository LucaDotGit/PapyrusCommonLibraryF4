Scriptname System:Console Const Hidden Native

;/
	Provides common functions to interact with the console menu.
/;

ObjectReference[] Function GetSelectableRefs() Global Native

ObjectReference Function GetSelectedRef() Global Native
Function SetSelectedRef(ObjectReference akRef) Global Native
Function ClearSelectedRef() Global
	SetSelectedRef(none)
EndFunction

string Function GetHistory() Global Native
Function SetHistory(string asHistory) Global Native
Function Clear() Global
	SetHistory("")
EndFunction

Function Write(string asText) Global Native
Function WriteLine(string asText) Global Native

bool Function ExecuteCommand(string asCommand, ObjectReference akTargetRef = none, bool abSilent = true) Global Native
