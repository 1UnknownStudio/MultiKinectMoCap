#pragma once

#include <cmath>
#include "./OGLVector4f.h"

class OGLMatrix4f
{
    public:
        float m_pMatrix4f[16];
        OGLMatrix4f  (void);
        ~OGLMatrix4f (void);

        void    setIdentity     (void);
        void    setFrustum      (float fovAngle, float aspectRatio, float zNear, float zFar); 
        void    setLookAt       (OGLVector4f &eyePos, OGLVector4f &lookAt, OGLVector4f &upVector);

        void    setXRotation    (float xAngle);
        void    setYRotation    (float yAngle);
        void    setZRotation    (float zAngle);
        void    setTranslation  (float x, float y, float z);

        OGLMatrix4f operator * (const OGLMatrix4f &inputMatrix);
        OGLMatrix4f operator + (const OGLMatrix4f &inputMatrix);
        OGLMatrix4f operator - (const OGLMatrix4f &inputMatrix);
        OGLMatrix4f operator = (const OGLMatrix4f &inputMatrix);

        OGLVector4f operator * (const OGLVector4f &inputVector);
};
