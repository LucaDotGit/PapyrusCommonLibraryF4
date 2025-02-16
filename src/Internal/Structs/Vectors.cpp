#include "Internal/Structs/Vectors.hpp"

namespace Internal::Vectors
{
	static constexpr auto X_KEY = "X"sv;
	static constexpr auto Y_KEY = "Y"sv;
	static constexpr auto Z_KEY = "Z"sv;
	static constexpr auto W_KEY = "W"sv;

	Vector2 MakeVector2(float a_x, float a_y) noexcept
	{
		auto vec2 = Vector2();
		SetVector2(vec2, a_x, a_y);
		return vec2;
	}

	Vector2 MakeVector2(std::span<float, 2> a_span) noexcept
	{
		auto vec2 = Vector2();
		SetVector2(vec2, a_span[0], a_span[1]);
		return vec2;
	}

	Vector2 MakeVector2(const RE::NiPoint2& a_point) noexcept
	{
		auto vec2 = Vector2();
		SetVector2(vec2, a_point.x, a_point.y);
		return vec2;
	}

	Vector3 MakeVector3(float a_x, float a_y, float a_z) noexcept
	{
		auto vec3 = Vector3();
		SetVector3(vec3, a_x, a_y, a_z);
		return vec3;
	}

	Vector3 MakeVector3(std::span<float, 3> a_span) noexcept
	{
		auto vec3 = Vector3();
		SetVector3(vec3, a_span[0], a_span[1], a_span[2]);
		return vec3;
	}

	Vector3 MakeVector3(const RE::NiPoint3& a_point) noexcept
	{
		auto vec3 = Vector3();
		SetVector3(vec3, a_point.x, a_point.y, a_point.z);
		return vec3;
	}

	Vector4 MakeVector4(float a_x, float a_y, float a_z, float a_w) noexcept
	{
		auto vec4 = Vector4();
		SetVector4(vec4, a_x, a_y, a_z, a_w);
		return vec4;
	}

	Vector4 MakeVector4(std::span<float, 4> a_span) noexcept
	{
		auto vec4 = Vector4();
		SetVector4(vec4, a_span[0], a_span[1], a_span[2], a_span[3]);
		return vec4;
	}

	Vector4 MakeVector4(const RE::NiPoint4& a_point) noexcept
	{
		auto vec4 = Vector4();
		SetVector4(vec4, a_point.x, a_point.y, a_point.z, a_point.w);
		return vec4;
	}

	std::tuple<float, float> GetVector2(const Vector2& a_vector) noexcept
	{
		return std::make_tuple(
			GetX(a_vector),
			GetY(a_vector));
	}

	bool SetVector2(Vector2& a_vector, float a_x, float a_y) noexcept
	{
		return SetX(a_vector, a_x) &&
			   SetY(a_vector, a_y);
	}

	std::tuple<float, float, float> GetVector3(const Vector3& a_vector) noexcept
	{
		return std::make_tuple(
			GetX(a_vector),
			GetY(a_vector),
			GetZ(a_vector));
	}

	bool SetVector3(Vector3& a_vector, float a_x, float a_y, float a_z) noexcept
	{
		return SetX(a_vector, a_x) &&
			   SetY(a_vector, a_y) &&
			   SetZ(a_vector, a_z);
	}

	std::tuple<float, float, float, float> GetVector4(const Vector4& a_vector) noexcept
	{
		return std::make_tuple(
			GetX(a_vector),
			GetY(a_vector),
			GetZ(a_vector),
			GetW(a_vector));
	}

	bool SetVector4(Vector4& a_vector, float a_x, float a_y, float a_z, float a_w) noexcept
	{
		return SetX(a_vector, a_x) &&
			   SetY(a_vector, a_y) &&
			   SetZ(a_vector, a_z) &&
			   SetW(a_vector, a_w);
	}

	float GetX(const Vector2& a_vector) noexcept
	{
		return a_vector.find<float>(X_KEY).value_or(0.0f);
	}

	bool SetX(Vector2& a_vector, float a_x) noexcept
	{
		return a_vector.insert(X_KEY, a_x);
	}

	float GetY(const Vector2& a_vector) noexcept
	{
		return a_vector.find<float>(Y_KEY).value_or(0.0f);
	}

	bool SetY(Vector2& a_vector, float a_y) noexcept
	{
		return a_vector.insert(Y_KEY, a_y);
	}

	float GetX(const Vector3& a_vector) noexcept
	{
		return a_vector.find<float>(X_KEY).value_or(0.0f);
	}

	bool SetX(Vector3& a_vector, float a_x) noexcept
	{
		return a_vector.insert(X_KEY, a_x);
	}

	float GetY(const Vector3& a_vector) noexcept
	{
		return a_vector.find<float>(Y_KEY).value_or(0.0f);
	}

	bool SetY(Vector3& a_vector, float a_y) noexcept
	{
		return a_vector.insert(Y_KEY, a_y);
	}

	float GetX(const Vector4& a_vector) noexcept
	{
		return a_vector.find<float>(X_KEY).value_or(0.0f);
	}

	bool SetX(Vector4& a_vector, float a_x) noexcept
	{
		return a_vector.insert(X_KEY, a_x);
	}

	float GetY(const Vector4& a_vector) noexcept
	{
		return a_vector.find<float>(Y_KEY).value_or(0.0f);
	}

	bool SetY(Vector4& a_vector, float a_y) noexcept
	{
		return a_vector.insert(Y_KEY, a_y);
	}

	float GetZ(const Vector3& a_vector) noexcept
	{
		return a_vector.find<float>(Z_KEY).value_or(0.0f);
	}

	bool SetZ(Vector3& a_vector, float a_z) noexcept
	{
		return a_vector.insert(Z_KEY, a_z);
	}

	float GetZ(const Vector4& a_vector) noexcept
	{
		return a_vector.find<float>(Z_KEY).value_or(0.0f);
	}

	bool SetZ(Vector4& a_vector, float a_z) noexcept
	{
		return a_vector.insert(Z_KEY, a_z);
	}

	float GetW(const Vector4& a_vector) noexcept
	{
		return a_vector.find<float>(W_KEY).value_or(0.0f);
	}

	bool SetW(Vector4& a_vector, float a_w) noexcept
	{
		return a_vector.insert(W_KEY, a_w);
	}
}
