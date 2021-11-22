#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "RCUtilsBase.h"

inline float ToRadians(float Deg)
{
	return Deg * ((float)M_PI / 180.0f);
}

inline float ToDegrees(float Rad)
{
	return Rad * (180.0f / (float)M_PI);
}

template <typename T>
inline T Abs(T A)
{
	return A < 0 ? (T)-A : A;
}

template <typename T>
inline T Sign(T A)
{
	return A < 0 ? (T)-1 : (T)1;
}

template <typename T>
inline T Clamp(T A, T Min, T Max)
{
	return Max(Min(A, Max), Min);
}

struct FVector2
{
	union
	{
		float Values[2];
		struct
		{
			float x, y;
		};
		struct
		{
			float u, v;
		};
	};

	static FVector2 GetZero()
	{
		FVector2 New;
		MemZero(New);
		return New;
	}

	FVector2() = default;
	FVector2(float a, float b)
	{
		Set(a, b);
	}

	void Set(float a, float b)
	{
		x = a;
		y = b;
	}
};

struct FVector3
{
	union
	{
		float Values[3];
		struct
		{
			float x, y, z;
		};
		struct
		{
			float u, v, w;
		};
	};

	FVector3() = default;

	FVector3(float InX, float InY, float InZ)
		: x(InX)
		, y(InY)
		, z(InZ)
	{
	}

	void Set(float InX, float InY, float InZ)
	{
		x = InX;
		y = InY;
		z = InZ;
	}

	static FVector3 GetZero()
	{
		FVector3 New;
		MemZero(New);
		return New;
	}

	FVector3 Mul(float f) const
	{
		FVector3 V;
		V.x = x * f;
		V.y = y * f;
		V.z = z * f;
		return V;
	}

	FVector3 Add(const FVector3& V) const
	{
		FVector3 O;
		O.x = x + V.x;
		O.y = y + V.y;
		O.z = z + V.z;
		return O;
	}

	FVector3& operator += (const FVector3& V)
	{
		x += V.x;
		y += V.y;
		z += V.z;
		return *this;
	}

	FVector3& operator -= (const FVector3& V)
	{
		x -= V.x;
		y -= V.y;
		z -= V.z;
		return *this;
	}

	FVector3& operator *= (float f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	FVector3& operator *= (const FVector3& V)
	{
		x *= V.x;
		y *= V.y;
		z *= V.z;
		return *this;
	}

	static FVector3 Cross(const FVector3& A, const FVector3& B)
	{
		FVector3 R;
		float u1 = A.x;
		float u2 = A.y;
		float u3 = A.z;
		float v1 = B.x;
		float v2 = B.y;
		float v3 = B.z;
		R.Set(u2*v3 - u3*v2, u3*v1 - u1*v3, u1*v2 - u2*v1);
		return R;
	}

	static float Dot(const FVector3& A, const FVector3& B)
	{
		return A.x * B.x + A.y * B.y + A.z * B.z;
	}

	static FVector3 Min(const FVector3& A, const FVector3& B)
	{
		return FVector3(::Min(A.x, B.x), ::Min(A.y, B.y), ::Min(A.z, B.z));
	}

	static FVector3 Max(const FVector3& A, const FVector3& B)
	{
		return FVector3(::Max(A.x, B.x), ::Max(A.y, B.y), ::Max(A.z, B.z));
	}

	static FVector3 Abs(const FVector3& A)
	{
		return FVector3(::Abs(A.x), ::Abs(A.y), ::Abs(A.z));
	}

	FVector3 GetNormalized() const
	{
		float InvLen = (float)(1.0 / sqrt(Dot(*this, *this)));
		return FVector3(x * InvLen, y * InvLen, z * InvLen);
	}
};

inline FVector3 operator + (const FVector3& A, const FVector3& B)
{
	return FVector3(A.x + B.x, A.y + B.y, A.z + B.z);
}

inline FVector3 operator - (const FVector3& A, const FVector3& B)
{
	return FVector3(A.x - B.x, A.y - B.y, A.z - B.z);
}

inline FVector3 operator - (const FVector3& A)
{
	return FVector3(-A.x, -A.y, -A.z);
}

inline FVector3 operator * (const FVector3& A, const FVector3& B)
{
	return FVector3(A.x * B.x, A.y * B.y, A.z * B.z);
}

inline FVector3 operator * (const FVector3& A, float f)
{
	return FVector3(A.x * f, A.y * f, A.z * f);
}

inline FVector3 operator * (float f, const FVector3& A)
{
	return FVector3(A.x * f, A.y * f, A.z * f);
}

struct FVector4
{
	union
	{
		float Values[4];
		struct
		{
			float x, y, z, w;
		};
	};

