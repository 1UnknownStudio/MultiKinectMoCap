#pragma once

#include <Windows.h>
#include <GL\gl.h>
#include <cmath>

#include "./../OGLMath/OGLVector4f.h"

class OGLDebugRender
{
    public:
        OGLDebugRender        (void);
        ~OGLDebugRender       (void);

        void    drawLine     (OGLVector4f &, OGLVector4f &, OGLVector4f &);
        void    drawGrid     (int, float, OGLVector4f &);

        void    drawAxis     (OGLVector4f &, float);
        void    drawPoint    (OGLVector4f &, OGLVector4f &, float);
};
