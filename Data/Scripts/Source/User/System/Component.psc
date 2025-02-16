Scriptname System:Component Const Hidden Native

;/
	Provides common functions for components.
/;

Struct Data
	Sound CraftSound
	MiscObject ScrapItem
	GlobalVariable ScrapScalar
EndStruct

Data Function GetData(Component akComponent) Global Native
Function SetData(Component akComponent, Data akData) Global Native
