#pragma once
#include <Windows.h>
#include <gl/glew.h>

#include <cstring>
#include <string>

class OGLShader
{
    private:
        unsigned int mShaderHandler;
        unsigned int mShaderType;

        std::string mShaderPath;
        std::string mInfoLog;

        bool mIsLoaded;
        bool mLoadShader (void);

    public:
        OGLShader        (char *shaderPath, unsigned int shaderType);
        ~OGLShader       (void);

        unsigned int     getShaderHandler       (void);
        unsigned int     getShaderType          (void); 

        std::string      getError               (void);
        bool             isLoaded               (void);
};
