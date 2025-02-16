#include "Internal/Bethesda/Comparer.hpp"

namespace Internal::Comparer
{
	std::strong_ordering Compare(
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right)
	{
		if (a_left == a_right) {
			return std::strong_ordering::equal;
		}

		if (!a_left || !a_right ||
			!*a_left || !*a_right) {
			return CompareValue(a_left, a_right);
		}

		const auto leftType = a_left->GetType().GetRawType();
		const auto rightType = a_right->GetType().GetRawType();

		const auto isLeftVar = leftType == RE::BSScript::TypeInfo::RawType::kVar;
		const auto isRightVar = rightType == RE::BSScript::TypeInfo::RawType::kVar;

		if (isLeftVar && isRightVar) {
			const auto* left = RE::BSScript::get<RE::BSScript::Variable>(*a_left);
			const auto* right = RE::BSScript::get<RE::BSScript::Variable>(*a_right);

			return Compare(left, right);
		}

		if (isLeftVar) {
			const auto* left = RE::BSScript::get<RE::BSScript::Variable>(*a_left);
			return Compare(left, a_right);
		}

		if (isRightVar) {
			const auto* right = RE::BSScript::get<RE::BSScript::Variable>(*a_right);
			return Compare(a_left, right);
		}

		if (leftType != rightType &&
			leftType != RE::BSScript::TypeInfo::RawType::kArrayVar &&
			rightType != RE::BSScript::TypeInfo::RawType::kArrayVar) {
			return std::strong_ordering::less;
		}

		switch (leftType) {
			case RE::BSScript::TypeInfo::RawType::kBool: {
				const auto left = RE::BSScript::get<bool>(*a_left);
				const auto right = RE::BSScript::get<bool>(*a_right);

				return CompareValue(left, right);
			}
			case RE::BSScript::TypeInfo::RawType::kInt: {
				const auto left = RE::BSScript::get<std::int32_t>(*a_left);
				const auto right = RE::BSScript::get<std::int32_t>(*a_right);

				return CompareValue(left, right);
			}
			case RE::BSScript::TypeInfo::RawType::kFloat: {
				const auto left = RE::BSScript::get<float>(*a_left);
				const auto right = RE::BSScript::get<float>(*a_right);

				return CompareValue(left, right);
			}
			case RE::BSScript::TypeInfo::RawType::kString: {
				const auto left = RE::BSScript::get<RE::BSFixedString>(*a_left);
				const auto right = RE::BSScript::get<RE::BSFixedString>(*a_right);

				return CompareString(left, right);
			}
			case RE::BSScript::TypeInfo::RawType::kObject: {
				const auto left = RE::BSScript::get<RE::BSScript::Object>(*a_left);
				const auto right = RE::BSScript::get<RE::BSScript::Object>(*a_right);

				return CompareObject(left, right);
			}
			case RE::BSScript::TypeInfo::RawType::kStruct: {
				const auto left = RE::BSScript::get<RE::BSScript::Struct>(*a_left);
				const auto right = RE::BSScript::get<RE::BSScript::Struct>(*a_right);

				return CompareStruct(left, right);
			}
			case RE::BSScript::TypeInfo::RawType::kArrayBool:
			case RE::BSScript::TypeInfo::RawType::kArrayInt:
			case RE::BSScript::TypeInfo::RawType::kArrayFloat:
			case RE::BSScript::TypeInfo::RawType::kArrayString:
			case RE::BSScript::TypeInfo::RawType::kArrayObject:
			case RE::BSScript::TypeInfo::RawType::kArrayStruct:
			case RE::BSScript::TypeInfo::RawType::kArrayVar: {
				const auto left = RE::BSScript::get<RE::BSScript::Array>(*a_left);
				const auto right = RE::BSScript::get<RE::BSScript::Array>(*a_right);

				return CompareArray(left, right);
			}
			default: {
				return std::strong_ordering::less;
			}
		}
	}

	bool Equals(
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right)
	{
		return Compare(a_left, a_right) == std::strong_ordering::equal;
	}

	bool IsLessThan(
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right)
	{
		return Compare(a_left, a_right) < 0;
	}

	bool IsLessThanOrEqual(
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right)
	{
		return Compare(a_left, a_right) <= 0;
	}

	bool IsGreaterThan(
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right)
	{
		return Compare(a_left, a_right) > 0;
	}

