Scriptname System:Pairs Const Hidden

;/
	Provides shared data for pairs.
/;

Struct Pair
	string Name
	Var Value
EndStruct

Struct StringPair
	string Name
	string Value
EndStruct

Pair Function CreatePair(string asName, Var akValue) Global
	Pair pair = new Pair
	pair.Name = asName
	pair.Value = akValue
	return pair
EndFunction

StringPair Function CreateStringPair(string asName, string asValue) Global
	StringPair pair = new StringPair
	pair.Name = asName
	pair.Value = asValue
	return pair
EndFunction
