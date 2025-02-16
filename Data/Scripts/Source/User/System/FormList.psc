Scriptname System:FormList Const Hidden Native

;/
	Provides common functions for FormLists.

	Notes:
	- The script forms are save-baked while the editor forms are not.
/;

Struct Data
	Form[] EditorForms
	Form[] ScriptForms
EndStruct

Data Function GetData(FormList akFormList) Global Native
Function SetData(FormList akFormList, Data akData) Global Native
