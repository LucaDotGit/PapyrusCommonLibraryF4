#pragma once

namespace Internal::Vectors
{
	using Vector2 = RE::BSScript::structure_wrapper<"System:Vectors", "Vector2">;
	using Vector3 = RE::BSScript::structure_wrapper<"System:Vectors", "Vector3">;
	using Vector4 = RE::BSScript::structure_wrapper<"System:Vectors", "Vector4">;

	[[nodiscard]] Vector2 MakeVector2(float a_x = 0.0f, float a_y = 0.0f) noexcept;
	[[nodiscard]] Vector2 MakeVector2(std::span<float, 2> a_span) noexcept;
	[[nodiscard]] Vector2 MakeVector2(const RE::NiPoint2& a_point) noexcept;

	[[nodiscard]] Vector3 MakeVector3(float a_x = 0.0f, float a_y = 0.0f, float a_z = 0.0f) noexcept;
	[[nodiscard]] Vector3 MakeVector3(std::span<float, 3> a_span) noexcept;
	[[nodiscard]] Vector3 MakeVector3(const RE::NiPoint3& a_point) noexcept;

	[[nodiscard]] Vector4 MakeVector4(float a_x = 0.0f, float a_y = 0.0f, float a_z = 0.0f, float a_w = 0.0f) noexcept;
	[[nodiscard]] Vector4 MakeVector4(std::span<float, 4> a_span) noexcept;
	[[nodiscard]] Vector4 MakeVector4(const RE::NiPoint4& a_point) noexcept;

	[[nodiscard]] std::tuple<float, float> GetVector2(const Vector2& a_vector) noexcept;
	bool SetVector2(Vector2& a_vector, float a_x, float a_y) noexcept;

	[[nodiscard]] std::tuple<float, float, float> GetVector3(const Vector3& a_vector) noexcept;
	bool SetVector3(Vector3& a_vector, float a_x, float a_y, float a_z) noexcept;

	[[nodiscard]] std::tuple<float, float, float, float> GetVector4(const Vector4& a_vector) noexcept;
	bool SetVector4(Vector4& a_vector, float a_x, float a_y, float a_z, float a_w) noexcept;

	[[nodiscard]] float GetX(const Vector2& a_vector) noexcept;
	bool SetX(Vector2& a_vector, float a_x) noexcept;

	[[nodiscard]] float GetY(const Vector2& a_vector) noexcept;
	bool SetY(Vector2& a_vector, float a_y) noexcept;

	[[nodiscard]] float GetX(const Vector3& a_vector) noexcept;
	bool SetX(Vector3& a_vector, float a_x) noexcept;

	[[nodiscard]] float GetY(const Vector3& a_vector) noexcept;
	bool SetY(Vector3& a_vector, float a_y) noexcept;

	[[nodiscard]] float GetX(const Vector4& a_vector) noexcept;
	bool SetX(Vector4& a_vector, float a_x) noexcept;

	[[nodiscard]] float GetY(const Vector4& a_vector) noexcept;
	bool SetY(Vector4& a_vector, float a_y) noexcept;

	[[nodiscard]] float GetZ(const Vector3& a_vector) noexcept;
	bool SetZ(Vector3& a_vector, float a_z) noexcept;

	[[nodiscard]] float GetZ(const Vector4& a_vector) noexcept;
	bool SetZ(Vector4& a_vector, float a_z) noexcept;

	[[nodiscard]] float GetW(const Vector4& a_vector) noexcept;
	bool SetW(Vector4& a_vector, float a_w) noexcept;
}
