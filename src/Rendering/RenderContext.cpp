#include "Rendering/RenderContext.h"

Mat4 RenderContext::s_view = Mat4::Identity();
Mat4 RenderContext::s_proj = Mat4::Identity();

void RenderContext::SetViewProjection(const Mat4& view, const Mat4& proj)
{
    s_view = view;
    s_proj = proj;
}

const Mat4& RenderContext::View() { return s_view; }
const Mat4& RenderContext::Projection() { return s_proj; }
