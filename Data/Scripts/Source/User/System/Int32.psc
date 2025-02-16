Scriptname System:Int32 Const Hidden Native

;/
	Provides basic non-delayed functions for signed 32-bit integers.
/;

int Function Min() Global Native
int Function Max() Global Native

int Function TryParse(string asString, int aiBase = 10, int aiDefault = 0) Global Native

; For format specifications, see: https://fmt.dev/latest/syntax.
; Example: System:Int32.ToString(123, "0x{:X}") -> "0x7B"
string Function ToString(int aiInt, string asFormat = "") Global Native
