#pragma once

namespace System::NetImmerse
{
	static constexpr auto SCRIPT_NAME = "System:NetImmerse"sv;

	static constexpr auto ROWS0_KEY = "Row0"sv;
	static constexpr auto ROWS1_KEY = "Row1"sv;
	static constexpr auto ROWS2_KEY = "Row2"sv;
	static constexpr auto ROWS3_KEY = "Row3"sv;

	static constexpr auto ROTATION_KEY = "Rotation"sv;
	static constexpr auto POSITION_KEY = "Position"sv;
	static constexpr auto SCALE_KEY = "Scale"sv;

	using NiMatrix3x4 = RE::BSScript::structure_wrapper<"System:NetImmerse", "NiMatrix3x4">;
	using NiTransform = RE::BSScript::structure_wrapper<"System:NetImmerse", "NiTransform">;

	static void UpdateNode(RE::NiAVObject* a_node)
	{
		if (!a_node) {
			return;
		}

		F4SE::GetTaskInterface()->AddTask([&]() {
			auto updateData = RE::NiUpdateData();
			a_node->UpdateWorldData(&updateData);
		});
	}

	static bool ContainsNode(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		bool a_firstPerson)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* root = a_ref->Get3D(a_firstPerson);
		return root && root->GetObjectByName(a_nodeName);
	}

	static std::vector<RE::BSFixedString> GetChildrenNames(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		bool a_firstPerson)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto* root = a_ref->Get3D(a_firstPerson);
		if (!root) {
			return {};
		}

		auto* node = RE::fallout_cast<RE::NiNode*>(root);
		if (!node) {
			return {};
		}

		const auto& nodeChildren = node->children;

		auto children = std::vector<RE::BSFixedString>();
		children.reserve(nodeChildren.size());

		for (const auto& child : nodeChildren) {
			children.push_back(child->name);
		}

		return children;
	}

	static RE::BSFixedString GetNodeParentName(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		bool a_firstPerson)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto* root = a_ref->Get3D(a_firstPerson);
		if (!root) {
			return {};
		}

		auto* node = root->GetObjectByName(a_nodeName);
		if (!node) {
			return {};
		}

		auto* parent = node->parent;
		if (!parent) {
			return {};
		}

		return parent->name;
	}

	static std::vector<RE::BSFixedString> GetNodeChildrenNames(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		bool a_firstPerson)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto* root = a_ref->Get3D(a_firstPerson);
		if (!root) {
			return {};
		}

		auto* node = root->GetObjectByName(a_nodeName);
		if (!node) {
			return {};
		}

		auto* object = RE::fallout_cast<RE::NiNode*>(node);
		if (!root) {
			return {};
		}

		const auto& nodeChildren = object->children;

		auto children = std::vector<RE::BSFixedString>();
		children.reserve(nodeChildren.size());

		for (const auto& child : nodeChildren) {
			children.push_back(child->name);
		}

		return children;
	}

	static NiTransform GetNodeTransformImpl(
		const RE::NiTransform& a_transform)
	{
		const auto& transformRotation = a_transform.rotate.entry;

		auto rotation = NiMatrix3x4();
		rotation.insert(ROWS0_KEY, ::Internal::Vectors::MakeVector4(transformRotation[0]));
		rotation.insert(ROWS1_KEY, ::Internal::Vectors::MakeVector4(transformRotation[1]));
		rotation.insert(ROWS2_KEY, ::Internal::Vectors::MakeVector4(transformRotation[2]));
		rotation.insert(ROWS3_KEY, ::Internal::Vectors::MakeVector4(transformRotation[3]));

		auto position = ::Internal::Vectors::MakeVector3(a_transform.translate);

		auto transform = NiTransform();
		transform.insert(ROTATION_KEY, rotation);
		transform.insert(POSITION_KEY, position);
		transform.insert(SCALE_KEY, a_transform.scale);

		return transform;
	}

	static void SetNodeTransformImpl(
		RE::NiAVObject* a_node,
		RE::NiTransform& a_transform,
		const NiTransform& a_value)
	{
		auto& transformRotation = a_transform.rotate;

		auto rotation = a_value.find<NiMatrix3x4>(ROTATION_KEY).value_or(NiMatrix3x4());
		auto position = a_value.find<::Internal::Vectors::Vector3>(POSITION_KEY).value_or(::Internal::Vectors::Vector3());
		auto scale = a_value.find<float>(SCALE_KEY).value();

		const auto setRow = [&](std::uint8_t a_index, std::string_view a_row) noexcept {
			const auto row = rotation.find<::Internal::Vectors::Vector4>(a_row).value_or(::Internal::Vectors::Vector4());
			const auto&& [x, y, z, w] = ::Internal::Vectors::GetVector4(row);
			transformRotation.entry[a_index] = { x, y, z, w };
		};

		setRow(0, ROWS0_KEY);
		setRow(1, ROWS1_KEY);
		setRow(2, ROWS2_KEY);
		setRow(3, ROWS3_KEY);

		const auto&& [x, y, z] = ::Internal::Vectors::GetVector3(position);

		a_transform.translate = { x, y, z };
		a_transform.scale = scale;

		UpdateNode(a_node);
	}

	static NiTransform GetNodeLocalTransform(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		bool a_firstPerson)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		auto* root = a_ref->Get3D(a_firstPerson);
		if (!root) {
			return nullptr;
		}

		const auto* node = root->GetObjectByName(a_nodeName);
		if (!node) {
			return nullptr;
		}

		return GetNodeTransformImpl(node->local);
	}

	static bool SetNodeLocalTransform(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		NiTransform a_transform,
		bool a_firstPerson)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* root = a_ref->Get3D(a_firstPerson);
		if (!root) {
			return false;
		}

		auto* node = root->GetObjectByName(a_nodeName);
		if (!node) {
			return false;
		}

		SetNodeTransformImpl(node, node->local, a_transform);
		return true;
	}

	static NiTransform GetNodeWorldTransform(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		bool a_firstPerson)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		auto* root = a_ref->Get3D(a_firstPerson);
		if (!root) {
			return nullptr;
		}

		const auto* node = root->GetObjectByName(a_nodeName);
		if (!node) {
			return nullptr;
		}

		return GetNodeTransformImpl(node->world);
	}

	static bool SetNodeWorldTransform(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		NiTransform a_transform,
		bool a_firstPerson)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* root = a_ref->Get3D(a_firstPerson);
		if (!root) {
			return false;
		}

		auto* node = root->GetObjectByName(a_nodeName);
		if (!node) {
			return false;
		}

		SetNodeTransformImpl(node, node->world, a_transform);
		return true;
	}

	static ::Internal::Vectors::Vector3 GetRelativeNodePosition(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_leftNodeName,
		RE::BSFixedString a_rightNodeName,
		bool a_firstPerson)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		auto* root = a_ref->Get3D(a_firstPerson);
		if (!root) {
			return nullptr;
		}

		auto* left = root->GetObjectByName(a_leftNodeName);
		if (!left) {
			return nullptr;
		}

		auto* right = root->GetObjectByName(a_rightNodeName);
		if (!right) {
			return nullptr;
		}

		const auto& leftTransform = left->world.translate;
		const auto& rightTransform = right->world.translate;

		const auto x = rightTransform.x - leftTransform.x;
		const auto y = rightTransform.y - leftTransform.y;
		const auto z = rightTransform.z - leftTransform.z;

		return ::Internal::Vectors::MakeVector3(x, y, z);
	}

	static bool ContainsNodeExtraData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		bool a_firstPerson)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* root = a_ref->Get3D(a_firstPerson);
		if (!root) {
			return false;
		}

		auto* node = root->GetObjectByName(a_nodeName);
		if (!node || !node->extra) {
			return false;
		}

		const auto lock = RE::BSAutoLock{ node->extra->lock };
		return node->GetExtraData(a_dataName);
	}

	static std::vector<RE::BSFixedString> GetNodeExtraDataNames(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		bool a_firstPerson)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto* root = a_ref->Get3D(a_firstPerson);
		if (!root) {
			return {};
		}

		auto* node = root->GetObjectByName(a_nodeName);
		if (!node || !node->extra) {
			return {};
		}

		const auto lock = RE::BSAutoLock{ node->extra->lock };

		auto names = std::vector<RE::BSFixedString>();
		names.reserve(node->extra->size());

		for (const auto* data : *node->extra) {
			if (data) {
				names.push_back(data->name);
			}
		}

		return names;
	}

	template <class TExtraData>
	static bool IsNodeExtraDataT(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID,
		RE::TESObjectREFR* a_ref,
		const RE::BSFixedString& a_nodeName,
		const RE::BSFixedString& a_dataName,
		bool a_firstPerson)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* root = a_ref->Get3D(a_firstPerson);
		if (!root) {
			return false;
		}

		const auto* node = root->GetObjectByName(a_nodeName);
		if (!node || !node->extra) {
			return false;
		}

		const auto lock = RE::BSAutoLock{ node->extra->lock };

		const auto* extraData = node->GetExtraData(a_dataName);
		if (!extraData) {
			return false;
		}

		return RE::fallout_cast<const TExtraData*>(extraData) != nullptr;
	}

	template <class TExtraData, typename TResult>
	static TResult GetNodeExtraDataImpl(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID,
		RE::TESObjectREFR* a_ref,
		const RE::BSFixedString& a_nodeName,
		const RE::BSFixedString& a_dataName,
		TResult a_default,
		bool a_firstPerson)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return a_default;
		}

		auto* root = a_ref->Get3D(a_firstPerson);
		if (!root) {
			return a_default;
		}

		const auto* node = root->GetObjectByName(a_nodeName);
		if (!node || !node->extra) {
			return a_default;
		}

		const auto lock = RE::BSAutoLock{ node->extra->lock };

		const auto* extraData = node->GetExtraData(a_dataName);
		if (!extraData) {
			return a_default;
		}

		const auto* extraDataT = RE::fallout_cast<const TExtraData*>(extraData);
		if (!extraDataT) {
			return a_default;
		}

		return extraDataT->data;
	}

	template <class TExtraData, typename TResult>
	static bool SetNodeExtraDataImpl(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID,
		RE::TESObjectREFR* a_ref,
		const RE::BSFixedString& a_nodeName,
		const RE::BSFixedString& a_dataName,
		TResult&& a_value,
		bool a_firstPerson)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* root = a_ref->Get3D(a_firstPerson);
		if (!root) {
			return false;
		}

		auto* node = root->GetObjectByName(a_nodeName);
		if (!node || !node->extra) {
			return false;
		}

		const auto lock = RE::BSAutoLock{ node->extra->lock };

		auto* extraData = node->GetExtraData(a_dataName);
		if (!extraData) {
			return false;
		}

		auto* extraDataT = RE::fallout_cast<TExtraData*>(extraData);
		if (!extraDataT) {
			return false;
		}

		extraDataT->data = a_value;

		UpdateNode(node);
		return true;
	}

	static bool IsNodeExtraDataBool(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		bool a_firstPerson)
	{
		return IsNodeExtraDataT<RE::NiBooleanExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_firstPerson);
	}

	static bool GetNodeExtraDataBool(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		bool a_default,
		bool a_firstPerson)
	{
		return GetNodeExtraDataImpl<RE::NiBooleanExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_default, a_firstPerson);
	}

	static bool SetNodeExtraDataBool(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		bool a_value,
		bool a_firstPerson)
	{
		return SetNodeExtraDataImpl<RE::NiBooleanExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_value, a_firstPerson);
	}

	static bool IsNodeExtraDataInt(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		bool a_firstPerson)
	{
		return IsNodeExtraDataT<RE::NiIntegerExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_firstPerson);
	}

	static std::int32_t GetNodeExtraDataInt(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		std::int32_t a_default,
		bool a_firstPerson)
	{
		return GetNodeExtraDataImpl<RE::NiIntegerExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_default, a_firstPerson);
	}

	static bool SetNodeExtraDataInt(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		std::int32_t a_value,
		bool a_firstPerson)
	{
		return SetNodeExtraDataImpl<RE::NiIntegerExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_value, a_firstPerson);
	}

	static bool IsNodeExtraDataFloat(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		bool a_firstPerson)
	{
		return IsNodeExtraDataT<RE::NiFloatExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_firstPerson);
	}

	static float GetNodeExtraDataFloat(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		float a_default,
		bool a_firstPerson)
	{
		return GetNodeExtraDataImpl<RE::NiFloatExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_default, a_firstPerson);
	}

	static bool SetNodeExtraDataFloat(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		float a_value,
		bool a_firstPerson)
	{
		return SetNodeExtraDataImpl<RE::NiFloatExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_value, a_firstPerson);
	}

	static bool IsNodeExtraDataString(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		bool a_firstPerson)
	{
		return IsNodeExtraDataT<RE::NiStringExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_firstPerson);
	}

	static RE::BSFixedString GetNodeExtraDataString(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		RE::BSFixedString a_default,
		bool a_firstPerson)
	{
		return GetNodeExtraDataImpl<RE::NiStringExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_default, a_firstPerson);
	}

	static bool SetNodeExtraDataString(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		RE::BSFixedString a_value,
		bool a_firstPerson)
	{
		return SetNodeExtraDataImpl<RE::NiStringExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_value, a_firstPerson);
	}

	template <class TExtraData, typename TResult>
	static std::vector<TResult> GetNodeExtraDataArrayImpl(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID,
		RE::TESObjectREFR* a_ref,
		const RE::BSFixedString& a_nodeName,
		const RE::BSFixedString& a_dataName,
		bool a_firstPerson)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		auto* root = a_ref->Get3D(a_firstPerson);
		if (!root) {
			return {};
		}

		const auto* node = root->GetObjectByName(a_nodeName);
		if (!node || !node->extra) {
			return {};
		}

		const auto lock = RE::BSAutoLock{ node->extra->lock };

		const auto* extraData = node->GetExtraData(a_dataName);
		if (!extraData) {
			return {};
		}

		const auto* extraDataT = RE::fallout_cast<const TExtraData*>(extraData);
		if (!extraDataT) {
			return {};
		}

		return { extraDataT->data, extraDataT->data + extraDataT->size };
	}

	template <class TExtraData, typename TResult>
	static bool SetNodeExtraDataArrayImpl(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID,
		RE::TESObjectREFR* a_ref,
		const RE::BSFixedString& a_nodeName,
		const RE::BSFixedString& a_dataName,
		const std::vector<TResult>& a_value,
		bool a_firstPerson)
	{
		if (!a_ref) {
			a_vm.PostError(::Internal::Errors::OBJECT_REFERENCE_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		auto* root = a_ref->Get3D(a_firstPerson);
		if (!root) {
			return false;
		}

		auto* node = root->GetObjectByName(a_nodeName);
		if (!node || !node->extra) {
			return false;
		}

		const auto lock = RE::BSAutoLock{ node->extra->lock };

		auto* extraData = node->GetExtraData(a_dataName);
		if (!extraData) {
			return false;
		}

		auto* extraDataT = RE::fallout_cast<TExtraData*>(extraData);
		if (!extraDataT) {
			return false;
		}

		const auto size = static_cast<std::uint32_t>(a_value.size());

		if (extraDataT->data) {
			RE::NiFree(extraDataT->data);
		}

		auto* data = RE::NiTMallocInterface<TResult>::allocate(size);
		std::ranges::copy(a_value, data);

		extraDataT->data = data;
		extraDataT->size = size;

		UpdateNode(node);
		return true;
	}

	static bool IsNodeExtraDataIntArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		bool a_firstPerson)
	{
		return IsNodeExtraDataT<RE::NiIntegersExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_firstPerson);
	}

	static std::vector<std::int32_t> GetNodeExtraDataIntArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		bool a_firstPerson)
	{
		return GetNodeExtraDataArrayImpl<RE::NiIntegersExtraData, std::int32_t>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_firstPerson);
	}

	static bool SetNodeExtraDataIntArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		std::vector<std::int32_t> a_value,
		bool a_firstPerson)
	{
		return SetNodeExtraDataArrayImpl<RE::NiIntegersExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_value, a_firstPerson);
	}

	static bool IsNodeExtraDataFloatArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		bool a_firstPerson)
	{
		return IsNodeExtraDataT<RE::NiFloatsExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_firstPerson);
	}

	static std::vector<float> GetNodeExtraDataFloatArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		bool a_firstPerson)
	{
		return GetNodeExtraDataArrayImpl<RE::NiFloatsExtraData, float>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_firstPerson);
	}

	static bool SetNodeExtraDataFloatArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		std::vector<float> a_value,
		bool a_firstPerson)
	{
		return SetNodeExtraDataArrayImpl<RE::NiFloatsExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_value, a_firstPerson);
	}

	static bool IsNodeExtraDataStringArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		bool a_firstPerson)
	{
		return IsNodeExtraDataT<RE::NiStringsExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_firstPerson);
	}

	static std::vector<RE::BSFixedString> GetNodeExtraDataStringArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		bool a_firstPerson)
	{
		return GetNodeExtraDataArrayImpl<RE::NiStringsExtraData, RE::BSFixedString>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, a_firstPerson);
	}

	static bool SetNodeExtraDataStringArray(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BSFixedString a_nodeName,
		RE::BSFixedString a_dataName,
		std::vector<RE::BSFixedString> a_value,
		bool a_firstPerson)
	{
		using pointer_t = RE::BSFixedString::pointer;

		auto strings = std::vector<pointer_t>();
		strings.reserve(a_value.size());

		std::ranges::transform(a_value, strings.begin(), [](const RE::BSFixedString& a_string) noexcept {
			return const_cast<pointer_t>(a_string.data());
		});

		return SetNodeExtraDataArrayImpl<RE::NiStringsExtraData>(a_vm, a_stackID, a_ref, a_nodeName, a_dataName, strings, a_firstPerson);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ContainsNode);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetChildrenNames);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetNodeParentName);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetNodeChildrenNames);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetNodeLocalTransform);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetNodeLocalTransform);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetNodeWorldTransform);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetNodeWorldTransform);
		BIND_METHOD(a_vm, SCRIPT_NAME, GetRelativeNodePosition);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ContainsNodeExtraData);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetNodeExtraDataNames);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsNodeExtraDataBool);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetNodeExtraDataBool);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetNodeExtraDataBool);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsNodeExtraDataInt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetNodeExtraDataInt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetNodeExtraDataInt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsNodeExtraDataFloat);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetNodeExtraDataFloat);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetNodeExtraDataFloat);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsNodeExtraDataString);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetNodeExtraDataString);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetNodeExtraDataString);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsNodeExtraDataIntArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetNodeExtraDataIntArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetNodeExtraDataIntArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsNodeExtraDataFloatArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetNodeExtraDataFloatArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetNodeExtraDataFloatArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsNodeExtraDataStringArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetNodeExtraDataStringArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetNodeExtraDataStringArray);

		return true;
	}
}
