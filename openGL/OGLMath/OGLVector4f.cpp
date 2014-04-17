#include "./OGLVector4f.h"
#include <cmath>

OGLVector4f::OGLVector4f(void)
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    this->w = 1.0f;
}

OGLVector4f::OGLVector4f(const OGLVector4f &v4f)
{
    this->x = v4f.x;
    this->y = v4f.y;
    this->z = v4f.z;
    this->w = v4f.w;
}

OGLVector4f::OGLVector4f(float x, float y, float z)
{
    this->x =    x;
    this->y =    y;
    this->z =    z;
    this->w = 1.0f;
}

OGLVector4f::OGLVector4f(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

OGLVector4f OGLVector4f::operator + (const OGLVector4f &v4f)
{
    float x = this->x + v4f.x;
    float y = this->y + v4f.y;
    float z = this->z + v4f.z;

    return(OGLVector4f(x, y, z));
}

OGLVector4f OGLVector4f::operator - (const OGLVector4f &v4f)
{
    float x = this->x - v4f.x;
    float y = this->y - v4f.y;
    float z = this->z - v4f.z;

    return(OGLVector4f(x, y, z));
}

OGLVector4f OGLVector4f::operator = (const OGLVector4f &v4f)
{
    this->x = v4f.x;
    this->y = v4f.y;
    this->z = v4f.z;
    this->w = v4f.w;

    return(*this);
}

OGLVector4f OGLVector4f::operator * (float n)
{
    float x = this->x * n;
    float y = this->y * n;
    float z = this->z * n;

    return(OGLVector4f(x, y, z));
}

OGLVector4f OGLVector4f::operator / (float n)
{
    float x = this->x / n;
    float y = this->y / n;
    float z = this->z / n;

    return(OGLVector4f(x, y, z));
}

OGLVector4f OGLVector4f::normalize(void)
{
    float l = this->length();
    float x = this->x / l;
    float y = this->y / l;
    float z = this->z / l;

    return(OGLVector4f(x, y, z));
}

OGLVector4f OGLVector4f::negative (void)
{
    float x = -this->x;
    float y = -this->y;
    float z = -this->z;

    return(OGLVector4f(x, y, z));
}

OGLVector4f OGLVector4f::cross(const OGLVector4f &v4f)
{
    float x = this->y * v4f.z - this->z * v4f.y;
    float y = this->z * v4f.x - this->x * v4f.z;
    float z = this->x * v4f.y - this->y * v4f.x;
    
    return(OGLVector4f(x, y, z));
}

float OGLVector4f::dot(const OGLVector4f &v4f)
{
    float x = this->x * v4f.x;
    float y = this->y * v4f.y;
    float z = this->z * v4f.z;
    
    return(x + y + z);
}

float OGLVector4f::length(void)
{
    float x = this->x * this->x;
    float y = this->y * this->y;
    float z = this->z * this->z;

    return(std::sqrt(x + y + z));
}