	static FVector4 GetZero()
	{
		FVector4 New;
		MemZero(New);
		return New;
	}

	FVector4() = default;

	FVector3 GetVector3() const
	{
		return FVector3(x, y, z);
	}

	FVector4(const FVector3& V, float W)
	{
		x = V.x;
		y = V.y;
		z = V.z;
		w = W;
	}

	FVector4(float InX, float InY, float InZ, float InW)
	{
		x = InX;
		y = InY;
		z = InZ;
		w = InW;
	}

	void Set(float InX, float InY, float InZ, float InW)
	{
		x = InX;
		y = InY;
		z = InZ;
		w = InW;
	}

	FVector4 Add(const FVector3& V) const
	{
		FVector4 O;
		O.x = x + V.x;
		O.y = y + V.y;
		O.z = z + V.z;
		O.w = w;
		return O;
	}

	FVector4& operator +=(const FVector3& V)
	{
		x = x + V.x;
		y = y + V.y;
		z = z + V.z;
		return *this;
	}

	FVector4& operator -=(const FVector3& V)
	{
		x = x + V.x;
		y = y + V.y;
		z = z + V.z;
		return *this;
	}

	FVector4 GetNormalized() const
	{
		float InvLen = (float)(1.0 / sqrt(Dot(*this, *this)));
		return FVector4(x * InvLen, y * InvLen, z * InvLen, w * InvLen);
	}

	static float Dot(const FVector4& A, const FVector4& B)
	{
		return A.x * B.x + A.y * B.y + A.z * B.z + A.w * B.w;
	}
};

inline FVector4 operator + (const FVector4& A, const FVector4& B)
{
	return FVector4(A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w);
}

inline FVector4 operator - (const FVector4& A, const FVector4& B)
{
	return FVector4(A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w);
}

inline FVector4 operator * (const FVector4& A, const FVector4& B)
{
	return FVector4(A.x * B.x, A.y * B.y, A.z * B.z, A.w * B.w);
}

inline FVector4 operator * (const FVector4& A, float f)
{
	return FVector4(A.x * f, A.y * f, A.z * f, A.w * f);
}

inline FVector4 operator * (float f, const FVector4& A)
{
	return FVector4(A.x * f, A.y * f, A.z * f, A.w * f);
}

struct FIntVector3
{
	union
	{
		int32 Values[3];
		struct
		{
			int32 x, y, z;
		};
	};

	static FIntVector3 GetZero()
	{
		FIntVector3 New;
		MemZero(New);
		return New;
	}

	FIntVector3() {}

	FIntVector3(int32 InX, int32 InY, int32 InZ)
	{
		Set(InX, InY, InZ);
	}

	void Set(int32 InX, int32 InY, int32 InZ)
	{
		x = InX;
		y = InY;
		z = InZ;
	}

	FIntVector3 GetAbs()
	{
		return FIntVector3(Abs(x), Abs(y), Abs(z));
	}

	int GetMaxComponent()
	{
		return Max(x, Max(y, z));
	}

	int GetMinComponent()
	{
		return Min(x, Min(y, z));
	}
};

inline FIntVector3 operator - (const FIntVector3& A, const FIntVector3& B)
{
	return FIntVector3(A.x - B.x, A.y - B.y, A.z - B.z);
}


struct FIntVector4
{
	union
	{
		int32 Values[4];
		struct
		{
			int32 x, y, z, w;
		};
	};

	static FIntVector4 GetZero()
	{
		FIntVector4 New;
		MemZero(New);
		return New;
	}

	FIntVector4() {}

	FIntVector4(int32 InX, int32 InY, int32 InZ, int32 InW)
	{
		Set(InX, InY, InZ, InW);
	}

	void Set(int32 InX, int32 InY, int32 InZ, int32 InW)
	{
		x = InX;
		y = InY;
		z = InZ;
		w = InW;
	}
};

struct FMatrix3x3
{
	union
	{
		float Values[9];
		FVector3 Rows[3];
	};

	FMatrix3x3() {}

	FMatrix3x3 GetTranspose() const
	{
		FMatrix3x3 New;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				New.Values[i * 3 + j] = Values[j * 3 + i];
			}
		}

