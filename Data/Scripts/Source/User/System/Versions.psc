Scriptname System:Versions Const Hidden

;/
	Provides shared data for versions.
/;

Struct Version
	int Major
	int Minor
	int Patch
	int Build
EndStruct

Version Function Create(int aiMajor = 0, int aiMinor = 0, int aiPatch = 0, int aiBuild = 0) Global
	Version version = new Version
	version.Major = aiMajor
	version.Minor = aiMinor
	version.Patch = aiPatch
	version.Build = aiBuild
	return version
EndFunction

Version Function FromString(string asVersion) Global
	string[] parts = System:Strings.Split(asVersion, ".")
	int count = parts.Length

	int major = 0
	int minor = 0
	int patch = 0
	int build = 0

	If (count > 0)
		major = System:Int32.TryParse(parts[0])
	EndIf

	If (count > 1)
		minor = System:Int32.TryParse(parts[1])
	EndIf

	If (count > 2)
		patch = System:Int32.TryParse(parts[2])
	EndIf

	If (count > 3)
		build = System:Int32.TryParse(parts[3])
	EndIf

	return Create(major, minor, patch, build)
EndFunction

string Function ToString(Version akVersion) Global
	return akVersion.Major + "." + akVersion.Minor + "." + akVersion.Patch + "." + akVersion.Build
EndFunction
