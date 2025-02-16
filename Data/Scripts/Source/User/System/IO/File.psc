Scriptname System:IO:File Const Hidden Native

;/
	Provides common non-delayed functions for files.

	Notes:
	- These functions are only valid within the game's root folder and its subdirectories.
/;

string Function ReadAllText(string asPath) Global Native
string[] Function ReadAllLines(string asPath) Global Native

bool Function WriteAllText(string asPath, string asText) Global Native
bool Function WriteAllLines(string asPath, string[] akLines) Global Native

bool Function AppendAllText(string asPath, string asText) Global Native
bool Function AppendAllLines(string asPath, string[] akLines) Global Native
bool Function AppendLine(string asPath, string asLine) Global
	string[] lines = new string[1]
	lines[0] = asLine
	return AppendAllLines(asPath, lines)
EndFunction

bool Function Exists(string asPath) Global Native
bool Function Create(string asPath) Global Native
bool Function Move(string asOldPath, string asNewPath) Global Native
bool Function Copy(string asOldPath, string asNewPath) Global Native
bool Function Delete(string asPath) Global Native
