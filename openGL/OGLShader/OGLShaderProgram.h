#pragma once

#include <Windows.h>
#include <gl/glew.h>

#include <cstring>
#include <string>

#include <vector>
#include <string>

#include "./OGLShader.h"

class OGLShaderProgram
{
    private:
        std::string  mInfoLog;
        unsigned int mProgramHandler;

        OGLShader *mVertexShader;
        OGLShader *mFragmentShader;

        bool mIsLinked;
        bool mLinkProgram (void);

    public:
        OGLShaderProgram        (OGLShader *vs, OGLShader *fs);
        ~OGLShaderProgram       (void);

        unsigned int getProgramHandler  (void);

        std::string getError            (void);
        bool        isLinked            (void);

        OGLShader   *getVertexShader    (void);
        OGLShader   *getFragmentShader  (void);

        void        activeProgram       (void);
        void        releseProgram       (void);

        void        setUniformValue     (std::string uName, float uValue);
        void        setUniformMatrix4   (std::string uName, float *uValue);
};
