Scriptname System:ScriptReceivers Const Hidden

;/
	Provides shared data for script receivers.
/;

Struct ScriptReceiver
	ScriptObject Object
	string ObjectName
	string FunctionName
EndStruct

ScriptReceiver Function CreateLocalReceiver(ScriptObject akObject, string asFunctionName) Global
	ScriptReceiver receiver = new ScriptReceiver
	receiver.Object = akObject
	receiver.ObjectName = System:ScriptObject.GetName(akObject)
	receiver.FunctionName = asFunctionName
	return receiver
EndFunction

ScriptReceiver Function CreateGlobalReceiver(string asScriptName, string asFunctionName) Global
	ScriptReceiver receiver = new ScriptReceiver
	receiver.ObjectName = asScriptName
	receiver.FunctionName = asFunctionName
	return receiver
EndFunction