		return New;
	}

	static FMatrix3x3 GetZero()
	{
		FMatrix3x3 New;
		MemZero(New);
		return New;
	}

	static FMatrix3x3 GetIdentity()
	{
		FMatrix3x3 New;
		MemZero(New);
		New.Values[0] = 1;
		New.Values[4] = 1;
		New.Values[8] = 1;
		return New;
	}

	static FMatrix3x3 GetRotationX(float AngleRad)
	{
		FMatrix3x3 New;
		MemZero(New);
		float Cos = (float)cos(AngleRad);
		float Sin = (float)sin(AngleRad);
		New.Rows[0].x = 1;
		New.Rows[1].y = Cos;
		New.Rows[1].z = -Sin;
		New.Rows[2].y = Sin;
		New.Rows[2].z = Cos;
		return New;
	}

	static FMatrix3x3 GetRotationY(float AngleRad)
	{
		FMatrix3x3 New;
		MemZero(New);
		float Cos = (float)cos(AngleRad);
		float Sin = (float)sin(AngleRad);
		New.Rows[0].x = Cos;
		New.Rows[0].z = Sin;
		New.Rows[1].y = 1;
		New.Rows[2].x = -Sin;
		New.Rows[2].z = Cos;
		return New;
	}

	static FMatrix3x3 GetRotationZ(float AngleRad)
	{
		FMatrix3x3 New;
		MemZero(New);
		float Cos = (float)cos(AngleRad);
		float Sin = (float)sin(AngleRad);
		New.Rows[0].x = Cos;
		New.Rows[0].y = -Sin;
		New.Rows[1].x = Sin;
		New.Rows[1].y = Cos;
		New.Rows[2].z = 1;
		return New;
	}

	void Set(int32 Row, int32 Col, float Value)
	{
		Values[Row * 3 + Col] = Value;
	}
};

struct FMatrix4x4
{
	union
	{
		float Values[16];
		FVector4 Rows[4];
	};

	FMatrix4x4() {}

	FMatrix4x4& operator = (const FMatrix4x4& M)
	{
		Rows[0] = M.Rows[0];
		Rows[1] = M.Rows[1];
		Rows[2] = M.Rows[2];
		Rows[3] = M.Rows[3];
		return *this;
	}

	FMatrix4x4 GetTranspose() const
	{
		FMatrix4x4 New;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				New.Values[i * 4 + j] = Values[j * 4 + i];
			}
		}

		return New;
	}

	static FMatrix4x4 GetZero()
	{
		FMatrix4x4 New;
		MemZero(New);
		return New;
	}

	static FMatrix4x4 GetIdentity()
	{
		FMatrix4x4 New;
		MemZero(New);
		New.Values[0] = 1;
		New.Values[5] = 1;
		New.Values[10] = 1;
		New.Values[15] = 1;
		return New;
	}

	static FMatrix4x4 GetScale(FVector3 Scale)
	{
		FMatrix4x4 New;
		MemZero(New);
		New.Values[0] = Scale.x;
		New.Values[5] = Scale.y;
		New.Values[10] = Scale.z;
		New.Values[15] = 1;
		return New;
	}

	static FMatrix4x4 GetRotationX(float AngleRad)
	{
		FMatrix4x4 New;
		MemZero(New);
		float Cos = (float)cos(AngleRad);
		float Sin = (float)sin(AngleRad);
		New.Rows[0].x = 1;
		New.Rows[1].y = Cos;
		New.Rows[1].z = -Sin;
		New.Rows[2].y = Sin;
		New.Rows[2].z = Cos;
		New.Rows[3].w = 1;
		return New;
	}

	static FMatrix4x4 GetRotationY(float AngleRad)
	{
		FMatrix4x4 New;
		MemZero(New);
		float Cos = (float)cos(AngleRad);
		float Sin = (float)sin(AngleRad);
		New.Rows[0].x = Cos;
		New.Rows[0].z = Sin;
		New.Rows[1].y = 1;
		New.Rows[2].x = -Sin;
		New.Rows[2].z = Cos;
		New.Rows[3].w = 1;
		return New;
	}

	static FMatrix4x4 GetRotationZ(float AngleRad)
	{
		FMatrix4x4 New;
		MemZero(New);
		float Cos = (float)cos(AngleRad);
		float Sin = (float)sin(AngleRad);
		New.Rows[0].x = Cos;
		New.Rows[0].y = -Sin;
		New.Rows[1].x = Sin;
		New.Rows[1].y = Cos;
		New.Rows[2].z = 1;
		New.Rows[3].w = 1;
		return New;
	}

	static FMatrix4x4 GetTranslation(const FVector3& Pos)
	{
		FMatrix4x4 New;
		New.Rows[0].Set(1.0f, 0.0, 0.0f, 0.0f);
		New.Rows[1].Set(0.0f, 1.0, 0.0f, 0.0f);
		New.Rows[2].Set(0.0f, 0.0, 1.0f, 0.0f);
		New.Rows[3] = FVector4(Pos, 1.0f);
		return New;
	}

	void Set(int32 Row, int32 Col, float Value)
	{
		Values[Row * 4 + Col] = Value;
	}

	FVector4 Col(int32 Index) const
	{
		return FVector4(
			Rows[0].Values[Index],
			Rows[1].Values[Index],
			Rows[2].Values[Index],
			Rows[3].Values[Index]);
	}

	FMatrix4x4& operator *=(const FMatrix4x4& M)
	{
		*this = Multiply(*this, M);
		return *this;
	}

	static FMatrix4x4 Multiply(const FMatrix4x4& M0, const FMatrix4x4& M1)
	{
		FMatrix4x4 M;
		for (int32 Row = 0; Row < 4; ++Row)
		{
			for (int32 Col = 0; Col < 4; ++Col)
			{
				M.Set(Row, Col, FVector4::Dot(M0.Rows[Row], M1.Col(Col)));
			}
		}
		return M;
	}

	static FMatrix4x4 GetInverse(const FMatrix4x4& M)
	{
		FVector3 a = M.Rows[0].GetVector3();
		FVector3 b = M.Rows[1].GetVector3();
		FVector3 c = M.Rows[2].GetVector3();
		FVector3 d = M.Rows[3].GetVector3();

		float x = M.Rows[3].x;
		float y = M.Rows[3].y;
		float z = M.Rows[3].z;
		float w = M.Rows[3].w;

		FVector3 s = FVector3::Cross(a, b);
		FVector3 t = FVector3::Cross(c, d);
		FVector3 u = a * y - b * x;
		FVector3 v = c * w - d * z;

		float InvDet = 1.0f / (FVector3::Dot(s, v) + FVector3::Dot(t, u));
		s *= InvDet;
		t *= InvDet;
		u *= InvDet;
		v *= InvDet;

		FVector3 r0 = FVector3::Cross(b, v) + t * y;
		FVector3 r1 = FVector3::Cross(v, a) - t * x;
		FVector3 r2 = FVector3::Cross(d, u) + s * w;
		FVector3 r3 = FVector3::Cross(u, c) - s * z;

		FMatrix4x4 Out;
		Out.Rows[0] = FVector4(r0, -FVector3::Dot(b, t));
		Out.Rows[1] = FVector4(r1, FVector3::Dot(a, t));
		Out.Rows[2] = FVector4(r2, -FVector3::Dot(d, s));
		Out.Rows[3] = FVector4(r3, FVector3::Dot(c, s));
		return Out;
	}

	FVector4 Transform(const FVector4& In)
	{
		float X = FVector4::Dot(Col(0), In);
		float Y = FVector4::Dot(Col(1), In);
		float Z = FVector4::Dot(Col(2), In);
		float W = FVector4::Dot(Col(3), In);
		return FVector4(X, Y, Z, W);
	}
};

