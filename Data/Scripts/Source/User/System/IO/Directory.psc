Scriptname System:IO:Directory Const Hidden Native

;/
	Provides common non-delayed functions for directories.

	Notes:
	- These functions are only valid within the game's root folder and its subdirectories.
	- The search pattern uses the following wildcard characters:
	  - "*": Matches zero or more characters.
	  - "?": Matches a single character.

	Wildcard Examples:
	- "Scripts/Source/*": Matches all files in the "Scripts/Source" directory.
	- "Scripts/Source/*.psc": Matches all files with the extension ".psc" in the "Scripts/Source" directory.
	- "Scripts/Source/?.psc": Matches all files with a single character extension in the "Scripts/Source" directory.
/;

string[] Function GetDirectories(string asPath, string asSearchPattern = "", bool abRecursive = false) Global Native
string[] Function GetFiles(string asPath, string asSearchPattern = "", bool abRecursive = false) Global Native

System:Enumerable Function EnumerateDirectories(string asPath, string asSearchPattern = "", bool abRecursive = false) Global
	string[] directories = GetDirectories(asPath, asSearchPattern, abRecursive)
	return System:Enumerable.From(directories as Var[])
EndFunction
System:Enumerable Function EnumerateFiles(string asPath, string asSearchPattern = "", bool abRecursive = false) Global
	string[] files = GetFiles(asPath, asSearchPattern, abRecursive)
	return System:Enumerable.From(files as Var[])
EndFunction

bool Function Exists(string asPath) Global Native
bool Function Create(string asPath) Global Native
bool Function Move(string asOldPath, string asNewPath) Global Native
bool Function Copy(string asOldPath, string asNewPath) Global Native
bool Function Delete(string asPath) Global Native
