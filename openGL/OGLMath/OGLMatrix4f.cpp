#include "./OGLMatrix4f.h"

OGLMatrix4f::OGLMatrix4f(void)
{
    this->m_pMatrix4f[ 0] = 1;
    this->m_pMatrix4f[ 1] = 0;
    this->m_pMatrix4f[ 2] = 0;
    this->m_pMatrix4f[ 3] = 0;
<<<<<<< HEAD
<<<<<<< HEAD

    this->m_pMatrix4f[ 4] = 0;
    this->m_pMatrix4f[ 5] = 1;
    this->m_pMatrix4f[ 6] = 0;
    this->m_pMatrix4f[ 7] = 0;

    this->m_pMatrix4f[ 8] = 0;
    this->m_pMatrix4f[ 9] = 0;
    this->m_pMatrix4f[10] = 1;
    this->m_pMatrix4f[11] = 0;

    this->m_pMatrix4f[12] = 0;
    this->m_pMatrix4f[13] = 0;
    this->m_pMatrix4f[14] = 0;
    this->m_pMatrix4f[15] = 1;
}
=======
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
=======
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4

    this->m_pMatrix4f[ 4] = 0;
    this->m_pMatrix4f[ 5] = 1;
    this->m_pMatrix4f[ 6] = 0;
    this->m_pMatrix4f[ 7] = 0;

    this->m_pMatrix4f[ 8] = 0;
    this->m_pMatrix4f[ 9] = 0;
    this->m_pMatrix4f[10] = 1;
    this->m_pMatrix4f[11] = 0;

    this->m_pMatrix4f[12] = 0;
    this->m_pMatrix4f[13] = 0;
    this->m_pMatrix4f[14] = 0;
    this->m_pMatrix4f[15] = 1;
}

<<<<<<< HEAD
<<<<<<< HEAD
OGLMatrix4f OGLMatrix4f::setIdentity(void)
{
    this->m_pMatrix4f[ 0] = 1;
    this->m_pMatrix4f[ 1] = 0;
    this->m_pMatrix4f[ 2] = 0;
    this->m_pMatrix4f[ 3] = 0;

=======
=======
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
OGLMatrix4f::~OGLMatrix4f(void)
{
}

void OGLMatrix4f::setIdentity(void)
{
    this->m_pMatrix4f[ 0] = 1;
    this->m_pMatrix4f[ 1] = 0;
    this->m_pMatrix4f[ 2] = 0;
    this->m_pMatrix4f[ 3] = 0;

<<<<<<< HEAD
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
=======
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
    this->m_pMatrix4f[ 4] = 0;
    this->m_pMatrix4f[ 5] = 1;
    this->m_pMatrix4f[ 6] = 0;
    this->m_pMatrix4f[ 7] = 0;

    this->m_pMatrix4f[ 8] = 0;
    this->m_pMatrix4f[ 9] = 0;
    this->m_pMatrix4f[10] = 1;
    this->m_pMatrix4f[11] = 0;

    this->m_pMatrix4f[12] = 0;
    this->m_pMatrix4f[13] = 0;
    this->m_pMatrix4f[14] = 0;
    this->m_pMatrix4f[15] = 1;
<<<<<<< HEAD
<<<<<<< HEAD

    return(*this);
}

OGLMatrix4f OGLMatrix4f::setLookAt(OGLVector4f &eyePos, OGLVector4f &lookAt, OGLVector4f &upVector)
=======
}

void OGLMatrix4f::setLookAt(OGLVector4f &eyePos, OGLVector4f &lookAt, OGLVector4f &upVector)
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
=======
}

void OGLMatrix4f::setLookAt(OGLVector4f &eyePos, OGLVector4f &lookAt, OGLVector4f &upVector)
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
{
    OGLVector4f zAxis = (eyePos - lookAt).normalize();
    OGLVector4f xAxis = (upVector.cross(zAxis)).normalize();
    OGLVector4f yAxis = (zAxis.cross(xAxis)).normalize();
    
    this->m_pMatrix4f[ 0] = xAxis.x;
    this->m_pMatrix4f[ 1] = yAxis.x;
    this->m_pMatrix4f[ 2] = zAxis.x;
    this->m_pMatrix4f[ 3] = 0;

    this->m_pMatrix4f[ 4] = xAxis.y;
    this->m_pMatrix4f[ 5] = yAxis.y;
    this->m_pMatrix4f[ 6] = zAxis.y;
    this->m_pMatrix4f[ 7] = 0;

    this->m_pMatrix4f[ 8] = xAxis.z;
    this->m_pMatrix4f[ 9] = yAxis.z;
    this->m_pMatrix4f[10] = zAxis.z;
    this->m_pMatrix4f[11] = 0;

    this->m_pMatrix4f[12] = -(xAxis.dot(eyePos));
    this->m_pMatrix4f[13] = -(yAxis.dot(eyePos));
    this->m_pMatrix4f[14] = -(zAxis.dot(eyePos));
    this->m_pMatrix4f[15] = 1;
<<<<<<< HEAD
<<<<<<< HEAD

    return(*this);
=======
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
=======
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
}

