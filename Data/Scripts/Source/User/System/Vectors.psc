Scriptname System:Vectors Const Hidden

;/
	Provides shared data for vectors.
/;

Struct Vector2
	float X
	float Y
EndStruct

Struct Vector3
	float X
	float Y
	float Z
EndStruct

Struct Vector4
	float X
	float Y
	float Z
	float W
EndStruct

Vector2 Function Create2D(float afX = 0.0, float afY = 0.0) Global
	Vector2 vec2 = new Vector2
	vec2.X = afX
	vec2.Y = afY
	return vec2
EndFunction

Vector3 Function Create3D(float afX = 0.0, float afY = 0.0, float afZ = 0.0) Global
	Vector3 vec3 = new Vector3
	vec3.X = afX
	vec3.Y = afY
	vec3.Z = afZ
	return vec3
EndFunction

Vector4 Function Create4D(float afX = 0.0, float afY = 0.0, float afZ = 0.0, float afW = 0.0) Global
	Vector4 vec4 = new Vector4
	vec4.X = afX
	vec4.Y = afY
	vec4.Z = afZ
	vec4.W = afW
	return vec4
EndFunction


Vector2 Function Add2D(Vector2 akVecA, Vector2 akVecB) Global
	float x = akVecA.X + akVecB.X
	float y = akVecA.Y + akVecB.Y
	return Create2D(x, y)
EndFunction

Vector3 Function Add3D(Vector3 akVecA, Vector3 akVecB) Global
	float x = akVecA.X + akVecB.X
	float y = akVecA.Y + akVecB.Y
	float z = akVecA.Z + akVecB.Z
	return Create3D(x, y, z)
EndFunction

Vector4 Function Add4D(Vector4 akVecA, Vector4 akVecB) Global
	float x = akVecA.X + akVecB.X
	float y = akVecA.Y + akVecB.Y
	float z = akVecA.Z + akVecB.Z
	float w = akVecA.W + akVecB.W
	return Create4D(x, y, z, w)
EndFunction

Vector2 Function Subtract2D(Vector2 akVecA, Vector2 akVecB) Global
	float x = akVecA.X - akVecB.X
	float y = akVecA.Y - akVecB.Y
	return Create2D(x, y)
EndFunction

Vector3 Function Subtract3D(Vector3 akVecA, Vector3 akVecB) Global
	float x = akVecA.X - akVecB.X
	float y = akVecA.Y - akVecB.Y
	float z = akVecA.Z - akVecB.Z
	return Create3D(x, y, z)
EndFunction

Vector4 Function Subtract4D(Vector4 akVecA, Vector4 akVecB) Global
	float x = akVecA.X - akVecB.X
	float y = akVecA.Y - akVecB.Y
	float z = akVecA.Z - akVecB.Z
	float w = akVecA.W - akVecB.W
	return Create4D(x, y, z, w)
EndFunction

Vector2 Function Multiply2D(Vector2 akVecA, Vector2 akVecB) Global
	float x = akVecA.X * akVecB.X
	float y = akVecA.Y * akVecB.Y
	return Create2D(x, y)
EndFunction

Vector3 Function Multiply3D(Vector3 akVecA, Vector3 akVecB) Global
	float x = akVecA.X * akVecB.X
	float y = akVecA.Y * akVecB.Y
	float z = akVecA.Z * akVecB.Z
	return Create3D(x, y, z)
EndFunction

Vector4 Function Multiply4D(Vector4 akVecA, Vector4 akVecB) Global
	float x = akVecA.X * akVecB.X
	float y = akVecA.Y * akVecB.Y
	float z = akVecA.Z * akVecB.Z
	float w = akVecA.W * akVecB.W
	return Create4D(x, y, z, w)
EndFunction

Vector2 Function Divide2D(Vector2 akVecA, Vector2 akVecB) Global
	float x = akVecA.X / akVecB.X
	float y = akVecA.Y / akVecB.Y
	return Create2D(x, y)
EndFunction

Vector3 Function Divide3D(Vector3 akVecA, Vector3 akVecB) Global
	float x = akVecA.X / akVecB.X
	float y = akVecA.Y / akVecB.Y
	float z = akVecA.Z / akVecB.Z
	return Create3D(x, y, z)
EndFunction

Vector4 Function Divide4D(Vector4 akVecA, Vector4 akVecB) Global
	float x = akVecA.X / akVecB.X
	float y = akVecA.Y / akVecB.Y
	float z = akVecA.Z / akVecB.Z
	float w = akVecA.W / akVecB.W
	return Create4D(x, y, z, w)
EndFunction

Vector2 Function MultiplyScalar2D(Vector2 akVec, float afScalar) Global
	float x = akVec.X * afScalar
	float y = akVec.Y * afScalar
	return Create2D(x, y)
