Scriptname System:ScriptObject Const Hidden Native

;/
	Provides common non-delayed functions for script objects, the base type of all scripts.
/;

ScriptObject Function Create(string asScriptName, Pairs:Pair[] akProperties = none) Global Native
ScriptObject Function Copy(ScriptObject akObject) Global Native

bool Function Exists(string asScriptName) Global Native
bool Function IsLoaded(string asScriptName) Global Native

bool Function IsInstanceOf(ScriptObject akObject, string asScriptName) Global Native
bool Function IsRegisteredForRemoteEvent(ScriptObject akObject, ScriptObject akSender, string asEventName) Global Native

string Function GetName(ScriptObject akObject) Global Native
string Function GetParentName(ScriptObject akObject) Global Native

Var Function GetVariableValue(ScriptObject akObject, string asName) Global Native
bool Function SetVariableValue(ScriptObject akObject, string asName, Var akValue) Global Native

Var Function GetAutoPropertyValue(ScriptObject akObject, string asName) Global Native
bool Function SetAutoPropertyValue(ScriptObject akObject, string asName, Var akValue) Global Native
