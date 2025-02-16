Scriptname System:IO:INI Const Hidden Native

;/
	Provides common non-delayed functions for INI files.

	Notes:
	- These functions are only valid within the game's root folder and its subdirectories.
	- Multi-line and quoted values are supported;
	  See: https://brofield.github.io/simpleini#multiline.
/;

Struct Entry
	string Section
	System:Pairs:StringPair[] Pairs
EndStruct

string[] Function GetSections(string asPath) Global Native
string[] Function GetKeys(string asPath, string asSection) Global Native
string[] Function GetValues(string asPath, string asSection) Global Native

System:Pairs:StringPair[] Function GetPairs(string asPath, string asSection) Global Native
bool Function SetPairs(string asPath, string asSection, System:Pairs:StringPair[] akPairs) Global Native

Entry[] Function GetEntries(string asPath) Global Native
bool Function SetEntries(string asPath, Entry[] akEntries) Global Native

bool Function ContainsSection(string asPath, string asSection) Global Native
bool Function ContainsKey(string asPath, string asSection, string asKey) Global Native

; The values true, false, yes, no, on, off, 1 and 0 are supported.
bool Function GetBool(string asPath, string asSection, string asKey, bool abDefault = false) Global Native
bool Function SetBool(string asPath, string asSection, string asKey, bool abValue) Global Native

int Function GetInt(string asPath, string asSection, string asKey, int aiDefault = 0) Global Native
bool Function SetInt(string asPath, string asSection, string asKey, int aiValue) Global Native

int Function GetUInt(string asPath, string asSection, string asKey, int auDefault = 0) Global Native
bool Function SetUInt(string asPath, string asSection, string asKey, int auValue) Global Native

float Function GetFloat(string asPath, string asSection, string asKey, float afDefault = 0.0) Global Native
bool Function SetFloat(string asPath, string asSection, string asKey, float afValue) Global Native

string Function GetString(string asPath, string asSection, string asKey, string asDefault = "") Global Native
bool Function SetString(string asPath, string asSection, string asKey, string asValue) Global Native

bool Function RemoveSection(string asPath, string asSection) Global Native
bool Function RemoveKey(string asPath, string asSection, string asKey) Global Native