	bool IsGreaterThanOrEqual(
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right)
	{
		return Compare(a_left, a_right) >= 0;
	}

	bool IsInRange(
		const RE::BSScript::Variable* a_value,
		const RE::BSScript::Variable* a_min,
		const RE::BSScript::Variable* a_max)
	{
		return IsGreaterThanOrEqual(a_value, a_min) &&
			   IsLessThanOrEqual(a_value, a_max);
	}

	[[nodiscard]] std::strong_ordering CompareForm(
		const RE::TESForm* a_left,
		const RE::TESForm* a_right) noexcept
	{
		if (a_left == a_right) {
			return std::strong_ordering::equal;
		}

		if (!a_left || !a_right) {
			return CompareValue(a_left, a_right);
		}

		return CompareValue(a_left->formID, a_right->formID);
	}

	std::strong_ordering CompareObject(
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_left,
		const RE::BSTSmartPointer<RE::BSScript::Object>& a_right) noexcept
	{
		if (a_left == a_right) {
			return std::strong_ordering::equal;
		}

		if (!a_left || !a_right) {
			return CompareValue(a_left.get(), a_right.get());
		}

		const auto leftHandle = a_left->handle;
		const auto rightHandle = a_right->handle;

		return CompareValue(leftHandle, rightHandle);
	}

	std::strong_ordering CompareStruct(
		const RE::BSTSmartPointer<RE::BSScript::Struct>& a_left,
		const RE::BSTSmartPointer<RE::BSScript::Struct>& a_right)
	{
		if (a_left == a_right) {
			return std::strong_ordering::equal;
		}

		if (!a_left || !a_right) {
			return CompareValue(a_left.get(), a_right.get());
		}

		const auto& leftType = a_left->type;
		if (!leftType) {
			return std::strong_ordering::less;
		}

		const auto& rightType = a_right->type;
		if (!rightType) {
			return std::strong_ordering::greater;
		}

		if (leftType != rightType) {
			return std::strong_ordering::less;
		}

		const auto leftLock = RE::BSAutoLock{ a_left->structLock };
		const auto rightLock = RE::BSAutoLock{ a_right->structLock };

		const auto size = a_left->type->variables.size();

		for (auto i = 0ui32; i < size; i++) {
			const auto* leftVar = &a_left->variables[i];
			const auto* rightVar = &a_right->variables[i];

			const auto comparison = Compare(leftVar, rightVar);
			if (comparison != std::strong_ordering::equal) {
				return comparison;
			}
		}

		return std::strong_ordering::equal;
	}

	std::strong_ordering CompareArray(
		const RE::BSTSmartPointer<RE::BSScript::Array>& a_left,
		const RE::BSTSmartPointer<RE::BSScript::Array>& a_right)
	{
		if (a_left == a_right) {
			return std::strong_ordering::equal;
		}

		if (!a_left || !a_right) {
			return CompareValue(a_left.get(), a_right.get());
		}

		const auto leftType = a_left->elementType.GetRawType();
		const auto rightType = a_right->elementType.GetRawType();

		if (leftType != rightType &&
			leftType != RE::BSScript::TypeInfo::RawType::kVar &&
			rightType != RE::BSScript::TypeInfo::RawType::kVar) {
			return std::strong_ordering::less;
		}

		const auto leftLock = RE::BSAutoLock{ a_left->elementsLock };
		const auto rightLock = RE::BSAutoLock{ a_right->elementsLock };

		const auto leftSize = a_left->size();
		const auto rightSize = a_right->size();

		if (leftSize != rightSize) {
			return CompareValue(leftSize, rightSize);
		}

		for (auto i = 0ui32; i < leftSize; i++) {
			const auto* leftVar = &a_left->elements[i];
			const auto* rightVar = &a_right->elements[i];

			const auto comparison = Compare(leftVar, rightVar);
			if (comparison != std::strong_ordering::equal) {
				return comparison;
			}
		}

		return std::strong_ordering::equal;
	}

