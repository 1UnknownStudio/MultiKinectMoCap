#pragma once

#include <cmath>
#include "./OGLVector4f.h"

class OGLMatrix4f
{
    public:
        float m_pMatrix4f[16];
        OGLMatrix4f  (void);
        ~OGLMatrix4f (void);

        OGLMatrix4f    setIdentity(void);
        OGLMatrix4f    setFrustum(float fovAngle, float aspectRatio, float zNear, float zFar);
        OGLMatrix4f    setLookAt(OGLVector4f &eyePos, OGLVector4f &lookAt, OGLVector4f &upVector);

        OGLMatrix4f    setXRotation(float xAngle);
        OGLMatrix4f    setYRotation(float yAngle);
        OGLMatrix4f    setZRotation(float zAngle);
        OGLMatrix4f    setTranslation(float x, float y, float z);

        OGLMatrix4f operator * (const OGLMatrix4f &inputMatrix);
        OGLMatrix4f operator + (const OGLMatrix4f &inputMatrix);
        OGLMatrix4f operator - (const OGLMatrix4f &inputMatrix);
        OGLMatrix4f operator = (const OGLMatrix4f &inputMatrix);

        OGLVector4f operator * (const OGLVector4f &inputVector);
};
