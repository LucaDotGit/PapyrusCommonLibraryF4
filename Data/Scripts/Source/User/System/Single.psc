Scriptname System:Single Const Hidden Native

;/
	Provides basic non-delayed functions for single-precision floating point numbers.
/;

int Function Decimals() Global Native
int Function MaxDecimals() Global Native

float Function Min() Global Native
float Function Max() Global Native

float Function Epsilon() Global Native
float Function NaN() Global Native
float Function PositiveInfinity() Global Native
float Function NegativeInfinity() Global Native

bool Function IsNaN(float afFloat) Global Native

bool Function IsInfinity(float afFloat) Global Native
bool Function IsPositiveInfinity(float afFloat) Global Native
bool Function IsNegativeInfinity(float afFloat) Global Native

float Function TryParse(string asString, float afDefault = 0.0) Global Native

; For format specifications, see: https://fmt.dev/latest/syntax.
; Example: System:Single.ToString(123.456, "{:.2f}") -> "123.46"
string Function ToString(float afFloat, string asFormat = "") Global Native