EndFunction

Vector3 Function MultiplyScalar3D(Vector3 akVec, float afScalar) Global
	float x = akVec.X * afScalar
	float y = akVec.Y * afScalar
	float z = akVec.Z * afScalar
	return Create3D(x, y, z)
EndFunction

Vector4 Function MultiplyScalar4D(Vector4 akVec, float afScalar) Global
	float x = akVec.X * afScalar
	float y = akVec.Y * afScalar
	float z = akVec.Z * afScalar
	float w = akVec.W * afScalar
	return Create4D(x, y, z, w)
EndFunction

Vector2 Function DivideScalar2D(Vector2 akVec, float afScalar) Global
	float x = akVec.X / afScalar
	float y = akVec.Y / afScalar
	return Create2D(x, y)
EndFunction

Vector3 Function DivideScalar3D(Vector3 akVec, float afScalar) Global
	float x = akVec.X / afScalar
	float y = akVec.Y / afScalar
	float z = akVec.Z / afScalar
	return Create3D(x, y, z)
EndFunction

Vector4 Function DivideScalar4D(Vector4 akVec, float afScalar) Global
	float x = akVec.X / afScalar
	float y = akVec.Y / afScalar
	float z = akVec.Z / afScalar
	float w = akVec.W / afScalar
	return Create4D(x, y, z, w)
EndFunction


float Function Length2D(Vector2 akVec) Global
	float x = akVec.X
	float y = akVec.Y
	return System:Math.Sqrt(x * x + y * y)
EndFunction

float Function Length3D(Vector3 akVec) Global
	float x = akVec.X
	float y = akVec.Y
	float z = akVec.Z
	return System:Math.Sqrt(x * x + y * y + z * z)
EndFunction

float Function Length4D(Vector4 akVec) Global
	float x = akVec.X
	float y = akVec.Y
	float z = akVec.Z
	float w = akVec.W
	return System:Math.Sqrt(x * x + y * y + z * z + w * w)
EndFunction

float Function LengthSquared2D(Vector2 akVec) Global
	float x = akVec.X
	float y = akVec.Y
	return x * x + y * y
EndFunction

float Function LengthSquared3D(Vector3 akVec) Global
	float x = akVec.X
	float y = akVec.Y
	float z = akVec.Z
	return x * x + y * y + z * z
EndFunction

float Function LengthSquared4D(Vector4 akVec) Global
	float x = akVec.X
	float y = akVec.Y
	float z = akVec.Z
	float w = akVec.W
	return x * x + y * y + z * z + w * w
EndFunction

float Function Distance2D(Vector2 akVecA, Vector2 akVecB) Global
	float x = akVecA.X - akVecB.X
	float y = akVecA.Y - akVecB.Y
	return System:Math.Sqrt(x * x + y * y)
EndFunction

float Function Distance3D(Vector3 akVecA, Vector3 akVecB) Global
	float x = akVecA.X - akVecB.X
	float y = akVecA.Y - akVecB.Y
	float z = akVecA.Z - akVecB.Z
	return System:Math.Sqrt(x * x + y * y + z * z)
EndFunction

float Function Distance4D(Vector4 akVecA, Vector4 akVecB) Global
	float x = akVecA.X - akVecB.X
	float y = akVecA.Y - akVecB.Y
	float z = akVecA.Z - akVecB.Z
	float w = akVecA.W - akVecB.W
	return System:Math.Sqrt(x * x + y * y + z * z + w * w)
EndFunction

float Function Dot2D(Vector2 akVecA, Vector2 akVecB) Global
	float x = akVecA.X * akVecB.X
	float y = akVecA.Y * akVecB.Y
	return x + y
EndFunction

float Function Dot3D(Vector3 akVecA, Vector3 akVecB) Global
	float x = akVecA.X * akVecB.X
	float y = akVecA.Y * akVecB.Y
	float z = akVecA.Z * akVecB.Z
	return x + y + z
EndFunction

float Function Dot4D(Vector4 akVecA, Vector4 akVecB) Global
	float x = akVecA.X * akVecB.X
	float y = akVecA.Y * akVecB.Y
	float z = akVecA.Z * akVecB.Z
	float w = akVecA.W * akVecB.W
	return x + y + z + w
EndFunction

float Function Angle2D(Vector2 akVecA, Vector2 akVecB) Global
	float dot = Dot2D(akVecA, akVecB)
	float lenA = Length2D(akVecA)
	float lenB = Length2D(akVecB)
	return System:Math.Acos(dot / (lenA * lenB))
EndFunction

float Function Angle3D(Vector3 akVecA, Vector3 akVecB) Global
	float dot = Dot3D(akVecA, akVecB)
	float lenA = Length3D(akVecA)
	float lenB = Length3D(akVecB)
	return System:Math.Acos(dot / (lenA * lenB))
