#include "./OGLMatrix4f.h"

OGLMatrix4f::OGLMatrix4f(void)
{
    this->mMatrix4f[ 0] = 1;  
    this->mMatrix4f[ 1] = 0;  
    this->mMatrix4f[ 2] = 0;  
    this->mMatrix4f[ 3] = 0;

    this->mMatrix4f[ 4] = 0;  
    this->mMatrix4f[ 5] = 1;  
    this->mMatrix4f[ 6] = 0;  
    this->mMatrix4f[ 7] = 0;

    this->mMatrix4f[ 8] = 0;  
    this->mMatrix4f[ 9] = 0;  
    this->mMatrix4f[10] = 1;  
    this->mMatrix4f[11] = 0;

    this->mMatrix4f[12] = 0;  
    this->mMatrix4f[13] = 0;  
    this->mMatrix4f[14] = 0; 
    this->mMatrix4f[15] = 1;
}

OGLMatrix4f::~OGLMatrix4f(void)
{
}

float *OGLMatrix4f::getMatrix(void)
{
    return(this->mMatrix4f);
}

void OGLMatrix4f::setIdentity(void)
{
    this->mMatrix4f[ 0] = 1;  
    this->mMatrix4f[ 1] = 0;  
    this->mMatrix4f[ 2] = 0;  
    this->mMatrix4f[ 3] = 0;

    this->mMatrix4f[ 4] = 0; 
    this->mMatrix4f[ 5] = 1;  
    this->mMatrix4f[ 6] = 0;  
    this->mMatrix4f[ 7] = 0;

    this->mMatrix4f[ 8] = 0;  
    this->mMatrix4f[ 9] = 0;  
    this->mMatrix4f[10] = 1;  
    this->mMatrix4f[11] = 0;

    this->mMatrix4f[12] = 0;  
    this->mMatrix4f[13] = 0;  
    this->mMatrix4f[14] = 0;  
    this->mMatrix4f[15] = 1;
}

void OGLMatrix4f::setLookAt(OGLVector3f &eyePos, OGLVector3f &lookAt, OGLVector3f &upVector)
{
    OGLVector3f zAxis = (eyePos - lookAt).normalize(); 
    OGLVector3f xAxis = (upVector.cross(zAxis)).normalize();
    OGLVector3f yAxis = (zAxis.cross(xAxis)).normalize();
    
    this->mMatrix4f[ 0] = xAxis.x;              
    this->mMatrix4f[ 1] = yAxis.x;              
    this->mMatrix4f[ 2] = zAxis.x;              
    this->mMatrix4f[ 3] = 0;

    this->mMatrix4f[ 4] = xAxis.y;             
    this->mMatrix4f[ 5] = yAxis.y;              
    this->mMatrix4f[ 6] = zAxis.y;             
    this->mMatrix4f[ 7] = 0;

    this->mMatrix4f[ 8] = xAxis.z;              
    this->mMatrix4f[ 9] = yAxis.z;             
    this->mMatrix4f[10] = zAxis.z;              
    this->mMatrix4f[11] = 0;

    this->mMatrix4f[12] = -(xAxis.dot(eyePos)); 
    this->mMatrix4f[13] = -(yAxis.dot(eyePos)); 
    this->mMatrix4f[14] = -(zAxis.dot(eyePos)); 
    this->mMatrix4f[15] = 1;
}

void OGLMatrix4f::setFrustum(float fovAngle, float aspectRatio, float zNear, float zFar)
{
    float fScale = zNear * std::tanf(fovAngle * 3.14159265f / 360.0f);

    float fRight = aspectRatio * fScale;
    float fLeft  = -fRight;

    float fTop    = fScale;
    float fBotton = -fTop;

    this->mMatrix4f[ 0] =  2.0f * zNear / (fRight - fLeft);
    this->mMatrix4f[ 1] =  0.0f;  
    this->mMatrix4f[ 2] =  0.0f; 
    this->mMatrix4f[ 3] =  0.0f;

    this->mMatrix4f[ 4] =  0.0f;  
    this->mMatrix4f[ 5] =  2.0f * zNear / (fTop - fBotton);  
    this->mMatrix4f[ 6] =  0.0f;   
    this->mMatrix4f[ 7] =  0.0f;

    this->mMatrix4f[ 8] =  (fRight + fLeft) / (fRight - fLeft);  
    this->mMatrix4f[ 9] =  (fTop + fBotton) / (fTop - fBotton);  
    this->mMatrix4f[10] = -((zFar + zNear) / (zFar - zNear));  
    this->mMatrix4f[11] = -1.0f;

    this->mMatrix4f[12] =  0.0f; 
    this->mMatrix4f[13] =  0.0f;  
    this->mMatrix4f[14] = -(2.0f * zFar * zNear / (zFar - zNear));  
    this->mMatrix4f[15] =  0.0f;
}
