Scriptname System:Strings Const Hidden Native

;/
	Provides common non-delayed functions for strings.

	Notes:
	- The language's strings are encoded in UTF-8.
	- The strings are getting hashed case-insensitively,
	  meaning that the case can depend, whether the value is already hashed or not.
/;

; Attempts to revert the string, and possibly its case, to the hashed form,
; possibly fixing some functions not working due to case-sensitivity.
string Function Rehash(string asString) Global Native

string Function Empty() Global Native
bool Function IsEmpty(string asString) Global Native

bool Function IsWhitespace(string asString) Global Native
bool Function IsBlank(string asString) Global Native
bool Function IsDigit(string asString) Global Native
bool Function IsLetter(string asString) Global Native
bool Function IsLetterOrDigit(string asString) Global Native
bool Function IsPunctuation(string asString) Global Native
bool Function IsControl(string asString) Global Native
bool Function IsGraphic(string asString) Global Native
bool Function IsPrintable(string asString) Global Native
bool Function IsLower(string asString) Global Native
bool Function IsUpper(string asString) Global Native

bool Function Contains(string asString, string asSubstring) Global Native
bool Function StartsWith(string asString, string asSubstring) Global Native
bool Function EndsWith(string asString, string asSubstring) Global Native

bool Function Any(string asString, string[] akSubstrings) Global Native
bool Function All(string asString, string[] akSubstrings) Global Native

int Function Size(string asString) Global Native
string Function First(string asString) Global Native
string Function Last(string asString) Global Native

string Function CharAt(string asString, int aiIndex) Global Native
int Function CharCodeAt(string asString, int aiIndex) Global Native
string[] Function ToCharArray(string asString) Global Native

int Function IndexOf(string asString, string asSubstring, int aiStartIndex = 0, int aiCount = 0x7FFFFFFF) Global Native
int Function IndexOfAny(string asString, string[] akSubstrings, int aiStartIndex = 0, int aiCount = 0x7FFFFFFF) Global Native
int Function LastIndexOf(string asString, string asSubstring, int aiStartIndex = 0x7FFFFFFF, int aiCount = 0x7FFFFFFF) Global Native
int Function LastIndexOfAny(string asString, string[] akSubstrings, int aiStartIndex = 0x7FFFFFFF, int aiCount = 0x7FFFFFFF) Global Native
int Function Count(string asString, string asSubstring, int aiStartIndex = 0, int aiCount = 0x7FFFFFFF) Global Native

string Function Substring(string asString, int aiStartIndex, int aiCount = 0x7FFFFFFF) Global Native
string Function Remove(string asString, int aiStartIndex, int aiCount = 0x7FFFFFFF) Global Native
string Function Insert(string asString, int aiIndex, string asSubstring) Global Native
string Function ReplaceAt(string asString, int aiIndex, string asReplacement) Global Native

string Function Replace(string asString, string asSubstring, string asReplacement, int aiCount = 0x7FFFFFFF) Global Native
string[] Function Split(string asString, string asSeparator, int aiCount = 0x7FFFFFFF) Global Native
string Function Join(string[] akStrings, string asSeparator = ", ") Global Native
string Function Concat(string[] akStrings) Global Native
string Function Repeat(string asString, int aiCount) Global Native

string Function Reverse(string asString) Global Native
string Function ToLower(string asString) Global Native
string Function ToUpper(string asString) Global Native

string Function Trim(string asString, string asTrimString = " ") Global Native
string Function TrimStart(string asString, string asTrimString = " ") Global Native
string Function TrimEnd(string asString, string asTrimString = " ") Global Native

string Function PadLeft(string asString, int aiTotalSize, string asPadString = " ") Global Native
string Function PadRight(string asString, int aiTotalSize, string asPadString = " ") Global Native
string Function Truncate(string asString, int aiTotalSize, string asSuffix = "...") Global Native

;/
	Notes:
	- For format specifications, see: https://fmt.dev/latest/syntax.
	- Objects, like structs and arrays, are automatically converted to strings.

	Example:
	Var[] args = new Var[3]
	args[0] = 123
	args[1] = 456
	args[2] = 579
	System:Strings.Format("{} + {} = {}", args) -> "123 + 456 = 579"
/;
string Function Format(string asFormat, Var[] akArgs = none) Global Native
