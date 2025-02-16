Scriptname System:Math Const Hidden Native

;/
	Provides common non-delayed mathematical functions and constants.
/;

float Function Pi() Global Native
float Function E() Global Native
float Function Tau() Global Native


;/
	Randomizer Functions

	Notes:
	- These are much faster and more "random" than the vanilla functions.
/;

int Function RandomSeed() Global Native

bool Function RandomBool() Global
	return SeededBool(RandomSeed())
EndFunction
bool Function SeededBool(int auSeed) Global Native

int Function RandomInt(int aiMinInclusive, int aiMaxInclusive) Global
	return SeededInt(aiMinInclusive, aiMaxInclusive, RandomSeed())
EndFunction
int Function SeededInt(int aiMinInclusive, int aiMaxInclusive, int auSeed) Global Native

float Function RandomFloat(float afMinInclusive, float afMaxExclusive) Global
	return SeededFloat(afMinInclusive, afMaxExclusive, RandomSeed())
EndFunction
float Function SeededFloat(float afMinInclusive, float afMaxExclusive, int auSeed) Global Native

Var[] Function Shuffle(Var[] akArray) Global
	return SeededShuffle(akArray, RandomSeed())
EndFunction
Var[] Function SeededShuffle(Var[] akArray, int auSeed) Global Native


int Function Abs(int aiValue) Global Native
float Function AbsF(float afValue) Global Native

int Function Min(int aiLeft, int aiRight) Global Native
float Function MinF(float afLeft, float afRight) Global Native

int Function Max(int aiLeft, int aiRight) Global Native
float Function MaxF(float afLeft, float afRight) Global Native

int Function Clamp(int aiValue, int aiMin, int aiMax) Global Native
float Function ClampF(float afValue, float afMin, float afMax) Global Native

int Function Sign(int aiValue) Global Native
int Function SignF(float afValue) Global Native

int Function CopySign(int aiMagnitude, int aiSign) Global Native
float Function CopySignF(float afMagnitude, float afSign) Global Native


float Function Ceil(float afValue) Global Native
float Function Floor(float afValue) Global Native
float Function Round(float afValue, int aiDecimals = 0) Global Native
float Function Trunc(float afValue) Global Native

float Function Lerp(float afStart, float afEnd, float afAlpha) Global Native
int Function LCM(int aiLeft, int aiRight) Global Native
int Function GCD(int aiLeft, int aiRight) Global Native


float Function Pow(float afBase, float afExponent) Global Native
float Function Sqrt(float afValue) Global Native

float Function Exp(float afValue) Global Native
float Function Exp2(float afValue) Global
	return Pow(2.0, afValue)
EndFunction
float Function Exp10(float afValue) Global
	return Pow(10.0, afValue)
EndFunction

float Function Log(float afValue) Global Native
float Function LogN(float afValue, float afBase) Global Native
float Function Log2(float afValue) Global
	return LogN(afValue, 2.0)
EndFunction
float Function Log10(float afValue) Global
	return LogN(afValue, 10.0)
EndFunction


float Function DegToRad(float afDegrees) Global Native
float Function RadToDeg(float afRadians) Global Native
float Function Cbrt(float afValue) Global Native
float Function Hypot(float afX, float afY) Global Native


float Function Sin(float afValue) Global Native
float Function Cos(float afValue) Global Native
float Function Tan(float afValue) Global Native
float Function Sinh(float afValue) Global Native
float Function Cosh(float afValue) Global Native
float Function Tanh(float afValue) Global Native
float Function Asin(float afValue) Global Native
float Function Acos(float afValue) Global Native
float Function Atan(float afValue) Global Native
float Function Atan2(float afY, float afX) Global Native
float Function Asinh(float afValue) Global Native
float Function Acosh(float afValue) Global Native
float Function Atanh(float afValue) Global Native
