#pragma once

class OGLVector4f
{
    public:
        union
        {
            struct { float x; float y; float z; float w; };
            float u[4];
        };

        OGLVector4f        (void);
        OGLVector4f        (const OGLVector4f &);
        OGLVector4f        (float, float, float);
        OGLVector4f        (float, float, float, float);

        OGLVector4f        operator +   (const OGLVector4f &);
        OGLVector4f        operator -   (const OGLVector4f &);
        OGLVector4f        operator =   (const OGLVector4f &);

        OGLVector4f        operator *   (float);
        OGLVector4f        operator /   (float);
        float              length       (void);
        float              dot          (const OGLVector4f &);

        OGLVector4f        cross        (const OGLVector4f &);
        OGLVector4f        normalize    (void);
        OGLVector4f        negative     (void);
};
