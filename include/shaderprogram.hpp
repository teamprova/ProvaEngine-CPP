#pragma once
#include <string>
#include <list>

class Matrix;
class Vector2;
class Vector3;
class Vector4;

class ShaderProgram
{
  public:
    unsigned int id;
    ShaderProgram();
    unsigned int GetVariable(std::string);
    unsigned int GetAttribute(std::string);
    unsigned int GetUniform(std::string);
    void SetVector2(std::string, Vector2);
    void SetVector3(std::string, Vector3);
    void SetVector4(std::string, Vector4);
    void SetMatrix(std::string, Matrix);
    void SetTexture(int, unsigned int);
    void SetTexture(std::string, unsigned int);
    void AttachFragmentShader(std::string);
    void AttachVertexShader(std::string);
    void Link();
    void PrintProgramLog();
    ~ShaderProgram();
  private:
    void CompileShader(unsigned int, std::string);
    void PrintShaderLog(unsigned int shader);
    std::list<unsigned int> _shaders;
};