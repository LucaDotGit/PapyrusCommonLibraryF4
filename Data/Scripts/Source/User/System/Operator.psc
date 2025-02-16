Scriptname System:Operator Const Hidden Native

;/
	Provides common non-delayed operator functions.

	Notes:
	- The comparison only works for variables of the same type,
	  otherwise the left variable is considered as lesser.

	Raw Variable Types:
	00	None
	01	Object
	02	String
	03	Int
	04	Float
	05	Bool
	06	Var
	07	Struct
	11	Array Object
	12	Array String
	13	Array Int
	14	Array Float
	15	Array Bool
	16	Array Var
	17	Array Struct
/;

Var Function Copy(Var akValue) Global Native
Var Function DeepCopy(Var akValue) Global Native


bool Function IsNone(Var akValue) Global Native
bool Function IsValueType(Var akValue) Global
	return akValue is bool || akValue is int || akValue is float
EndFunction
bool Function IsRefType(Var akValue) Global
	return !IsNone(akValue) && !IsValueType(akValue)
EndFunction

bool Function IsStruct(Var akValue) Global Native
bool Function IsArray(Var akValue) Global Native


int Function Compare(Var akLeft, Var akRight) Global Native

bool Function Equals(Var akLeft, Var akRight) Global
	return Compare(akLeft, akRight) == 0
EndFunction
bool Function IsLessThan(Var akLeft, Var akRight) Global
	return Compare(akLeft, akRight) < 0
EndFunction
bool Function IsLessThanOrEqual(Var akLeft, Var akRight) Global
	return Compare(akLeft, akRight) <= 0
EndFunction
bool Function IsGreaterThan(Var akLeft, Var akRight) Global
	return Compare(akLeft, akRight) > 0
EndFunction
bool Function IsGreaterThanOrEqual(Var akLeft, Var akRight) Global
	return Compare(akLeft, akRight) >= 0
EndFunction
bool Function IsInRange(Var akValue, Var akMin, Var akMax) Global
	return Compare(akValue, akMin) >= 0 && Compare(akValue, akMax) <= 0
EndFunction

bool Function RefEquals(Var akLeft, Var akRight) Global Native
bool Function TypeEquals(Var akLeft, Var akRight) Global Native

int Function GetRawType(Var akValue) Global Native


int Function Mod(int aiLeft, int aiRight) Global Native
float Function ModF(float afLeft, float afRight) Global Native

int Function LShift(int auLeft, int auRight) Global Native
int Function RShift(int auLeft, int auRight) Global Native
int Function AND(int auLeft, int auRight) Global Native
int Function OR(int auLeft, int auRight) Global Native
int Function XOR(int auLeft, int auRight) Global Native
int Function NOT(int auValue) Global Native


bool Function HasFlag(int auValue, int auFlag) Global Native
int Function SetFlag(int auValue, int auFlag, bool abSet) Global Native
