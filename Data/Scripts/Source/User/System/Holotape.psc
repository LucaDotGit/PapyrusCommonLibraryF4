Scriptname System:Holotape Const Hidden Native

;/
	Provides common functions for notes.
/;

Struct Data
	int Type
	bool HasBeenRead
	Sound PlayingSound
	Scene PlayingScene
	string PlayingProgram
	Terminal PlayingTerminal
EndStruct

Data Function GetData(Holotape akHolotape) Global Native
Function SetData(Holotape akHolotape, Data akData) Global Native


bool Function IsVoice(Data akData) Global
	return akData.Type == 0
EndFunction
bool Function IsScene(Data akData) Global
	return akData.Type == 1
EndFunction
bool Function IsProgram(Data akData) Global
	return akData.Type == 2
EndFunction
bool Function IsTerminal(Data akData) Global
	return akData.Type == 3
EndFunction

Function SetVoice(Data akData, Sound akVoice) Global
	akData.PlayingScene = none
	akData.PlayingProgram = ""
	akData.PlayingTerminal = none

	akData.Type = 0
	akData.PlayingSound = akVoice
EndFunction

Function SetScene(Data akData, Scene akScene) Global
	akData.PlayingSound = none
	akData.PlayingProgram = ""
	akData.PlayingTerminal = none

	akData.Type = 1
	akData.PlayingScene = akScene
EndFunction

Function SetProgram(Data akData, string asProgram) Global
	akData.PlayingSound = none
	akData.PlayingScene = none
	akData.PlayingTerminal = none

	akData.Type = 2
	akData.PlayingProgram = asProgram
EndFunction

Function SetTerminal(Data akData, Terminal akTerminal) Global
	akData.PlayingSound = none
	akData.PlayingScene = none
	akData.PlayingProgram = ""

	akData.Type = 3
	akData.PlayingTerminal = akTerminal
EndFunction
