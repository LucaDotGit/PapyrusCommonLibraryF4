Scriptname System:Boolean Const Hidden Native

;/
	Provides basic non-delayed functions for booleans.
/;

string Function FalseString() Global Native
string Function TrueString() Global Native

bool Function TryParse(string asString) Global Native

; For format specifications, see: https://fmt.dev/latest/syntax.
string Function ToString(bool abBool, string asFormat = "") Global Native
