#include "./OGLDebugRender.h"
#include <vector>

OGLDebugRender::OGLDebugRender()
{
}

OGLDebugRender::~OGLDebugRender()
{
}

void OGLDebugRender::drawAxis(OGLVector3f &start, float sz)
{
	this->drawLine(start, OGLVector3f(sz, 0.0f, 0.0f) + start, OGLVector3f(1.0, 0.0, 0.0));
	this->drawLine(start, OGLVector3f(0.0f, sz, 0.0f) + start, OGLVector3f(0.0, 1.0, 0.0));
	this->drawLine(start, OGLVector3f(0.0f, 0.0f, sz) + start, OGLVector3f(0.0, 0.0, 1.0));
}

void OGLDebugRender::drawGrid(int nLines, float sz, OGLVector3f &color)
{
	float hSz = sz / 2.0f;

	for(int i = 0; i <= nLines; i++)
	{
		this->drawLine(OGLVector3f(-hSz + (i * sz) / nLines, 0.0f, -hSz), OGLVector3f(-hSz + (i * sz) / nLines, 0.0f, hSz), color);
	}

	for(int i = 0; i <= nLines; i++)
	{
		this->drawLine(OGLVector3f(-hSz, 0.0f, -hSz + (i * sz) / nLines), OGLVector3f(hSz, 0.0f, -hSz + (i * sz) / nLines), color);
	}
}

void OGLDebugRender::drawSphere(float sRadius, int nSections, OGLVector3f &color)
{
    float pI = 3.14159265359f;
    float sSection = pI / nSections;

	for(float phi = 0; phi < 2.0f * pI; phi += sSection)
	{
		for(float theta = 0; theta < pI; theta += sSection)
		{
            OGLVector3f startP(sRadius * std::sinf(phi) * std::cosf(theta),
                               sRadius * std::cosf(phi),
                               sRadius * std::sinf(phi) * std::sinf(theta));
     
            OGLVector3f endP(sRadius * std::sinf(phi) * std::cosf(theta + sSection),
                             sRadius * std::cosf(phi),
                             sRadius * std::sinf(phi) * std::sinf(theta + sSection));

            this->drawLine(startP, endP, OGLVector3f(1.0f, 1.0f, 1.0f));
		}
	}
}

void OGLDebugRender::drawLine(OGLVector3f &start, OGLVector3f &end, OGLVector3f &color)
{
	float v[6] = {start.x, start.y, start.z, end.x, end.y, end.z};
	float c[6] = {color.x, color.y, color.z, color.x, color.y, color.z};

	glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, v);
			glColorPointer(3, GL_FLOAT, 0, c);
			glDrawArrays(GL_LINES, 0, 6);
		glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void OGLDebugRender::drawPoint(OGLVector3f &vPoint, OGLVector3f &vColor, float sz)
{
	float v[3] = { vPoint.x, vPoint.y, vPoint.z };
	float c[3] = { vColor.x, vColor.y, vColor.z };

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
		glPointSize(sz);
			glVertexPointer(3, GL_FLOAT, 0, v);
			glColorPointer(3, GL_FLOAT, 0, c);
			glDrawArrays(GL_POINTS, 0, 3);
		glPointSize(1.0);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}