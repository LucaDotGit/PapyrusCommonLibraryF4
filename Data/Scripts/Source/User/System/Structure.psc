Scriptname System:Structure Const Hidden Native

;/
	Provides common non-delayed functions and type information for structures.
/;

string Function GetName(Var akStruct) Global Native

; For the below functions, the order of the pairs is non-deterministic.
Pairs:Pair[] Function GetInitialVariables(string asStructName) Global Native
Pairs:Pair[] Function GetVariables(Var akStruct) Global Native

Var[] Function GetValuesByName(Var[] akStructs, string asVariableName) Global Native

int Function IndexOfValue(Var[] akStructs, string asVariableName, Var akValue, int aiStartIndex = 0, int aiCount = 0x7FFFFFFF) Global Native
int Function LastIndexOfValue(Var[] akStructs, string asVariableName, Var akValue, int aiStartIndex = 0x7FFFFFFF, int aiCount = 0x7FFFFFFF) Global Native
