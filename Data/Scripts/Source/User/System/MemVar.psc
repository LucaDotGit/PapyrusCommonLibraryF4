Scriptname System:MemVar Const Hidden Native

;/
	Provides non-delayed functions to store and retrieve temporary global variables.

	Notes:
	- The variables persist only for the current game session.
/;

string[] Function GetNamespaces() Global Native
string[] Function GetKeys(string asNamespace) Global Native
Var[] Function GetValues(string asNamespace) Global Native

Pairs:Pair[] Function GetPairs(string asNamespace) Global Native
bool Function SetPairs(string asNamespace, Pairs:Pair[] akPairs) Global Native

bool Function ContainsNamespace(string asNamespace) Global Native
bool Function ContainsKey(string asNamespace, string asKey) Global Native

Var Function GetValue(string asNamespace, string asKey) Global Native
Var Function GetValueOrDefault(string asNamespace, string asKey, Var akDefault) Global Native
bool Function SetValue(string asNamespace, string asKey, Var akValue) Global Native

Var[] Function GetArray(string asNamespace, string asKey) Global Native
bool Function SetArray(string asNamespace, string asKey, Var[] akValues) Global Native

bool Function Remove(string asNamespace, string asKey) Global Native
bool Function Clear(string asNamespace) Global Native