OGLMatrix4f OGLMatrix4f::setFrustum(float fovAngle, float aspectRatio, float zNear, float zFar)
{
    float fScale = zNear * std::tan(fovAngle * 3.14159265f / 360.0f);

    float fRight = aspectRatio * fScale;
    float fLeft  = -fRight;

    float fTop    = fScale;
    float fBotton = -fTop;

    this->m_pMatrix4f[ 0] =  2.0f * zNear / (fRight - fLeft);
    this->m_pMatrix4f[ 1] =  0.0f;
    this->m_pMatrix4f[ 2] =  0.0f;
    this->m_pMatrix4f[ 3] =  0.0f;

    this->m_pMatrix4f[ 4] =  0.0f;
    this->m_pMatrix4f[ 5] =  2.0f * zNear / (fTop - fBotton);
    this->m_pMatrix4f[ 6] =  0.0f;
    this->m_pMatrix4f[ 7] =  0.0f;

    this->m_pMatrix4f[ 8] =  (fRight + fLeft) / (fRight - fLeft);
    this->m_pMatrix4f[ 9] =  (fTop + fBotton) / (fTop - fBotton);
    this->m_pMatrix4f[10] = -((zFar + zNear) / (zFar - zNear));
    this->m_pMatrix4f[11] = -1.0f;

    this->m_pMatrix4f[12] =  0.0f;
    this->m_pMatrix4f[13] =  0.0f;
    this->m_pMatrix4f[14] = -(2.0f * zFar * zNear / (zFar - zNear));
    this->m_pMatrix4f[15] =  0.0f;
<<<<<<< HEAD
<<<<<<< HEAD

    return(*this);
}

OGLMatrix4f OGLMatrix4f::setXRotation(float xAngle)
=======
}

void OGLMatrix4f::setXRotation(float xAngle)
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
=======
}

void OGLMatrix4f::setXRotation(float xAngle)
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
{
    this->m_pMatrix4f[ 0] =  1;
    this->m_pMatrix4f[ 1] =  0;
    this->m_pMatrix4f[ 2] =  0;
    this->m_pMatrix4f[ 3] =  0;

    this->m_pMatrix4f[ 4] =  0;
    this->m_pMatrix4f[ 5] =  std::cos(xAngle);
    this->m_pMatrix4f[ 6] = -std::sin(xAngle);
    this->m_pMatrix4f[ 7] =  0;

    this->m_pMatrix4f[ 8] =  0;
    this->m_pMatrix4f[ 9] =  std::sin(xAngle);
    this->m_pMatrix4f[10] =  std::cos(xAngle);
    this->m_pMatrix4f[11] =  0;

    this->m_pMatrix4f[12] =  0;
    this->m_pMatrix4f[13] =  0;
    this->m_pMatrix4f[14] =  0;
    this->m_pMatrix4f[15] =  1;
<<<<<<< HEAD
<<<<<<< HEAD

    return(*this);
}

OGLMatrix4f OGLMatrix4f::setYRotation(float yAngle)
=======
}

void OGLMatrix4f::setYRotation(float yAngle)
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
=======
}

void OGLMatrix4f::setYRotation(float yAngle)
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
{
    this->m_pMatrix4f[ 0] =  std::cos(yAngle);
    this->m_pMatrix4f[ 1] =  0;
    this->m_pMatrix4f[ 2] =  std::sin(yAngle);
    this->m_pMatrix4f[ 3] =  0;

    this->m_pMatrix4f[ 4] =  0;
    this->m_pMatrix4f[ 5] =  1;
    this->m_pMatrix4f[ 6] =  0;
    this->m_pMatrix4f[ 7] =  0;

    this->m_pMatrix4f[ 8] = -std::sin(yAngle);
    this->m_pMatrix4f[ 9] =  0;
    this->m_pMatrix4f[10] =  std::cos(yAngle);
    this->m_pMatrix4f[11] =  0;

    this->m_pMatrix4f[12] =  0;
    this->m_pMatrix4f[13] =  0;
    this->m_pMatrix4f[14] =  0;
    this->m_pMatrix4f[15] =  1;
<<<<<<< HEAD
<<<<<<< HEAD

    return(*this);
}

