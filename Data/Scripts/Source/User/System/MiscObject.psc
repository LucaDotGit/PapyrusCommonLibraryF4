Scriptname System:MiscObject Const Hidden Native

;/
	Provides common functions for misc items.
/;

Struct Data
	Entry[] Components
EndStruct

Struct Entry
	Component Object
	int Count
	int DisplayIndex
EndStruct

Data Function GetData(MiscObject akMiscObject) Global Native
Function SetData(MiscObject akMiscObject, Data akData) Global Native

Entry Function CreateEntry(Component akComponent, int aiCount = 1, int aiDisplayIndex = 0) Global
	Entry entry = new Entry
	entry.Object = akComponent
	entry.Count = aiCount
	entry.DisplayIndex = aiDisplayIndex
	return entry
EndFunction
