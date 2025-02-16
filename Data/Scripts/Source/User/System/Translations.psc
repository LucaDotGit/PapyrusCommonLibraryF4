Scriptname System:Translations Const Hidden Native

;/
	Provides common functions for the game's translation system.

	Notes:
	- The language's strings are encoded in UTF-8,
	  thus these functions will convert them to UTF-16,
	  since the translation system uses this encoding.
	- The keys should be prefixed with a dollar sign ("$").

	Language Codes:
	- "cn": Traditional Chinese
	- "de": German
	- "en": English
	- "es": Spanish (Spain)
	- "esmx": Spanish (Mexico)
	- "fr": French
	- "it": Italian
	- "ja": Japanese
	- "pl": Polish
	- "ptbr": Portuguese (Brazil)
	- "ru": Russian
/;

string Function GetLanguageCode() Global Native
bool Function Contains(string asKey) Global Native

string Function GetValue(string asKey, string asDefault = "") Global Native
bool Function SetValue(string asKey, string asValue) Global Native

bool Function Add(string asKey, string asValue) Global Native
bool Function Remove(string asKey) Global Native
