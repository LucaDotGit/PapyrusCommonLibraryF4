Scriptname System:Book Const Hidden Native

;/
	Provides common functions for books.
/;

Struct Data
	int Flags
	int TextOffsetX
	int TextOffsetY
	Static InventoryModel
EndStruct

Data Function GetData(Book akBook) Global Native
Function SetData(Book akBook, Data akData) Global Native


bool Function GetCannotBeTaken(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x2)
EndFunction
Function SetCannotBeTaken(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x2, abValue)
EndFunction

bool Function GetHasBeenRead(Data akData) Global
	return System:Operator.HasFlag(akData.Flags, 0x8)
EndFunction
Function SetHasBeenRead(Data akData, bool abValue) Global
	akData.Flags = System:Operator.SetFlag(akData.Flags, 0x8, abValue)
EndFunction