OGLMatrix4f OGLMatrix4f::setZRotation(float zAngle)
=======
}

void OGLMatrix4f::setZRotation(float zAngle)
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
=======
}

void OGLMatrix4f::setZRotation(float zAngle)
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
{
    this->m_pMatrix4f[ 0] =  std::cos(zAngle);
    this->m_pMatrix4f[ 1] = -std::sin(zAngle);
    this->m_pMatrix4f[ 2] =  0;
    this->m_pMatrix4f[ 3] =  0;

    this->m_pMatrix4f[ 4] =  std::sin(zAngle);
    this->m_pMatrix4f[ 5] =  std::cos(zAngle);
    this->m_pMatrix4f[ 6] =  0;
    this->m_pMatrix4f[ 7] =  0;

    this->m_pMatrix4f[ 8] =  0;
    this->m_pMatrix4f[ 9] =  0;
    this->m_pMatrix4f[10] =  1;
    this->m_pMatrix4f[11] =  0;

    this->m_pMatrix4f[12] =  0;
    this->m_pMatrix4f[13] =  0;
    this->m_pMatrix4f[14] =  0;
    this->m_pMatrix4f[15] =  1;
<<<<<<< HEAD
<<<<<<< HEAD

    return(*this);
}

OGLMatrix4f OGLMatrix4f::setTranslation(float x, float y, float z)
=======
}

void OGLMatrix4f::setTranslation(float x, float y, float z)
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
=======
}

void OGLMatrix4f::setTranslation(float x, float y, float z)
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
{
    this->m_pMatrix4f[ 0] = 1;
    this->m_pMatrix4f[ 1] = 0;
    this->m_pMatrix4f[ 2] = 0;
    this->m_pMatrix4f[ 3] = x;

    this->m_pMatrix4f[ 4] = 0;
    this->m_pMatrix4f[ 5] = 1;
    this->m_pMatrix4f[ 6] = 0;
    this->m_pMatrix4f[ 7] = y;

    this->m_pMatrix4f[ 8] = 0;
    this->m_pMatrix4f[ 9] = 0;
    this->m_pMatrix4f[10] = 1;
    this->m_pMatrix4f[11] = z;

    this->m_pMatrix4f[12] = 0;
    this->m_pMatrix4f[13] = 0;
    this->m_pMatrix4f[14] = 0;
    this->m_pMatrix4f[15] = 1;
<<<<<<< HEAD
<<<<<<< HEAD

    return(*this);
=======
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
=======
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
}

