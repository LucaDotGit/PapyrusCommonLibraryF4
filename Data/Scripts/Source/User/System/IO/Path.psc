Scriptname System:IO:Path Const Hidden Native

;/
	Provides common non-delayed functions for paths.

	Notes:
	- These functions do not interact with the filesystem.
/;

string Function CurrentDirectory() Global Native
string Function ParentDirectory() Global Native
string Function ExtensionSeparator() Global Native
string Function DirectorySeparator() Global Native
string Function AltDirectorySeparator() Global Native

string[] Function GetInvalidPathChars() Global Native
string[] Function GetInvalidFileNameChars() Global Native

bool Function IsInSandbox(string asPath) Global Native
bool Function Equals(string asPath1, string asPath2) Global Native
int Function Compare(string asPath1, string asPath2) Global Native

string Function GetParent(string asPath) Global Native
string Function GetRelative(string asPath, string asRelative) Global Native

string Function GetDirectoryName(string asPath) Global Native
string Function GetFileName(string asPath) Global Native
string Function GetFileNameWithoutExtension(string asPath) Global Native
string Function GetExtension(string asPath) Global Native

string Function ChangeFileName(string asPath, string asFileName) Global Native
string Function ChangeExtension(string asPath, string asExtension) Global Native

string Function TrimEndingSeparator(string asPath) Global Native
string Function Normalize(string asPath) Global Native

string[] Function Split(string asPath) Global Native
string Function Join(string[] akPaths) Global Native
