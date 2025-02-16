#pragma once

namespace System::MovementType
{
	static constexpr auto SCRIPT_NAME = "System:MovementType"sv;

	static constexpr auto NAME_KEY = "Name"sv;
	static constexpr auto LEFT_KEY = "Left"sv;
	static constexpr auto RIGHT_KEY = "Right"sv;
	static constexpr auto FORWARD_KEY = "Forward"sv;
	static constexpr auto BACKWARD_KEY = "Backward"sv;
	static constexpr auto PITCH_KEY = "Pitch"sv;
	static constexpr auto ROLL_KEY = "Roll"sv;
	static constexpr auto YAW_KEY = "Yaw"sv;
	static constexpr auto STANDING_KEY = "Standing"sv;
	static constexpr auto WALKING_KEY = "Walking"sv;
	static constexpr auto RUNNING_KEY = "Running"sv;
	static constexpr auto SPRINTING_KEY = "Sprinting"sv;
	static constexpr auto FLOAT_HEIGHT_KEY = "FloatHeight"sv;
	static constexpr auto FLIGHT_ANGLE_GAIN_KEY = "FlightAngleGain"sv;

	using Data = RE::BSScript::structure_wrapper<"System:MovementType", "Data">;
	using Entry = RE::BSScript::structure_wrapper<"System:MovementType", "Entry">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSMovementType* a_movementType)
	{
		if (!a_movementType) {
			a_vm.PostError(::Internal::Errors::MOVEMENT_TYPE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		using MaxSpeeds = RE::Movement::MaxSpeeds;
		using SpeedDirections = RE::Movement::SPEED_DIRECTIONS;

		const auto& movementTypeData = a_movementType->movementTypeData;
		const auto& defaultData = movementTypeData.defaultData;
		const auto& speeds = defaultData.speeds;

		auto data = Data();
		data.insert(NAME_KEY, movementTypeData.typeName);

		const auto createEntry = [](std::span<const float, MaxSpeeds::kTotal> a_speeds) noexcept {
			auto speed = Entry();
			speed.insert(STANDING_KEY, a_speeds[MaxSpeeds::kStanding]);
			speed.insert(WALKING_KEY, a_speeds[MaxSpeeds::kWalking]);
			speed.insert(RUNNING_KEY, a_speeds[MaxSpeeds::kRunning]);
			speed.insert(SPRINTING_KEY, a_speeds[MaxSpeeds::kSprinting]);
			return speed;
		};

		data.insert(LEFT_KEY, createEntry(speeds[SpeedDirections::kLeft]));
		data.insert(RIGHT_KEY, createEntry(speeds[SpeedDirections::kRight]));
		data.insert(FORWARD_KEY, createEntry(speeds[SpeedDirections::kForward]));
		data.insert(BACKWARD_KEY, createEntry(speeds[SpeedDirections::kBackward]));
		data.insert(PITCH_KEY, createEntry(speeds[SpeedDirections::kPitch]));
		data.insert(ROLL_KEY, createEntry(speeds[SpeedDirections::kRoll]));
		data.insert(YAW_KEY, createEntry(speeds[SpeedDirections::kYaw]));

		data.insert(FLOAT_HEIGHT_KEY, movementTypeData.floatHeight);
		data.insert(FLIGHT_ANGLE_GAIN_KEY, movementTypeData.flightAngleGain);

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::BGSMovementType* a_movementType,
		Data a_data)
	{
		if (!a_movementType) {
			a_vm.PostError(::Internal::Errors::MOVEMENT_TYPE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		using MaxSpeeds = RE::Movement::MaxSpeeds;
		using SpeedDirections = RE::Movement::SPEED_DIRECTIONS;

		auto& movementTypeData = a_movementType->movementTypeData;
		auto& defaultData = movementTypeData.defaultData;
		auto& speeds = defaultData.speeds;

		const auto setEntry = [&](std::string_view a_key, std::span<float, MaxSpeeds::kTotal> a_speeds) noexcept {
			const auto entry = a_data.find<Entry>(a_key).value_or(nullptr);

			a_speeds[MaxSpeeds::kStanding] = entry.find<float>(STANDING_KEY).value_or(0.0f);
			a_speeds[MaxSpeeds::kWalking] = entry.find<float>(WALKING_KEY).value_or(0.0f);
			a_speeds[MaxSpeeds::kRunning] = entry.find<float>(RUNNING_KEY).value_or(0.0f);
			a_speeds[MaxSpeeds::kSprinting] = entry.find<float>(SPRINTING_KEY).value_or(0.0f);
		};

		movementTypeData.typeName = a_data.find<RE::BSFixedString>(NAME_KEY).value();

		setEntry(LEFT_KEY, speeds[SpeedDirections::kLeft]);
		setEntry(RIGHT_KEY, speeds[SpeedDirections::kRight]);
		setEntry(FORWARD_KEY, speeds[SpeedDirections::kForward]);
		setEntry(BACKWARD_KEY, speeds[SpeedDirections::kBackward]);
		setEntry(PITCH_KEY, speeds[SpeedDirections::kPitch]);
		setEntry(ROLL_KEY, speeds[SpeedDirections::kRoll]);
		setEntry(YAW_KEY, speeds[SpeedDirections::kYaw]);

		movementTypeData.floatHeight = a_data.find<float>(FLOAT_HEIGHT_KEY).value();
		movementTypeData.flightAngleGain = a_data.find<float>(FLIGHT_ANGLE_GAIN_KEY).value();
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}
