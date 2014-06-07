#pragma once

#include <Windows.h>
#include <GL\gl.h>
#include <cmath>

#include "./../OGLMath/OGLVector4f.h"

class OGLDebugRender
{
    public:
        OGLDebugRender        ();
        ~OGLDebugRender       ();

        void    drawLine     (OGLVector4f &, OGLVector4f &, OGLVector4f &);
        void    drawGrid     (int, float, OGLVector4f &);
<<<<<<< HEAD
<<<<<<< HEAD

=======
        void    drawSphere   (float, int, OGLVector4f &);
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
=======
        void    drawSphere   (float, int, OGLVector4f &);
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
        void    drawAxis     (OGLVector4f &, float);
        void    drawPoint    (OGLVector4f &, OGLVector4f &, float);
};
