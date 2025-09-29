#pragma once
#include <GL/freeglut.h>
#include <cmath>
#include <cfloat>

constexpr GLfloat FLT_PI			{ 3.141592653f };
constexpr GLfloat FLT_RADIAN_FACTOR	{ FLT_PI / 180.f };
constexpr GLfloat FLT_DEGREE_FACTOR	{ 180.f / FLT_PI };

inline constexpr GLfloat ToRadian(GLfloat degree) { return degree * FLT_RADIAN_FACTOR; }
inline constexpr GLfloat ToDegree(GLfloat radian) { return radian * FLT_DEGREE_FACTOR; }

inline constexpr bool IsZero(GLfloat f) { return (f > -FLT_EPSILON && f < FLT_EPSILON); }
inline constexpr bool IsEqual(GLfloat f0, GLfloat f1) { return IsZero(f0 - f1); }

class GLAngle {
public:
	union {
		GLfloat f[3];
		struct { GLfloat pitch, yaw, roll; };
	};
	GLAngle() : pitch{ 0.0f }, yaw{ 0.0f }, roll{ 0.0f } {}
};

class GLScale {
public:
	union {
		GLfloat f[3];
		struct { GLfloat x, y, z; };
	};
	GLScale() : x{ 1.0f }, y{ 1.0f }, z{ 1.0f } {}
	GLScale(GLfloat n) : x{ n }, y{ n }, z{ n } {}
	GLScale(GLfloat X, GLfloat Y, GLfloat Z) : x{ X }, y{ Y }, z{ Z } {}
};

class GLvector {
public:
	union {
		GLfloat f[4];
		struct { GLfloat x, y, z, w; };
		struct { GLfloat r, g, b, a; };
	};
	GLvector() : x{ 0.0f }, y{ 0.0f }, z{ 0.0f }, w{ 1.0f } {}
	GLvector(const GLvector& other) { memcpy_s(this, sizeof(GLvector), &other, sizeof(GLvector)); }
	GLvector(GLfloat f0, GLfloat f1, GLfloat f2 = 0.0f, GLfloat f3 = 1.0f)
		: x{ f0 }, y{ f1 }, z{ f2 }, w{ f3 } {}
	GLvector operator*(GLfloat scalar) const { return GLvector(x * scalar, y * scalar, z * scalar); }
	GLvector operator/(GLfloat scalar) const { return GLvector(x / scalar, y / scalar, z / scalar); }
	GLvector operator+(const GLvector& other) const { return GLvector(x + other.x, y + other.y, z + other.z); }
	GLvector operator-(const GLvector& other) const { return GLvector(x - other.x, y - other.y, z - other.z); }
	GLvector operator-() const { return GLvector(-x, -y, -z); }
	GLvector& operator=(const GLvector& other) { memcpy_s(this, sizeof(GLvector), &other, sizeof(GLvector)); return *this; }
	GLvector& operator+=(const GLvector& other) { *this = *this + other; return *this; }
};
inline GLvector operator*(GLfloat scalar, const GLvector& v) { return GLvector(scalar * v.x, scalar * v.y, scalar * v.z); }
inline bool operator==(const GLvector& v0, const GLvector& v1) { return (IsEqual(v0.x, v1.x) && IsEqual(v0.y, v1.y) && IsEqual(v0.z, v1.z) && IsEqual(v0.w, v1.w)); }

class GLmatrix {
public:
	union {
		GLvector r[4];
		GLfloat arr[16];
		struct {
			GLfloat m11, m12, m13, m14;
			GLfloat m21, m22, m23, m24;
			GLfloat m31, m32, m33, m34;
			GLfloat m41, m42, m43, m44;
		};
	};
	GLmatrix()
		: m11{ 1.0f }, m12{ 0.0f }, m13{ 0.0f }, m14{ 0.0f }
		, m21{ 0.0f }, m22{ 1.0f }, m23{ 0.0f }, m24{ 0.0f }
		, m31{ 0.0f }, m32{ 0.0f }, m33{ 1.0f }, m34{ 0.0f }
		, m41{ 0.0f }, m42{ 0.0f }, m43{ 0.0f }, m44{ 1.0f }
	{}
	GLmatrix(const GLmatrix& other) { memcpy_s(this, sizeof(GLmatrix), &other, sizeof(GLmatrix)); }
	GLmatrix& operator=(const GLmatrix& other) { memcpy_s(this, sizeof(GLmatrix), &other, sizeof(GLmatrix)); return *this; }
	

