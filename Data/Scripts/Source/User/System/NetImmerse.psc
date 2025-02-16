Scriptname System:NetImmerse Const Hidden Native

;/
	Provides common functions for the NetImmerse part of the engine.
	It's used to represent meshes, animations, effects and more.

	Terminology:
	- Node: A point in the hierarchy of a mesh. It can represent a bone, light, a camera, etc.
	- Transform: A combination of rotation, position and scale.
	- Local Transform: The transform of a node relative to its parent.
	- World Transform: The transform of a node relative to the world.
	
	Tools:
	- NifSkope: A tool to view and edit NIF files. See: https://github.com/niftools/nifskope.
/;

Struct NiMatrix3x4
	Vectors:Vector4 Row0
	Vectors:Vector4 Row1
	Vectors:Vector4 Row2
	Vectors:Vector4 Row3
EndStruct

Struct NiTransform
	NiMatrix3x4 Rotation
	Vectors:Vector3 Position
	float Scale
EndStruct

bool Function ContainsNode(ObjectReference akRef, string asNodeName, bool abFirstPerson = false) Global Native
string[] Function GetChildrenNames(ObjectReference akRef, bool abFirstPerson = false) Global Native

string Function GetNodeParentName(ObjectReference akRef, string asNodeName, bool abFirstPerson = false) Global Native
string[] Function GetNodeChildrenNames(ObjectReference akRef, string asNodeName, bool abFirstPerson = false) Global Native

;/
	Start of delayed functions.
/;

NiTransform Function GetNodeLocalTransform(ObjectReference akRef, string asNodeName, bool abFirstPerson = false) Global Native
bool Function SetNodeLocalTransform(ObjectReference akRef, string asNodeName, NiTransform akTransform, bool abFirstPerson = false) Global Native

NiTransform Function GetNodeWorldTransform(ObjectReference akRef, string asNodeName, bool abFirstPerson = false) Global Native
bool Function SetNodeWorldTransform(ObjectReference akRef, string asNodeName, NiTransform akTransform, bool abFirstPerson = false) Global Native

Vectors:Vector3 Function GetRelativeNodePosition(ObjectReference akRef, string asLeftNodeName, string asRightNodeName, bool abFirstPerson = false) Global Native

;/
	End of delayed functions.
/;

bool Function ContainsNodeExtraData(ObjectReference akRef, string asNodeName, string asDataName, bool abFirstPerson = false) Global Native
string[] Function GetNodeExtraDataNames(ObjectReference akRef, string asNodeName, bool abFirstPerson = false) Global Native

bool Function IsNodeExtraDataBool(ObjectReference akRef, string asNodeName, string asDataName, bool abFirstPerson = false) Global Native
bool Function GetNodeExtraDataBool(ObjectReference akRef, string asNodeName, string asDataName, bool abDefault = false, bool abFirstPerson = false) Global Native
bool Function SetNodeExtraDataBool(ObjectReference akRef, string asNodeName, string asDataName, bool abValue, bool abFirstPerson = false) Global Native

bool Function IsNodeExtraDataInt(ObjectReference akRef, string asNodeName, string asDataName, bool abFirstPerson = false) Global Native
int Function GetNodeExtraDataInt(ObjectReference akRef, string asNodeName, string asDataName, int aiDefault = 0, bool abFirstPerson = false) Global Native
bool Function SetNodeExtraDataInt(ObjectReference akRef, string asNodeName, string asDataName, int aiValue, bool abFirstPerson = false) Global Native

bool Function IsNodeExtraDataFloat(ObjectReference akRef, string asNodeName, string asDataName, bool abFirstPerson = false) Global Native
float Function GetNodeExtraDataFloat(ObjectReference akRef, string asNodeName, string asDataName, float afDefault = 0.0, bool abFirstPerson = false) Global Native
bool Function SetNodeExtraDataFloat(ObjectReference akRef, string asNodeName, string asDataName, float afValue, bool abFirstPerson = false) Global Native

bool Function IsNodeExtraDataString(ObjectReference akRef, string asNodeName, string asDataName, bool abFirstPerson = false) Global Native
string Function GetNodeExtraDataString(ObjectReference akRef, string asNodeName, string asDataName, string asDefault = "", bool abFirstPerson = false) Global Native
bool Function SetNodeExtraDataString(ObjectReference akRef, string asNodeName, string asDataName, string asValue, bool abFirstPerson = false) Global Native

bool Function IsNodeExtraDataIntArray(ObjectReference akRef, string asNodeName, string asDataName, bool abFirstPerson = false) Global Native
int[] Function GetNodeExtraDataIntArray(ObjectReference akRef, string asNodeName, string asDataName, bool abFirstPerson = false) Global Native
bool Function SetNodeExtraDataIntArray(ObjectReference akRef, string asNodeName, string asDataName, int[] akValues, bool abFirstPerson = false) Global Native

bool Function IsNodeExtraDataFloatArray(ObjectReference akRef, string asNodeName, string asDataName, bool abFirstPerson = false) Global Native
float[] Function GetNodeExtraDataFloatArray(ObjectReference akRef, string asNodeName, string asDataName, bool abFirstPerson = false) Global Native
bool Function SetNodeExtraDataFloatArray(ObjectReference akRef, string asNodeName, string asDataName, float[] akValues, bool abFirstPerson = false) Global Native

bool Function IsNodeExtraDataStringArray(ObjectReference akRef, string asNodeName, string asDataName, bool abFirstPerson = false) Global Native
string[] Function GetNodeExtraDataStringArray(ObjectReference akRef, string asNodeName, string asDataName, bool abFirstPerson = false) Global Native
bool Function SetNodeExtraDataStringArray(ObjectReference akRef, string asNodeName, string asDataName, string[] akValues, bool abFirstPerson = false) Global Native