OGLMatrix4f OGLMatrix4f::operator * (const OGLMatrix4f &inputMatrix)
{
    OGLMatrix4f newMatrix;

    newMatrix.m_pMatrix4f[ 0] = this->m_pMatrix4f[ 0] * inputMatrix.m_pMatrix4f[ 0] + this->m_pMatrix4f[ 1] * inputMatrix.m_pMatrix4f[ 4] + this->m_pMatrix4f[ 2] * inputMatrix.m_pMatrix4f[ 8] + this->m_pMatrix4f[ 3] * inputMatrix.m_pMatrix4f[12];
    newMatrix.m_pMatrix4f[ 1] = this->m_pMatrix4f[ 0] * inputMatrix.m_pMatrix4f[ 1] + this->m_pMatrix4f[ 1] * inputMatrix.m_pMatrix4f[ 5] + this->m_pMatrix4f[ 2] * inputMatrix.m_pMatrix4f[ 9] + this->m_pMatrix4f[ 3] * inputMatrix.m_pMatrix4f[13];
    newMatrix.m_pMatrix4f[ 2] = this->m_pMatrix4f[ 0] * inputMatrix.m_pMatrix4f[ 2] + this->m_pMatrix4f[ 1] * inputMatrix.m_pMatrix4f[ 6] + this->m_pMatrix4f[ 2] * inputMatrix.m_pMatrix4f[10] + this->m_pMatrix4f[ 3] * inputMatrix.m_pMatrix4f[14];
    newMatrix.m_pMatrix4f[ 3] = this->m_pMatrix4f[ 0] * inputMatrix.m_pMatrix4f[ 3] + this->m_pMatrix4f[ 1] * inputMatrix.m_pMatrix4f[ 7] + this->m_pMatrix4f[ 2] * inputMatrix.m_pMatrix4f[11] + this->m_pMatrix4f[ 3] * inputMatrix.m_pMatrix4f[15];

    newMatrix.m_pMatrix4f[ 4] = this->m_pMatrix4f[ 4] * inputMatrix.m_pMatrix4f[ 0] + this->m_pMatrix4f[ 5] * inputMatrix.m_pMatrix4f[ 4] + this->m_pMatrix4f[ 6] * inputMatrix.m_pMatrix4f[ 8] + this->m_pMatrix4f[ 7] * inputMatrix.m_pMatrix4f[12];
    newMatrix.m_pMatrix4f[ 5] = this->m_pMatrix4f[ 4] * inputMatrix.m_pMatrix4f[ 1] + this->m_pMatrix4f[ 5] * inputMatrix.m_pMatrix4f[ 5] + this->m_pMatrix4f[ 6] * inputMatrix.m_pMatrix4f[ 9] + this->m_pMatrix4f[ 7] * inputMatrix.m_pMatrix4f[13];
    newMatrix.m_pMatrix4f[ 6] = this->m_pMatrix4f[ 4] * inputMatrix.m_pMatrix4f[ 2] + this->m_pMatrix4f[ 5] * inputMatrix.m_pMatrix4f[ 6] + this->m_pMatrix4f[ 6] * inputMatrix.m_pMatrix4f[10] + this->m_pMatrix4f[ 7] * inputMatrix.m_pMatrix4f[14];
    newMatrix.m_pMatrix4f[ 7] = this->m_pMatrix4f[ 4] * inputMatrix.m_pMatrix4f[ 3] + this->m_pMatrix4f[ 5] * inputMatrix.m_pMatrix4f[ 7] + this->m_pMatrix4f[ 6] * inputMatrix.m_pMatrix4f[11] + this->m_pMatrix4f[ 7] * inputMatrix.m_pMatrix4f[15];

    newMatrix.m_pMatrix4f[ 8] = this->m_pMatrix4f[ 8] * inputMatrix.m_pMatrix4f[ 0] + this->m_pMatrix4f[ 9] * inputMatrix.m_pMatrix4f[ 4] + this->m_pMatrix4f[10] * inputMatrix.m_pMatrix4f[ 8] + this->m_pMatrix4f[11] * inputMatrix.m_pMatrix4f[12];
    newMatrix.m_pMatrix4f[ 9] = this->m_pMatrix4f[ 8] * inputMatrix.m_pMatrix4f[ 1] + this->m_pMatrix4f[ 9] * inputMatrix.m_pMatrix4f[ 5] + this->m_pMatrix4f[10] * inputMatrix.m_pMatrix4f[ 9] + this->m_pMatrix4f[11] * inputMatrix.m_pMatrix4f[13];
    newMatrix.m_pMatrix4f[10] = this->m_pMatrix4f[ 8] * inputMatrix.m_pMatrix4f[ 2] + this->m_pMatrix4f[ 9] * inputMatrix.m_pMatrix4f[ 6] + this->m_pMatrix4f[10] * inputMatrix.m_pMatrix4f[10] + this->m_pMatrix4f[11] * inputMatrix.m_pMatrix4f[14];
    newMatrix.m_pMatrix4f[11] = this->m_pMatrix4f[ 8] * inputMatrix.m_pMatrix4f[ 3] + this->m_pMatrix4f[ 9] * inputMatrix.m_pMatrix4f[ 7] + this->m_pMatrix4f[10] * inputMatrix.m_pMatrix4f[11] + this->m_pMatrix4f[11] * inputMatrix.m_pMatrix4f[15];

    newMatrix.m_pMatrix4f[12] = this->m_pMatrix4f[12] * inputMatrix.m_pMatrix4f[ 0] + this->m_pMatrix4f[13] * inputMatrix.m_pMatrix4f[ 4] + this->m_pMatrix4f[14] * inputMatrix.m_pMatrix4f[ 8] + this->m_pMatrix4f[15] * inputMatrix.m_pMatrix4f[12];
    newMatrix.m_pMatrix4f[13] = this->m_pMatrix4f[12] * inputMatrix.m_pMatrix4f[ 1] + this->m_pMatrix4f[13] * inputMatrix.m_pMatrix4f[ 5] + this->m_pMatrix4f[14] * inputMatrix.m_pMatrix4f[ 9] + this->m_pMatrix4f[15] * inputMatrix.m_pMatrix4f[13];
    newMatrix.m_pMatrix4f[14] = this->m_pMatrix4f[12] * inputMatrix.m_pMatrix4f[ 2] + this->m_pMatrix4f[13] * inputMatrix.m_pMatrix4f[ 6] + this->m_pMatrix4f[14] * inputMatrix.m_pMatrix4f[10] + this->m_pMatrix4f[15] * inputMatrix.m_pMatrix4f[14];
    newMatrix.m_pMatrix4f[15] = this->m_pMatrix4f[12] * inputMatrix.m_pMatrix4f[ 3] + this->m_pMatrix4f[13] * inputMatrix.m_pMatrix4f[ 7] + this->m_pMatrix4f[14] * inputMatrix.m_pMatrix4f[11] + this->m_pMatrix4f[15] * inputMatrix.m_pMatrix4f[15];

    return(newMatrix);
}