EndFunction

float Function Angle4D(Vector4 akVecA, Vector4 akVecB) Global
	float dot = Dot4D(akVecA, akVecB)
	float lenA = Length4D(akVecA)
	float lenB = Length4D(akVecB)
	return System:Math.Acos(dot / (lenA * lenB))
EndFunction

float[] Function ToArray2D(Vector2 akVec) Global
	float[] afArray = new float[2]
	afArray[0] = akVec.X
	afArray[1] = akVec.Y
	return afArray
EndFunction

float[] Function ToArray3D(Vector3 akVec) Global
	float[] afArray = new float[3]
	afArray[0] = akVec.X
	afArray[1] = akVec.Y
	afArray[2] = akVec.Z
	return afArray
EndFunction

float[] Function ToArray4D(Vector4 akVec) Global
	float[] afArray = new float[4]
	afArray[0] = akVec.X
	afArray[1] = akVec.Y
	afArray[2] = akVec.Z
	afArray[3] = akVec.W
	return afArray
EndFunction


Vector2 Function Negate2D(Vector2 akVec) Global
	float x = -akVec.X
	float y = -akVec.Y
	return Create2D(x, y)
EndFunction

Vector3 Function Negate3D(Vector3 akVec) Global
	float x = -akVec.X
	float y = -akVec.Y
	float z = -akVec.Z
	return Create3D(x, y, z)
EndFunction

Vector4 Function Negate4D(Vector4 akVec) Global
	float x = -akVec.X
	float y = -akVec.Y
	float z = -akVec.Z
	float w = -akVec.W
	return Create4D(x, y, z, w)
EndFunction

Vector2 Function Min2D(Vector2 akVecA, Vector2 akVecB) Global
	float x = System:Math.MinF(akVecA.X, akVecB.X)
	float y = System:Math.MinF(akVecA.Y, akVecB.Y)
	return Create2D(x, y)
EndFunction

Vector3 Function Min3D(Vector3 akVecA, Vector3 akVecB) Global
	float x = System:Math.MinF(akVecA.X, akVecB.X)
	float y = System:Math.MinF(akVecA.Y, akVecB.Y)
	float z = System:Math.MinF(akVecA.Z, akVecB.Z)
	return Create3D(x, y, z)
EndFunction

Vector4 Function Min4D(Vector4 akVecA, Vector4 akVecB) Global
	float x = System:Math.MinF(akVecA.X, akVecB.X)
	float y = System:Math.MinF(akVecA.Y, akVecB.Y)
	float z = System:Math.MinF(akVecA.Z, akVecB.Z)
	float w = System:Math.MinF(akVecA.W, akVecB.W)
	return Create4D(x, y, z, w)
EndFunction

Vector2 Function Max2D(Vector2 akVecA, Vector2 akVecB) Global
	float x = System:Math.MaxF(akVecA.X, akVecB.X)
	float y = System:Math.MaxF(akVecA.Y, akVecB.Y)
	return Create2D(x, y)
EndFunction

Vector3 Function Max3D(Vector3 akVecA, Vector3 akVecB) Global
	float x = System:Math.MaxF(akVecA.X, akVecB.X)
	float y = System:Math.MaxF(akVecA.Y, akVecB.Y)
	float z = System:Math.MaxF(akVecA.Z, akVecB.Z)
	return Create3D(x, y, z)
EndFunction

Vector4 Function Max4D(Vector4 akVecA, Vector4 akVecB) Global
	float x = System:Math.MaxF(akVecA.X, akVecB.X)
	float y = System:Math.MaxF(akVecA.Y, akVecB.Y)
	float z = System:Math.MaxF(akVecA.Z, akVecB.Z)
	float w = System:Math.MaxF(akVecA.W, akVecB.W)
	return Create4D(x, y, z, w)
EndFunction

Vector2 Function Clamp2D(Vector2 akVec, Vector2 akMin, Vector2 akMax) Global
	float x = System:Math.ClampF(akVec.X, akMin.X, akMax.X)
	float y = System:Math.ClampF(akVec.Y, akMin.Y, akMax.Y)
	return Create2D(x, y)
EndFunction

Vector3 Function Clamp3D(Vector3 akVec, Vector3 akMin, Vector3 akMax) Global
	float x = System:Math.ClampF(akVec.X, akMin.X, akMax.X)
	float y = System:Math.ClampF(akVec.Y, akMin.Y, akMax.Y)
	float z = System:Math.ClampF(akVec.Z, akMin.Z, akMax.Z)
	return Create3D(x, y, z)
EndFunction

