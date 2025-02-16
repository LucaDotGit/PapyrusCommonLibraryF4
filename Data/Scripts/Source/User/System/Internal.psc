Scriptname System:Internal Const Hidden Native

;/
	Provides internal non-delayed utility functions.
/;

string Function GetName() Global Native
Versions:Version Function GetVersion() Global Native
string Function GetVersionString() Global Native

Function LogWarning(string asMessage) Global Native
Function LogError(string asMessage) Global Native
