Scriptname System:AimModel Const Hidden Native

;/
	Provides common functions for aim models.
/;

Struct Data
	float ConeMinAngle
	float ConeMaxAngle
	float ConeIncreasePerShot
	float ConeDecreasePerSec
	int ConeDecreaseDelayMS
	float ConeSneakMult
	float RecoilArcAngle
	float RecoilArcRotateAngle
	float RecoilMaxAnglePerShot
	float RecoilMinAnglePerShot
	float RecoilDiminishSpringForce
	float RecoilDiminishSightsMult
	float RecoilHipMult
	int RunawayRecoilShots
	float BaseStability
EndStruct

Data Function GetData(AimModel akAimModel) Global Native
Function SetData(AimModel akAimModel, Data akData) Global Native
