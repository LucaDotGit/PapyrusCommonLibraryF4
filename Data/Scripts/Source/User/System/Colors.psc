Scriptname System:Colors Const Hidden

;/
	Provides shared data for colors.
/;

Struct Color
	int Red
	int Green
	int Blue
	int Alpha
EndStruct

Color Function Create(int aiRed = 0, int aiGreen = 0, int aiBlue = 0, int aiAlpha = 0) Global
	Color color = new Color
	color.Red = aiRed
	color.Green = aiGreen
	color.Blue = aiBlue
	color.Alpha = aiAlpha
	return color
EndFunction

Color Function FromArgb(int auHex) Global
	int a = System:Operator.AND(System:Operator.RShift(auHex, 24), 0xFF)
	int r = System:Operator.AND(System:Operator.RShift(auHex, 16), 0xFF)
	int g = System:Operator.AND(System:Operator.RShift(auHex, 8), 0xFF)
	int b = System:Operator.AND(auHex, 0xFF)
	return Create(r, g, b, a)
EndFunction

Color Function FromRgb(int aiHex) Global
	int r = System:Operator.AND(System:Operator.RShift(aiHex, 16), 0xFF)
	int g = System:Operator.AND(System:Operator.RShift(aiHex, 8), 0xFF)
	int b = System:Operator.AND(aiHex, 0xFF)
	return Create(r, g, b)
EndFunction

int Function ToArgb(Color akColor) Global
	int argb = 0
	argb += System:Operator.LShift(akColor.Alpha, 24)
	argb += System:Operator.LShift(akColor.Red, 16)
	argb += System:Operator.LShift(akColor.Green, 8)
	argb += akColor.Blue
	return argb
EndFunction

int Function ToRgb(Color akColor) Global
	int rgb = 0
	rgb += System:Operator.LShift(akColor.Red, 16)
	rgb += System:Operator.LShift(akColor.Green, 8)
	rgb += akColor.Blue
	return rgb
EndFunction

Color Function FromHexString(string asColor) Global
	If (System:Strings.Size(asColor) == 8)
		int argb = System:UInt32.TryParse(asColor, aiBase = 16)
		return FromArgb(argb)
	EndIf

	int rgb = System:Int32.TryParse(asColor, aiBase = 16)
	return FromRgb(rgb)
EndFunction

string Function ToArgbString(Color akColor) Global
	int argb = ToArgb(akColor)
	return System:UInt32.ToString(argb, "{:08X}")
EndFunction

string Function ToRgbString(Color akColor) Global
	int rgb = ToRgb(akColor)
	return System:Int32.ToString(rgb, "{:06X}")
EndFunction