	bool RefEquals(
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right)
	{
		if (a_left == a_right) {
			return true;
		}

		if (!a_left || !a_right ||
			!*a_left || !*a_right) {
			return false;
		}

		const auto leftType = a_left->GetType().GetRawType();
		const auto rightType = a_right->GetType().GetRawType();

		const auto isLeftVar = leftType == RE::BSScript::TypeInfo::RawType::kVar;
		const auto isRightVar = rightType == RE::BSScript::TypeInfo::RawType::kVar;

		if (isLeftVar && isRightVar) {
			const auto* left = RE::BSScript::get<RE::BSScript::Variable>(*a_left);
			const auto* right = RE::BSScript::get<RE::BSScript::Variable>(*a_right);

			return RefEquals(left, right);
		}

		if (isLeftVar) {
			const auto* left = RE::BSScript::get<RE::BSScript::Variable>(*a_left);
			return RefEquals(left, a_right);
		}

		if (isRightVar) {
			const auto* right = RE::BSScript::get<RE::BSScript::Variable>(*a_right);
			return RefEquals(a_left, right);
		}

		if (leftType != rightType &&
			leftType != RE::BSScript::TypeInfo::RawType::kArrayVar &&
			rightType != RE::BSScript::TypeInfo::RawType::kArrayVar) {
			return false;
		}

		switch (leftType) {
			case RE::BSScript::TypeInfo::RawType::kString: {
				const auto left = RE::BSScript::get<RE::BSFixedString>(*a_left);
				const auto right = RE::BSScript::get<RE::BSFixedString>(*a_right);

				return left == right;
			}
			case RE::BSScript::TypeInfo::RawType::kObject: {
				const auto left = RE::BSScript::get<RE::BSScript::Object>(*a_left);
				const auto right = RE::BSScript::get<RE::BSScript::Object>(*a_right);

				return left == right;
			}
			case RE::BSScript::TypeInfo::RawType::kStruct: {
				const auto left = RE::BSScript::get<RE::BSScript::Struct>(*a_left);
				const auto right = RE::BSScript::get<RE::BSScript::Struct>(*a_right);

				return left == right;
			}
			case RE::BSScript::TypeInfo::RawType::kArrayBool:
			case RE::BSScript::TypeInfo::RawType::kArrayInt:
			case RE::BSScript::TypeInfo::RawType::kArrayFloat:
			case RE::BSScript::TypeInfo::RawType::kArrayString:
			case RE::BSScript::TypeInfo::RawType::kArrayObject:
			case RE::BSScript::TypeInfo::RawType::kArrayStruct:
			case RE::BSScript::TypeInfo::RawType::kArrayVar: {
				const auto left = RE::BSScript::get<RE::BSScript::Array>(*a_left);
				const auto right = RE::BSScript::get<RE::BSScript::Array>(*a_right);

				return left == right;
			}
			default: {
				return false;
			}
		}
	}

	bool TypeEquals(
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right)
	{
		if (a_left == a_right) {
			return true;
		}

		if (!a_left && !a_right ||
			!*a_left && !*a_right) {
			return true;
		}

		if (!a_left || !a_right ||
			!*a_left || !*a_right) {
			return false;
		}

		const auto leftType = a_left->GetType();
		const auto rightType = a_right->GetType();

		const auto leftRawType = leftType.GetRawType();
		const auto rightRawType = rightType.GetRawType();

		const auto isLeftVar = leftRawType == RE::BSScript::TypeInfo::RawType::kVar;
		const auto isRightVar = rightRawType == RE::BSScript::TypeInfo::RawType::kVar;

		if (isLeftVar && isRightVar) {
			const auto* left = RE::BSScript::get<RE::BSScript::Variable>(*a_left);
			const auto* right = RE::BSScript::get<RE::BSScript::Variable>(*a_right);

			return TypeEquals(left, right);
		}

		return TypeEquals(leftType, rightType);
	}

	bool TypeEquals(
		const RE::BSScript::TypeInfo& a_left,
		const RE::BSScript::TypeInfo& a_right)
	{
		const auto leftRawType = a_left.GetRawType();
		const auto rightRawType = a_right.GetRawType();

		if (leftRawType != rightRawType) {
			return false;
		}

		const auto* leftComplexType = a_left.GetComplexType();
		const auto* rightComplexType = a_right.GetComplexType();

		return leftComplexType == rightComplexType;
	}

	RE::BSScript::TypeInfo::RawType GetRawType(const RE::BSScript::Variable* a_var)
	{
		if (!a_var) {
			return RE::BSScript::TypeInfo::RawType::kNone;
		}

		if (a_var->is<RE::BSScript::Variable>()) {
			const auto* var = RE::BSScript::get<RE::BSScript::Variable>(*a_var);
			return GetRawType(var);
		}

		return a_var->GetType().GetRawType();
	}
}