OGLMatrix4f OGLMatrix4f::operator + (const OGLMatrix4f &inputMatrix)
{
    OGLMatrix4f newMatrix;

    newMatrix.m_pMatrix4f[ 0] = this->m_pMatrix4f[ 0] + inputMatrix.m_pMatrix4f[ 0];
    newMatrix.m_pMatrix4f[ 1] = this->m_pMatrix4f[ 1] + inputMatrix.m_pMatrix4f[ 1];
    newMatrix.m_pMatrix4f[ 2] = this->m_pMatrix4f[ 2] + inputMatrix.m_pMatrix4f[ 2];
    newMatrix.m_pMatrix4f[ 3] = this->m_pMatrix4f[ 3] + inputMatrix.m_pMatrix4f[ 3];

    newMatrix.m_pMatrix4f[ 4] = this->m_pMatrix4f[ 4] + inputMatrix.m_pMatrix4f[ 4];
    newMatrix.m_pMatrix4f[ 5] = this->m_pMatrix4f[ 5] + inputMatrix.m_pMatrix4f[ 5];
    newMatrix.m_pMatrix4f[ 6] = this->m_pMatrix4f[ 6] + inputMatrix.m_pMatrix4f[ 6];
    newMatrix.m_pMatrix4f[ 7] = this->m_pMatrix4f[ 7] + inputMatrix.m_pMatrix4f[ 7];

    newMatrix.m_pMatrix4f[ 8] = this->m_pMatrix4f[ 8] + inputMatrix.m_pMatrix4f[ 8];
    newMatrix.m_pMatrix4f[ 9] = this->m_pMatrix4f[ 9] + inputMatrix.m_pMatrix4f[ 9];
    newMatrix.m_pMatrix4f[10] = this->m_pMatrix4f[10] + inputMatrix.m_pMatrix4f[10];
    newMatrix.m_pMatrix4f[11] = this->m_pMatrix4f[11] + inputMatrix.m_pMatrix4f[11];

    newMatrix.m_pMatrix4f[12] = this->m_pMatrix4f[12] + inputMatrix.m_pMatrix4f[12];
    newMatrix.m_pMatrix4f[13] = this->m_pMatrix4f[13] + inputMatrix.m_pMatrix4f[13];
    newMatrix.m_pMatrix4f[14] = this->m_pMatrix4f[14] + inputMatrix.m_pMatrix4f[14];
    newMatrix.m_pMatrix4f[15] = this->m_pMatrix4f[15] + inputMatrix.m_pMatrix4f[15];

    return(newMatrix);
}

