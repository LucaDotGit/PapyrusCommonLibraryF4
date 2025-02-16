Scriptname System:Regex Const Hidden Native

;/
	Provides common non-delayed functions for regular expressions.

	Notes:
	- For grammar specifications, see: https://www.boost.org/libs/regex/doc/html/boost_regex/syntax/perl_syntax.html.

	Flags:
	- "m": Specifies multi-line mode where `.` does not match newlines.
	- "s": Specifies single-line mode where `^` and `$` match the start and end of the entire string, instead of for each line.
/;

bool Function IsValid(string asPattern, string asFlags = "") Global Native
bool Function IsMatch(string asString, string asPattern, string asFlags = "") Global Native

string Function Escape(string asString) Global Native
string Function Unescape(string asString) Global Native

string Function Match(string asString, string asPattern, string asFlags = "") Global Native
string[] Function Matches(string asString, string asPattern, string asFlags = "") Global Native
int Function Search(string asString, string asPattern, string asFlags = "") Global Native

string Function Replace(string asString, string asPattern, string asReplacement, string asFlags = "") Global Native
string Function ReplaceAll(string asString, string asPattern, string asReplacement, string asFlags = "") Global Native
string[] Function Split(string asString, string asPattern, int aiCount = 0x7FFFFFFF, string asFlags = "") Global Native
