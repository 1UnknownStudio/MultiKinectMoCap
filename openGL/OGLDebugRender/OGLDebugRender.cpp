#include "./OGLDebugRender.h"
#include <vector>

OGLDebugRender::OGLDebugRender(void)
{
}

OGLDebugRender::~OGLDebugRender(void)
{
}

void OGLDebugRender::drawAxis(OGLVector4f &start, float sz)
{
    this->drawLine(start, OGLVector4f(sz, 0.0f, 0.0f) + start, OGLVector4f(1.0, 0.0, 0.0));
    this->drawLine(start, OGLVector4f(0.0f, sz, 0.0f) + start, OGLVector4f(0.0, 1.0, 0.0));
    this->drawLine(start, OGLVector4f(0.0f, 0.0f, sz) + start, OGLVector4f(0.0, 0.0, 1.0));
}

void OGLDebugRender::drawGrid(int nLines, float sz, OGLVector4f &color)
{
    float hSz = sz / 2.0f;

    for(int i = 0; i <= nLines; i++)
    {
        this->drawLine(OGLVector4f(-hSz + (i * sz) / nLines, 0.0f, -hSz), OGLVector4f(-hSz + (i * sz) / nLines, 0.0f, hSz), color);
    }

    for(int i = 0; i <= nLines; i++)
    {
        this->drawLine(OGLVector4f(-hSz, 0.0f, -hSz + (i * sz) / nLines), OGLVector4f(hSz, 0.0f, -hSz + (i * sz) / nLines), color);
    }
}

void OGLDebugRender::drawLine(OGLVector4f &start, OGLVector4f &end, OGLVector4f &color)
{
    float v[6] = {start.x, start.y, start.z, end.x, end.y, end.z};
    float c[6] = {color.x, color.y, color.z, color.x, color.y, color.z};

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, v);
    glColorPointer(3, GL_FLOAT, 0, c);
    glDrawArrays(GL_LINES, 0, 2);
    
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void OGLDebugRender::drawPoint(OGLVector4f &vPoint, OGLVector4f &vColor, float sz)
{
    float v[3] = { vPoint.x, vPoint.y, vPoint.z };
    float c[3] = { vColor.x, vColor.y, vColor.z };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glPointSize(sz);
    glVertexPointer(3, GL_FLOAT, 0, v);
    glColorPointer(3, GL_FLOAT, 0, c);
    glDrawArrays(GL_POINTS, 0, 1);
    glPointSize(1.0);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
