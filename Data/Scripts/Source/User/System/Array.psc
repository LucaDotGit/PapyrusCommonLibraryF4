Scriptname System:Array Const Hidden Native

;/
	Provides common non-delayed functions for immutable arrays.
	
	Notes:
	- Be sure to cast your array to `Var[]`, if not already, before using these functions.
	- The vanilla array limit of 128 elements doesn't apply here, like in all other non-vanilla array functions.
/;

Var[] Function Repeat(int aiCount) Global Native
bool[] Function RepeatBool(int aiCount, bool abValue = false) Global Native
int[] Function RepeatInt(int aiCount, int aiValue = 0) Global Native
float[] Function RepeatFloat(int aiCount, float afValue = 0.0) Global Native
string[] Function RepeatString(int aiCount, string asValue = "") Global Native
ScriptObject[] Function RepeatObject(int aiCount, ScriptObject akObject = none) Global Native
Var[] Function RepeatVar(int aiCount, Var akValue) Global Native
Var[] Function RepeatArray(int aiCount, Var[] akArray) Global Native

int[] Function Range(int aiStart, int aiCount, int aiStep = 1) Global Native
float[] Function RangeFloat(float afStart, int aiCount, float afStep = 1.0) Global Native

Var[] Function Copy(Var[] akArray) Global Native
Var[] Function DeepCopy(Var[] akArray) Global Native

Var Function BoolArrayToVar(bool[] akArray) Global Native
Var Function IntArrayToVar(int[] akArray) Global Native
Var Function FloatArrayToVar(float[] akArray) Global Native
Var Function StringArrayToVar(string[] akArray) Global Native
Var Function ObjectArrayToVar(ScriptObject[] akArray) Global Native
Var Function VarArrayToVar(Var[] akArray) Global Native

bool[] Function VarToBoolArray(Var akValue) Global Native
int[] Function VarToIntArray(Var akValue) Global Native
float[] Function VarToFloatArray(Var akValue) Global Native
string[] Function VarToStringArray(Var akValue) Global Native
ScriptObject[] Function VarToObjectArray(Var akValue) Global Native
Var[] Function VarToVarArray(Var akValue) Global Native

bool Function IsEmpty(Var[] akArray) Global
	return akArray.Length == 0
EndFunction
int Function Count(Var[] akArray) Global
	return akArray.Length
EndFunction

bool Function Contains(Var[] akArray, Var akValue) Global Native
bool Function StartsWith(Var[] akArray, Var akValue) Global Native
bool Function EndsWith(Var[] akArray, Var akValue) Global Native

Var Function First(Var[] akArray) Global
	return akArray[0]
EndFunction
Var Function Last(Var[] akArray) Global
	return akArray[akArray.Length - 1]
EndFunction
Var Function At(Var[] akArray, int aiIndex) Global
	return akArray[aiIndex]
EndFunction

int Function IndexOf(Var[] akArray, Var akValue, int aiStartIndex = 0, int aiCount = 0x7FFFFFFF) Global Native
int Function LastIndexOf(Var[] akArray, Var akValue, int aiStartIndex = 0x7FFFFFFF, int aiCount = 0x7FFFFFFF) Global Native

Var Function Find(Var[] akArray, Var akValue) Global
	int index = IndexOf(akArray, akValue)
	If (index >= 0)
		return akArray[index]
	Else
		return none
	EndIf
EndFunction
Var Function FindLast(Var[] akArray, Var akValue) Global
	int index = LastIndexOf(akArray, akValue)
	If (index >= 0)
		return akArray[index]
	Else
		return none
	EndIf
EndFunction

bool Function Any(Var[] akArray1, Var[] akArray2) Global Native
bool Function All(Var[] akArray1, Var[] akArray2) Global Native

Var Function Min(Var[] akArray) Global Native
Var Function Max(Var[] akArray) Global Native

int Function Sum(int[] akArray) Global Native
float Function SumFloat(float[] akArray) Global Native

int Function Average(int[] akArray) Global Native
float Function AverageFloat(float[] akArray) Global Native

Var[] Function Union(Var[] akArray1, Var[] akArray2) Global Native
Var[] Function Intersect(Var[] akArray1, Var[] akArray2) Global Native
Var[] Function Except(Var[] akArray1, Var[] akArray2) Global Native
Var[] Function Take(Var[] akArray, int aiCount) Global Native
Var[] Function Skip(Var[] akArray, int aiCount) Global Native
Var[] Function Distinct(Var[] akArray) Global Native

Var[] Function Sort(Var[] akArray, bool abDescending = false) Global Native
Var[] Function Reverse(Var[] akArray) Global Native

string Function Join(Var[] akArray, string asSeparator = ", ") Global
	return System:Strings.Join(akArray as string[], asSeparator)
EndFunction

Var[] Function Add(Var[] akArray, Var akValue) Global Native
Var[] Function AddRange(Var[] akArray, Var[] akValues) Global Native

Var[] Function Insert(Var[] akArray, int aiIndex, Var akValue) Global Native
Var[] Function InsertRange(Var[] akArray, int aiIndex, Var[] akValues) Global Native

Var[] Function Remove(Var[] akArray, Var akValue) Global Native
Var[] Function RemoveAll(Var[] akArray, Var akValue) Global Native
Var[] Function RemoveAt(Var[] akArray, int aiIndex) Global Native
Var[] Function RemoveRange(Var[] akArray, int aiIndex, int aiCount) Global Native

Var[] Function Fill(Var[] akArray, Var akValue, int aiStartIndex = 0, int aiCount = 0x7FFFFFFF) Global Native
Var[] Function Resize(Var[] akArray, int aiCount) Global Native
