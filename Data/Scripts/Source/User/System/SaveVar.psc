Scriptname System:SaveVar Const Hidden Native

;/
	Provides non-delayed functions to store and retrieve persistent global variables.

	Notes:
	- The variables persist between saves and are stored in F4SE's co-save file.
	- For each namespace, you need to create a same-named file under "Data/PCL/SaveVars".
	  Example: "Data/PCL/SaveVars/MyNamespace.txt" for namespace "MyNamespace".

	Tip:
	- Instead of using SetArray for every array,
	  use the array to var conversion functions from System:Array,
	  in combination with the SetValue function from this script, to save disk space.
/;

bool Function IsNamespaceValid(string asNamespace) Global Native

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
