#include "OGLShaderProgram.h"

OGLShaderProgram::OGLShaderProgram(OGLShader *vs, OGLShader *fs)
{
    this->mProgramHandler = glCreateProgram();
    this->mFragmentShader = fs; this->mVertexShader = vs;

    if(vs != NULL && vs->isLoaded()) 
    {
        glAttachShader(this->mProgramHandler, vs->getShaderHandler());
    }

    if(fs != NULL && fs->isLoaded())
    {
        glAttachShader(this->mProgramHandler, fs->getShaderHandler());
    }

    this->mInfoLog.assign("No Errors");
    this->mIsLinked = this->mLinkProgram();
}


OGLShaderProgram::~OGLShaderProgram(void)
{
    if(this->mVertexShader != NULL)
    {
        glDetachShader(this->mProgramHandler, this->mVertexShader->getShaderHandler());
        delete(this->mVertexShader);
    }

    if(this->mFragmentShader != NULL)
    {
        glDetachShader(this->mProgramHandler, this->mFragmentShader->getShaderHandler());
        delete(this->mFragmentShader);
    }

    this->mInfoLog.clear();
    glDeleteProgram(this->mProgramHandler);
}


bool OGLShaderProgram::mLinkProgram(void)
{
    int status;
    glLinkProgram(this->mProgramHandler);
    glGetProgramiv(this->mProgramHandler, GL_LINK_STATUS, &status); 
    
    if(status == GL_FALSE)
    {
        this->mInfoLog.clear();
        int iLength; int cWritten;
        glGetProgramiv(this->mProgramHandler, GL_INFO_LOG_LENGTH, &iLength);
        
        char *pError = (char *) malloc (iLength * sizeof(char) + 1);
        ZeroMemory(pError, iLength * sizeof(char) + 1);

        glGetProgramInfoLog(this->mProgramHandler, iLength, &cWritten, pError);
        this->mInfoLog.assign(pError);

        delete(pError);
        return(false);
    }

    return(true);
}

std::string OGLShaderProgram::getError(void)
{
    std::string Error("");

    Error.append("VertexShader: "   + this->mVertexShader->getError() + "\n");
    Error.append("FragmentShader: " + this->mFragmentShader->getError() + "\n");
    Error.append("ProgramShader: "  + this->mInfoLog + "\n");

    return(Error);
}

bool OGLShaderProgram::isLinked()
{
    return(this->mIsLinked);
}

OGLShader *OGLShaderProgram::getVertexShader(void)
{
    return(this->mVertexShader);
}

OGLShader *OGLShaderProgram::getFragmentShader(void)
{
    return(this->mFragmentShader);
}

void OGLShaderProgram::activeProgram(void)
{
    glUseProgram(this->mProgramHandler);
}

void OGLShaderProgram::releseProgram(void)
{
    glUseProgram(0);
}

void OGLShaderProgram::setUniformValue(std::string uName, float uValue)
{
    int uLocation = glGetUniformLocation(this->mProgramHandler, uName.c_str());
    if(uLocation > -1)
    {
        glUniform1f(uLocation, uValue);
    }
}

void OGLShaderProgram::setUniformVector4f(std::string uName, float *uValue)
{
    int uLocation = glGetUniformLocation(this->mProgramHandler, uName.c_str());
    if(uLocation > -1)
    {
        glUniform4fv(uLocation, 1, uValue);
    }
}

void OGLShaderProgram::setUniformMatrix4(std::string uName, bool transpose, float *uValue)
{
    int uLocation = glGetUniformLocation(this->mProgramHandler, uName.c_str());
    if(uLocation > -1)
    {
        glUniformMatrix4fv(uLocation, 1, transpose, uValue);
    }
}

int OGLShaderProgram::getLocation(std::string uName)
{
    return(glGetUniformLocation(this->mProgramHandler, uName.c_str()));
}