OGLMatrix4f OGLMatrix4f::operator - (const OGLMatrix4f &inputMatrix)
{
    OGLMatrix4f newMatrix;

    newMatrix.m_pMatrix4f[ 0] = this->m_pMatrix4f[ 0] - inputMatrix.m_pMatrix4f[ 0];
    newMatrix.m_pMatrix4f[ 1] = this->m_pMatrix4f[ 1] - inputMatrix.m_pMatrix4f[ 1];
    newMatrix.m_pMatrix4f[ 2] = this->m_pMatrix4f[ 2] - inputMatrix.m_pMatrix4f[ 2];
    newMatrix.m_pMatrix4f[ 3] = this->m_pMatrix4f[ 3] - inputMatrix.m_pMatrix4f[ 3];

    newMatrix.m_pMatrix4f[ 4] = this->m_pMatrix4f[ 4] - inputMatrix.m_pMatrix4f[ 4];
    newMatrix.m_pMatrix4f[ 5] = this->m_pMatrix4f[ 5] - inputMatrix.m_pMatrix4f[ 5];
    newMatrix.m_pMatrix4f[ 6] = this->m_pMatrix4f[ 6] - inputMatrix.m_pMatrix4f[ 6];
    newMatrix.m_pMatrix4f[ 7] = this->m_pMatrix4f[ 7] - inputMatrix.m_pMatrix4f[ 7];

    newMatrix.m_pMatrix4f[ 8] = this->m_pMatrix4f[ 8] - inputMatrix.m_pMatrix4f[ 8];
    newMatrix.m_pMatrix4f[ 9] = this->m_pMatrix4f[ 9] - inputMatrix.m_pMatrix4f[ 9];
    newMatrix.m_pMatrix4f[10] = this->m_pMatrix4f[10] - inputMatrix.m_pMatrix4f[10];
    newMatrix.m_pMatrix4f[11] = this->m_pMatrix4f[11] - inputMatrix.m_pMatrix4f[11];

    newMatrix.m_pMatrix4f[12] = this->m_pMatrix4f[12] - inputMatrix.m_pMatrix4f[12];
    newMatrix.m_pMatrix4f[13] = this->m_pMatrix4f[13] - inputMatrix.m_pMatrix4f[13];
    newMatrix.m_pMatrix4f[14] = this->m_pMatrix4f[14] - inputMatrix.m_pMatrix4f[14];
    newMatrix.m_pMatrix4f[15] = this->m_pMatrix4f[15] - inputMatrix.m_pMatrix4f[15];

    return(newMatrix);
}


OGLMatrix4f OGLMatrix4f::operator = (const OGLMatrix4f &inputMatrix)
{
    this->m_pMatrix4f[ 0] = inputMatrix.m_pMatrix4f[ 0];
    this->m_pMatrix4f[ 1] = inputMatrix.m_pMatrix4f[ 1];
    this->m_pMatrix4f[ 2] = inputMatrix.m_pMatrix4f[ 2];
    this->m_pMatrix4f[ 3] = inputMatrix.m_pMatrix4f[ 3];

    this->m_pMatrix4f[ 4] = inputMatrix.m_pMatrix4f[ 4];
    this->m_pMatrix4f[ 5] = inputMatrix.m_pMatrix4f[ 5];
    this->m_pMatrix4f[ 6] = inputMatrix.m_pMatrix4f[ 6];
    this->m_pMatrix4f[ 7] = inputMatrix.m_pMatrix4f[ 7];

    this->m_pMatrix4f[ 8] = inputMatrix.m_pMatrix4f[ 8];
    this->m_pMatrix4f[ 9] = inputMatrix.m_pMatrix4f[ 9];
    this->m_pMatrix4f[10] = inputMatrix.m_pMatrix4f[10];
    this->m_pMatrix4f[11] = inputMatrix.m_pMatrix4f[11];

    this->m_pMatrix4f[12] = inputMatrix.m_pMatrix4f[12];
    this->m_pMatrix4f[13] = inputMatrix.m_pMatrix4f[13];
    this->m_pMatrix4f[14] = inputMatrix.m_pMatrix4f[14];
    this->m_pMatrix4f[15] = inputMatrix.m_pMatrix4f[15];

    return(*this);
}

OGLVector4f OGLMatrix4f::operator * (const OGLVector4f &inputVector)
{
    OGLVector4f newVector;

    newVector.x = this->m_pMatrix4f[ 0] * inputVector.x + this->m_pMatrix4f[ 1] * inputVector.y + this->m_pMatrix4f[ 2] * inputVector.z + this->m_pMatrix4f[ 3] * inputVector.w;
    newVector.y = this->m_pMatrix4f[ 4] * inputVector.x + this->m_pMatrix4f[ 5] * inputVector.y + this->m_pMatrix4f[ 6] * inputVector.z + this->m_pMatrix4f[ 7] * inputVector.w;
    newVector.z = this->m_pMatrix4f[ 8] * inputVector.x + this->m_pMatrix4f[ 9] * inputVector.y + this->m_pMatrix4f[10] * inputVector.z + this->m_pMatrix4f[11] * inputVector.w;
    newVector.w = this->m_pMatrix4f[12] * inputVector.x + this->m_pMatrix4f[13] * inputVector.y + this->m_pMatrix4f[14] * inputVector.z + this->m_pMatrix4f[15] * inputVector.w;

    return(newVector);
}
