#pragma once

#include <cmath>
#include "./OGLVector3f.h"

class OGLMatrix4f
{
    private:
        float mMatrix4f[16];

    public:
        OGLMatrix4f  (void);
        ~OGLMatrix4f (void);

        float   *getMatrix      (void);

        void    setIdentity     (void);
        void    setFrustum      (float fovAngle, float aspectRatio, float zNear, float zFar); 
        void    setLookAt       (OGLVector3f &eyePos, OGLVector3f &lookAt, OGLVector3f &upVector);
};

