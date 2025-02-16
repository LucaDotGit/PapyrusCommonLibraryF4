#pragma once

namespace System::AimModel
{
	static constexpr auto SCRIPT_NAME = "System:AimModel"sv;

	static constexpr auto CONE_MIN_ANGLE_KEY = "ConeMinAngle"sv;
	static constexpr auto CONE_MAX_ANGLE_KEY = "ConeMaxAngle"sv;
	static constexpr auto CONE_INCREASE_PER_SHOT_KEY = "ConeIncreasePerShot"sv;
	static constexpr auto CONE_DECREASE_PER_SEC_KEY = "ConeDecreasePerSec"sv;
	static constexpr auto CONE_DECREASE_DELAY_MS_KEY = "ConeDecreaseDelayMS"sv;
	static constexpr auto CONE_SNEAK_MULT_KEY = "ConeSneakMult"sv;
	static constexpr auto RECOIL_ARC_ANGLE_KEY = "RecoilArcAngle"sv;
	static constexpr auto RECOIL_ARC_ROTATE_ANGLE_KEY = "RecoilArcRotateAngle"sv;
	static constexpr auto RECOIL_MAX_ANGLE_PER_SHOT_KEY = "RecoilMaxAnglePerShot"sv;
	static constexpr auto RECOIL_MIN_ANGLE_PER_SHOT_KEY = "RecoilMinAnglePerShot"sv;
	static constexpr auto RECOIL_DIMINISH_SPRING_FORCE_KEY = "RecoilDiminishSpringForce"sv;
	static constexpr auto RECOIL_DIMINISH_SIGHTS_MULT_KEY = "RecoilDiminishSightsMult"sv;
	static constexpr auto RECOIL_HIP_MULT_KEY = "RecoilHipMult"sv;
	static constexpr auto RUNAWAY_RECOIL_SHOTS_KEY = "RunawayRecoilShots"sv;
	static constexpr auto BASE_STABILITY_KEY = "BaseStability"sv;

	using Data = RE::BSScript::structure_wrapper<"System:AimModel", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSAimModel* a_aimModel)
	{
		if (!a_aimModel) {
			a_vm.PostError(::Internal::Errors::AIM_MODEL_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto& aimModelData = a_aimModel->aimModelData;

		auto data = Data();
		data.insert(CONE_MIN_ANGLE_KEY, aimModelData.aimModelMinConeDegrees);
		data.insert(CONE_MAX_ANGLE_KEY, aimModelData.aimModelMaxConeDegrees);
		data.insert(CONE_INCREASE_PER_SHOT_KEY, aimModelData.aimModelConeIncreasePerShot);
		data.insert(CONE_DECREASE_PER_SEC_KEY, aimModelData.aimModelConeDecreasePerSec);
		data.insert(CONE_DECREASE_DELAY_MS_KEY, aimModelData.aimModelConeDecreaseDelayMs);
		data.insert(CONE_SNEAK_MULT_KEY, aimModelData.aimModelConeSneakMultiplier);
		data.insert(RECOIL_ARC_ANGLE_KEY, aimModelData.aimModelRecoilArcDeg);
		data.insert(RECOIL_ARC_ROTATE_ANGLE_KEY, aimModelData.aimModelRecoilArcRotateDeg);
		data.insert(RECOIL_MAX_ANGLE_PER_SHOT_KEY, aimModelData.aimModelRecoilMaxDegPerShot);
		data.insert(RECOIL_MIN_ANGLE_PER_SHOT_KEY, aimModelData.aimModelRecoilMinDegPerShot);
		data.insert(RECOIL_DIMINISH_SPRING_FORCE_KEY, aimModelData.aimModelRecoilDiminishSpringForce);
		data.insert(RECOIL_DIMINISH_SIGHTS_MULT_KEY, aimModelData.aimModelRecoilDiminishSightsMult);
		data.insert(RECOIL_HIP_MULT_KEY, aimModelData.aimModelRecoilHipMult);
		data.insert(RUNAWAY_RECOIL_SHOTS_KEY, aimModelData.aimModelRecoilShotsForRunaway);
		data.insert(BASE_STABILITY_KEY, aimModelData.aimModelBaseStability);

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSAimModel* a_aimModel,
		Data a_data)
	{
		if (!a_aimModel) {
			a_vm.PostError(::Internal::Errors::AIM_MODEL_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		auto& aimModelData = a_aimModel->aimModelData;

		aimModelData.aimModelMinConeDegrees = a_data.find<float>(CONE_MIN_ANGLE_KEY).value();
		aimModelData.aimModelMaxConeDegrees = a_data.find<float>(CONE_MAX_ANGLE_KEY).value();
		aimModelData.aimModelConeIncreasePerShot = a_data.find<float>(CONE_INCREASE_PER_SHOT_KEY).value();
		aimModelData.aimModelConeDecreasePerSec = a_data.find<float>(CONE_DECREASE_PER_SEC_KEY).value();
		aimModelData.aimModelConeDecreaseDelayMs = a_data.find<std::uint32_t>(CONE_DECREASE_DELAY_MS_KEY).value();
		aimModelData.aimModelConeSneakMultiplier = a_data.find<float>(CONE_SNEAK_MULT_KEY).value();
		aimModelData.aimModelRecoilArcDeg = a_data.find<float>(RECOIL_ARC_ANGLE_KEY).value();
		aimModelData.aimModelRecoilArcRotateDeg = a_data.find<float>(RECOIL_ARC_ROTATE_ANGLE_KEY).value();
		aimModelData.aimModelRecoilMaxDegPerShot = a_data.find<float>(RECOIL_MAX_ANGLE_PER_SHOT_KEY).value();
		aimModelData.aimModelRecoilMinDegPerShot = a_data.find<float>(RECOIL_MIN_ANGLE_PER_SHOT_KEY).value();
		aimModelData.aimModelRecoilDiminishSpringForce = a_data.find<float>(RECOIL_DIMINISH_SPRING_FORCE_KEY).value();
		aimModelData.aimModelRecoilDiminishSightsMult = a_data.find<float>(RECOIL_DIMINISH_SIGHTS_MULT_KEY).value();
		aimModelData.aimModelRecoilHipMult = a_data.find<float>(RECOIL_HIP_MULT_KEY).value();
		aimModelData.aimModelRecoilShotsForRunaway = a_data.find<std::uint32_t>(RUNAWAY_RECOIL_SHOTS_KEY).value();
		aimModelData.aimModelBaseStability = a_data.find<float>(BASE_STABILITY_KEY).value();
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}
