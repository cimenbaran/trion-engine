#pragma once
#include "Math/Mat4.h"

class RenderContext
{
public:
    static void SetViewProjection(const Mat4& view, const Mat4& proj);
    static const Mat4& View();
    static const Mat4& Projection();

private:
    static Mat4 s_view;
    static Mat4 s_proj;
};