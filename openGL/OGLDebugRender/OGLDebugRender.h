#pragma once

#include <Windows.h>
#include <GL\gl.h>
#include <cmath>

#include "./../OGLMath/OGLVector3f.h"

class OGLDebugRender
{
    public:
        OGLDebugRender        ();
        ~OGLDebugRender       ();

        void    drawLine     (OGLVector3f &, OGLVector3f &, OGLVector3f &);
        void    drawGrid     (int, float, OGLVector3f &);
        void    drawSphere   (float, int, OGLVector3f &);
        void    drawAxis     (OGLVector3f &, float);
        void    drawPoint    (OGLVector3f &, OGLVector3f &, float);
};
