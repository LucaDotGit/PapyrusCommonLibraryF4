Scriptname System:Flora Const Hidden Native

;/
	Provides common functions for floras.
/;

Struct Data
	Form HarvestItem
	Sound HarvestSound
	int SpringHarvestChance
	int SummerHarvestChance
	int FallHarvestChance
	int WinterHarvestChance
EndStruct

Data Function GetData(Flora akFlora) Global Native
Function SetData(Flora akFlora, Data akData) Global Native
