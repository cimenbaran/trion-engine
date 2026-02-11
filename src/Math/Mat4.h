#pragma once
#include <cmath>
#include "Vec3.h"

struct Mat4
{
    // Column-major: m[col*4 + row]
    float m[16]{};

    static Mat4 Identity()
    {
        Mat4 r;
        r.m[0] = r.m[5] = r.m[10] = r.m[15] = 1.0f;
        return r;
    }

    static Mat4 Translate(const Vec3& t)
    {
        Mat4 r = Identity();
        r.m[12] = t.x;
        r.m[13] = t.y;
        r.m[14] = t.z;
        return r;
    }

    static Mat4 Scale(const Vec3& s)
    {
        Mat4 r = Identity();
        r.m[0] = s.x;
        r.m[5] = s.y;
        r.m[10] = s.z;
        return r;
    }

    static Mat4 RotateX(float rad)
    {
        Mat4 r = Identity();
        float c = std::cos(rad), s = std::sin(rad);
        r.m[5] = c;  r.m[9] = -s;
        r.m[6] = s;  r.m[10] = c;
        return r;
    }

    static Mat4 RotateY(float rad)
    {
        Mat4 r = Identity();
        float c = std::cos(rad), s = std::sin(rad);
        r.m[0] = c;  r.m[8] = s;
        r.m[2] = -s; r.m[10] = c;
        return r;
    }

    static Mat4 RotateZ(float rad)
    {
        Mat4 r = Identity();
        float c = std::cos(rad), s = std::sin(rad);
        r.m[0] = c;  r.m[4] = -s;
        r.m[1] = s;  r.m[5] = c;
        return r;
    }

    // Euler (degrees): yaw(Y), pitch(X), roll(Z) 
    // Z * Y * X 
    static Mat4 RotateEulerDegrees(const Vec3& eulerDeg)
    {
        const float d2r = 3.14159265359f / 180.0f;
        Mat4 rx = RotateX(eulerDeg.x * d2r);
        Mat4 ry = RotateY(eulerDeg.y * d2r);
        Mat4 rz = RotateZ(eulerDeg.z * d2r);
        return rz * ry * rx;
    }

    Mat4 operator*(const Mat4& b) const
    {
        Mat4 r{};
        for (int col = 0; col < 4; ++col)
        {
            for (int row = 0; row < 4; ++row)
            {
                r.m[col * 4 + row] =
                    m[0 * 4 + row] * b.m[col * 4 + 0] +
                    m[1 * 4 + row] * b.m[col * 4 + 1] +
                    m[2 * 4 + row] * b.m[col * 4 + 2] +
                    m[3 * 4 + row] * b.m[col * 4 + 3];
            }
        }
        return r;
    }

    static Mat4 Perspective(float fovYRadians, float aspect, float zNear, float zFar)
    {
        // OpenGL clip space: z in [-1, 1]
        Mat4 r{};
        const float f = 1.0f / std::tan(fovYRadians * 0.5f);

        r.m[0] = f / aspect;
        r.m[5] = f;
        r.m[10] = (zFar + zNear) / (zNear - zFar);
        r.m[11] = -1.0f;
        r.m[14] = (2.0f * zFar * zNear) / (zNear - zFar);
        return r;
    }

    static Mat4 LookAt(const Vec3& eye, const Vec3& target, const Vec3& up)
    {
        
        Vec3 f = Normalize(target - eye);
        Vec3 s = Normalize(Cross(f, up));
        Vec3 u = Cross(s, f);

        Mat4 r = Identity();

        r.m[0] = s.x; r.m[4] = s.y; r.m[8] = s.z;
        r.m[1] = u.x; r.m[5] = u.y; r.m[9] = u.z;
        r.m[2] = -f.x; r.m[6] = -f.y; r.m[10] = -f.z;

        r.m[12] = -Dot(s, eye);
        r.m[13] = -Dot(u, eye);
        r.m[14] = Dot(f, eye);

        return r;
    }
};