	static GLmatrix Rotate(const GLvector axis, const GLfloat angle) {
		GLmatrix mtx;
		GLfloat theta{ ToRadian(angle) };
		GLfloat c{ cos(theta) };
		GLfloat rev_c{ 1.0f - c };
		GLfloat s{ sin(theta) };

		mtx.m11 = c + axis.x * axis.x * rev_c;
		mtx.m12 = axis.x * axis.y * rev_c - axis.z * s;
		mtx.m13 = axis.x * axis.z * rev_c + axis.y * s;
		// mtx.m14 = 0.0f;

		mtx.m21 = axis.y * axis.x * rev_c + axis.z * s;
		mtx.m22 = c + axis.y * axis.y * rev_c;
		mtx.m23 = axis.y * axis.z * rev_c - axis.x * s;
		// mtx.m24 = 0.0f;

		mtx.m31 = axis.z * axis.x * rev_c - axis.y * s;
		mtx.m32 = axis.z * axis.y * rev_c + axis.x * s;
		mtx.m33 = c + axis.z * axis.z * rev_c;
		// mtx.m34 = 0.0f;

		// mtx.m41 = 0.0f;
		// mtx.m42 = 0.0f;
		// mtx.m43 = 0.0f;
		// mtx.m44 = 1.0f;
		return mtx;
	}
};
inline GLmatrix operator*(const GLmatrix& m0, const GLmatrix& m1) {
	GLmatrix mtx;
	mtx.m11 = m0.m11 * m1.m11 + m0.m12 * m1.m21 + m0.m13 * m1.m31 + m0.m14 * m1.m41;
	mtx.m12 = m0.m11 * m1.m12 + m0.m12 * m1.m22 + m0.m13 * m1.m32 + m0.m14 * m1.m42;
	mtx.m13 = m0.m11 * m1.m13 + m0.m12 * m1.m23 + m0.m13 * m1.m33 + m0.m14 * m1.m43;
	mtx.m14 = m0.m11 * m1.m14 + m0.m12 * m1.m24 + m0.m13 * m1.m34 + m0.m14 * m1.m44;

	mtx.m21 = m0.m21 * m1.m11 + m0.m22 * m1.m21 + m0.m23 * m1.m31 + m0.m24 * m1.m41;
	mtx.m22 = m0.m21 * m1.m12 + m0.m22 * m1.m22 + m0.m23 * m1.m32 + m0.m24 * m1.m42;
	mtx.m23 = m0.m21 * m1.m13 + m0.m22 * m1.m23 + m0.m23 * m1.m33 + m0.m24 * m1.m43;
	mtx.m24 = m0.m21 * m1.m14 + m0.m22 * m1.m24 + m0.m23 * m1.m34 + m0.m24 * m1.m44;

	mtx.m31 = m0.m31 * m1.m11 + m0.m32 * m1.m21 + m0.m33 * m1.m31 + m0.m34 * m1.m41;
	mtx.m32 = m0.m31 * m1.m12 + m0.m32 * m1.m22 + m0.m33 * m1.m32 + m0.m34 * m1.m42;
	mtx.m33 = m0.m31 * m1.m13 + m0.m32 * m1.m23 + m0.m33 * m1.m33 + m0.m34 * m1.m43;
	mtx.m34 = m0.m31 * m1.m14 + m0.m32 * m1.m24 + m0.m33 * m1.m34 + m0.m34 * m1.m44;

	mtx.m41 = m0.m41 * m1.m11 + m0.m42 * m1.m21 + m0.m43 * m1.m31 + m0.m44 * m1.m41;
	mtx.m42 = m0.m41 * m1.m12 + m0.m42 * m1.m22 + m0.m43 * m1.m32 + m0.m44 * m1.m42;
	mtx.m43 = m0.m41 * m1.m13 + m0.m42 * m1.m23 + m0.m43 * m1.m33 + m0.m44 * m1.m43;
	mtx.m44 = m0.m41 * m1.m14 + m0.m42 * m1.m24 + m0.m43 * m1.m34 + m0.m44 * m1.m44;
	return mtx;
}
inline GLvector operator*(const GLmatrix& m, const GLvector& v) { 
	GLvector ret;
	ret.x = m.m11 * v.x + m.m12 * v.y + m.m13 * v.z + m.m14 * v.w;
	ret.y = m.m21 * v.x + m.m22 * v.y + m.m23 * v.z + m.m24 * v.w;
	ret.z = m.m31 * v.x + m.m32 * v.y + m.m33 * v.z + m.m34 * v.w;
	ret.w = m.m41 * v.x + m.m42 * v.y + m.m43 * v.z + m.m44 * v.w;
	return ret;
}

inline GLfloat length(const GLvector& v) {
	return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}
inline GLvector normalize(const GLvector& v) {
	return v / length(v);
}
inline GLvector add(const GLvector& v0, const GLvector& v1) {
	return v0 + v1;
}
inline GLvector sub(const GLvector& v0, const GLvector& v1) {
	return v0 - v1;
}
inline GLfloat dot(const GLvector& v0, const GLvector& v1) {
	return ((v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z));
}
inline GLvector cross(const GLvector& v0, const GLvector& v1) {
	return normalize(GLvector{ v0.y*v1.z - v0.z*v1.y, v0.z*v1.x - v0.x*v1.z, v0.x*v1.y - v0.y*v1.x });
}
inline GLfloat mul(const GLvector& v0, const GLvector& v1) {
	return ((v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z) + (v0.w * v1.w));
}
inline GLvector lerp(const GLvector& v0, const GLvector& v1, const GLfloat t /*0.0 ~ 1.0*/) {
	return v0 * (1.0f - t) + v1 * t;
}
inline GLfloat lerp(const GLfloat v0, const GLfloat v1, const GLfloat t /*0.0 ~ 1.0*/) {
	return v0 * (1.0f - t) + v1 * t;
}

inline GLvector CalcCadinalSpline(const GLvector& P0, const GLvector& P1, const GLvector& P2, const GLvector& P3, const GLfloat t, const GLfloat tension = 0.1f) {
	const GLfloat s{ (1.0f - tension) * 0.5f };

	const GLvector a{ (2.0f - s) * P1 + (s - 2.0f) * P2 - s * P0 + s * P3 };
	const GLvector b{ 2.0f * s * P0 + (s - 3.0f) * P1 + (3.0f - 2.0f * s) * P2 - s * P3 };
	const GLvector c{ s * P2 - s * P0 };
	const GLvector d{ P1 };

	return (a * pow(t, 3.0f) + b * pow(t, 2.0f) + c * t + d);
}