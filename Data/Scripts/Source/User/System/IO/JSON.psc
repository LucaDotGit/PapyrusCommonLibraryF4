Scriptname System:IO:JSON Const Hidden Native

;/
	Provides common non-delayed functions for JSON files.

	Notes:
	- These functions are only valid within the game's root folder and its subdirectories.
	- Nested keys are separated by forward slashes ("/"), like "/root/node/array/1";
	  See: https://json.nlohmann.me/features/json_pointer.

	Form Format:
	{
		"modName": "MyMod.esp",
		"formID": 123456
	}

	Struct Format:
	{
		"structName": "MyScript#MyStruct",
		"variables": {
			"MyInt": 10,
			"MyFloat": 1.0,
			"MyString": "Hello, World!"
		}
	}
/;

bool Function Contains(string asPath, string asKey) Global Native
bool Function Remove(string asPath, string asKey) Global Native
bool Function Clear(string asPath, string asKey) Global Native

bool Function GetBool(string asPath, string asKey, bool abDefault = false) Global Native
bool Function SetBool(string asPath, string asKey, bool abValue) Global Native
bool[] Function GetBoolArray(string asPath, string asKey) Global Native
bool Function SetBoolArray(string asPath, string asKey, bool[] akValues) Global Native

int Function GetInt(string asPath, string asKey, int aiDefault = 0) Global Native
bool Function SetInt(string asPath, string asKey, int aiValue) Global Native
int[] Function GetIntArray(string asPath, string asKey) Global Native
bool Function SetIntArray(string asPath, string asKey, int[] akValues) Global Native

int Function GetUInt(string asPath, string asKey, int auDefault = 0) Global Native
bool Function SetUInt(string asPath, string asKey, int auValue) Global Native
int[] Function GetUIntArray(string asPath, string asKey) Global Native
bool Function SetUIntArray(string asPath, string asKey, int[] akValues) Global Native

float Function GetFloat(string asPath, string asKey, float afDefault = 0.0) Global Native
bool Function SetFloat(string asPath, string asKey, float afValue) Global Native
float[] Function GetFloatArray(string asPath, string asKey) Global Native
bool Function SetFloatArray(string asPath, string asKey, float[] akValues) Global Native

string Function GetString(string asPath, string asKey, string asDefault = "") Global Native
bool Function SetString(string asPath, string asKey, string asValue) Global Native
string[] Function GetStringArray(string asPath, string asKey) Global Native
bool Function SetStringArray(string asPath, string asKey, string[] akValues) Global Native

Var Function GetVar(string asPath, string asKey) Global Native
bool Function SetVar(string asPath, string asKey, Var akValue) Global Native
Var[] Function GetVarArray(string asPath, string asKey) Global Native
bool Function SetVarArray(string asPath, string asKey, Var[] akValues) Global Native


;/
	Notes:
	- The below functions are equivalent to the `Var` ones, but without storing the struct's name,
	  so you need to specify it manually when retrieving the value.

	Struct Format:
	{
		"MyInt": 10,
		"MyFloat": 1.0,
		"MyString": "Hello, World!"
	}
/;

Var Function GetStruct(string asPath, string asKey, string asStructName) Global Native
bool Function SetStruct(string asPath, string asKey, Var akValue) Global Native
Var[] Function GetStructArray(string asPath, string asKey, string asStructName) Global Native
bool Function SetStructArray(string asPath, string asKey, Var[] akValues) Global Native