inline FMatrix4x4 CalculateProjectionMatrixLH(float FOVRadians, float Aspect, float NearZ, float FarZ)
{
	const float HalfTanFOV = (float)tan(FOVRadians / 2.0);
	FMatrix4x4 New = FMatrix4x4::GetZero();
	New.Set(0, 0, 1.0f / (Aspect * HalfTanFOV));
	New.Set(1, 1, 1.0f / HalfTanFOV);
	New.Set(2, 3, 1);
	New.Set(2, 2, FarZ / (FarZ - NearZ));
	New.Set(3, 2, (NearZ * FarZ) / (NearZ - FarZ));
	return New;
}

inline FMatrix4x4 CalculateProjectionMatrixRH(float FOVRadians, float Aspect, float NearZ, float FarZ)
{
	const float HalfTanFOV = (float)tan(FOVRadians / 2.0);
	FMatrix4x4 New = FMatrix4x4::GetZero();
	New.Set(0, 0, 1.0f / (Aspect * HalfTanFOV));
	New.Set(1, 1, 1.0f / HalfTanFOV);
	New.Set(2, 3, -1);
	New.Set(2, 2, FarZ / (NearZ - FarZ));
	New.Set(3, 2, (NearZ * FarZ) / (NearZ - FarZ));
	return New;
}

inline uint32 PackNormalToU32(const FVector3& V)
{
	uint32 Out = 0;
	Out |= ((uint32)((V.x + 1.0f) * 127.5f) & 0xff) << 0;
	Out |= ((uint32)((V.y + 1.0f) * 127.5f) & 0xff) << 8;
	Out |= ((uint32)((V.z + 1.0f) * 127.5f) & 0xff) << 16;
	return Out;
}

inline uint32 GetNumMips(uint32 Width, uint32 Height)
{
	uint32 NumMips = 1;
	while (Width > 1 || Height > 1)
	{
		Width = Max(Width >> 1, 1u);
		Height = Max(Height >> 1, 1u);
		++NumMips;
	}
	return NumMips;
}
