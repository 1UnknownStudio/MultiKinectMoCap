#include "./OGLShader.h"

OGLShader::OGLShader(char *shaderPath, unsigned int shaderType)
{
    this->mShaderHandler = 0;
    this->mShaderType    = shaderType;

    this->mInfoLog.assign("No Errors");
    this->mShaderPath.assign(shaderPath);

    this->mIsLoaded = this->mLoadShader();
}


OGLShader::~OGLShader(void)
{
    glDeleteShader(this->mShaderHandler);
    this->mShaderPath.clear();
    this->mInfoLog.clear();
}

bool OGLShader::mLoadShader(void)
{
    FILE *pFile = NULL;
    
    if(fopen_s(&pFile, this->mShaderPath.c_str(), "rt") != 0)
    {
        this->mInfoLog.clear();
        this->mInfoLog.assign("Error opening file: " + this->mShaderPath);

        return(false);
    }

    std::string sContent = "";
    char fContent[255] = {0};
    
    while(fgets(fContent, 255, pFile))
    {
        sContent.append(fContent);
    }
    fclose(pFile);

    this->mShaderHandler = glCreateShader(this->mShaderType);
    const char *c_str = sContent.c_str();
    
    glShaderSource(this->mShaderHandler, 1, &c_str, NULL);
    glCompileShader(this->mShaderHandler);
    
    int status;
    glGetShaderiv(this->mShaderHandler, GL_COMPILE_STATUS, &status); 
    
    if(status == GL_FALSE)
    {
        this->mInfoLog.clear();
        int iLength; int cWritten;
        glGetShaderiv(this->mShaderHandler, GL_INFO_LOG_LENGTH, &iLength);
        
        char *sError = (char *) malloc (iLength * sizeof(char) + 1);
        ZeroMemory(sError, iLength * sizeof(char) + 1);

        glGetShaderInfoLog(this->mShaderHandler, iLength, &cWritten, sError);
        this->mInfoLog.assign(sError);

        delete(sError);
        return(false);
    }
    
    return(true);
}

unsigned int OGLShader::getShaderHandler(void)
{
    return(this->mShaderHandler);
}

unsigned int OGLShader::getShaderType(void)
{
    return(this->mShaderType);
}

std::string OGLShader::getError(void)
{
    return(this->mInfoLog);
}

bool OGLShader::isLoaded(void)
{
    return(this->mIsLoaded);
}
