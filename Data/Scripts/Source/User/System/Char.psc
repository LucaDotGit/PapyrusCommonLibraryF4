Scriptname System:Char Const Hidden Native

;/
	Provides basic non-delayed functions for characters.
/;

int Function Min() Global Native
int Function Max() Global Native

int Function TryParse(string asString, int acDefault = 0) Global Native

; For format specifications, see: https://fmt.dev/latest/syntax.
; Example: System:Char.ToString(65, "{:c}") -> "A"
string Function ToString(int acChar, string asFormat = "") Global Native