Vector4 Function Clamp4D(Vector4 akVec, Vector4 akMin, Vector4 akMax) Global
	float x = System:Math.ClampF(akVec.X, akMin.X, akMax.X)
	float y = System:Math.ClampF(akVec.Y, akMin.Y, akMax.Y)
	float z = System:Math.ClampF(akVec.Z, akMin.Z, akMax.Z)
	float w = System:Math.ClampF(akVec.W, akMin.W, akMax.W)
	return Create4D(x, y, z, w)
EndFunction

Vector2 Function Normalize2D(Vector2 akVec) Global
	float x = akVec.X
	float y = akVec.Y
	float len = System:Math.Sqrt(x * x + y * y)
	return Create2D(x / len, y / len)
EndFunction

Vector3 Function Normalize3D(Vector3 akVec) Global
	float x = akVec.X
	float y = akVec.Y
	float z = akVec.Z
	float len = System:Math.Sqrt(x * x + y * y + z * z)
	return Create3D(x / len, y / len, z / len)
EndFunction

Vector4 Function Normalize4D(Vector4 akVec) Global
	float x = akVec.X
	float y = akVec.Y
	float z = akVec.Z
	float w = akVec.W
	float len = System:Math.Sqrt(x * x + y * y + z * z + w * w)
	return Create4D(x / len, y / len, z / len, w / len)
EndFunction

Vector2 Function Lerp2D(Vector2 akVecA, Vector2 akVecB, float afT) Global
	float x = akVecA.X + (akVecB.X - akVecA.X) * afT
	float y = akVecA.Y + (akVecB.Y - akVecA.Y) * afT
	return Create2D(x, y)
EndFunction

Vector3 Function Lerp3D(Vector3 akVecA, Vector3 akVecB, float afT) Global
	float x = akVecA.X + (akVecB.X - akVecA.X) * afT
	float y = akVecA.Y + (akVecB.Y - akVecA.Y) * afT
	float z = akVecA.Z + (akVecB.Z - akVecA.Z) * afT
	return Create3D(x, y, z)
EndFunction

Vector4 Function Lerp4D(Vector4 akVecA, Vector4 akVecB, float afT) Global
	float x = akVecA.X + (akVecB.X - akVecA.X) * afT
	float y = akVecA.Y + (akVecB.Y - akVecA.Y) * afT
	float z = akVecA.Z + (akVecB.Z - akVecA.Z) * afT
	float w = akVecA.W + (akVecB.W - akVecA.W) * afT
	return Create4D(x, y, z, w)
EndFunction

Vector2 Function Project2D(Vector2 akVecA, Vector2 akVecB) Global
	float dot = Dot2D(akVecA, akVecB)
	float len = LengthSquared2D(akVecB)
	return MultiplyScalar2D(akVecB, dot / len)
EndFunction

Vector3 Function Project3D(Vector3 akVecA, Vector3 akVecB) Global
	float dot = Dot3D(akVecA, akVecB)
	float len = LengthSquared3D(akVecB)
	return MultiplyScalar3D(akVecB, dot / len)
EndFunction

Vector4 Function Project4D(Vector4 akVecA, Vector4 akVecB) Global
	float dot = Dot4D(akVecA, akVecB)
	float len = LengthSquared4D(akVecB)
	return MultiplyScalar4D(akVecB, dot / len)
EndFunction

Vector2 Function Reflect2D(Vector2 akVec, Vector2 akNormal) Global
	float dot = Dot2D(akVec, akNormal)
	float x = akVec.X - 2.0 * dot * akNormal.X
	float y = akVec.Y - 2.0 * dot * akNormal.Y
	return Create2D(x, y)
EndFunction

Vector3 Function Reflect3D(Vector3 akVec, Vector3 akNormal) Global
	float dot = Dot3D(akVec, akNormal)
	float x = akVec.X - 2.0 * dot * akNormal.X
	float y = akVec.Y - 2.0 * dot * akNormal.Y
	float z = akVec.Z - 2.0 * dot * akNormal.Z
	return Create3D(x, y, z)
EndFunction

Vector4 Function Reflect4D(Vector4 akVec, Vector4 akNormal) Global
	float dot = Dot4D(akVec, akNormal)
	float x = akVec.X - 2.0 * dot * akNormal.X
	float y = akVec.Y - 2.0 * dot * akNormal.Y
	float z = akVec.Z - 2.0 * dot * akNormal.Z
	float w = akVec.W - 2.0 * dot * akNormal.W
	return Create4D(x, y, z, w)
EndFunction

Vector3 Function Cross3D(Vector3 akVecA, Vector3 akVecB) Global
	float x = akVecA.Y * akVecB.Z - akVecA.Z * akVecB.Y
	float y = akVecA.Z * akVecB.X - akVecA.X * akVecB.Z
	float z = akVecA.X * akVecB.Y - akVecA.Y * akVecB.X
	return Create3D(x, y, z)
EndFunction
