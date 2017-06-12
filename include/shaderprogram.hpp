#pragma once
#include <string>
#include <list>

namespace Prova
{
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
      // from file
      void LoadFragmentShader(std::string);
      void LoadVertexShader(std::string);
      void LoadGeometryShader(std::string);
      // from source
      void AttachFragmentShader(std::string);
      void AttachVertexShader(std::string);
      void AttachGeometryShader(std::string);
      void Link();
      void PrintProgramLog();
      ~ShaderProgram();
    private:
      void LoadShader(unsigned int, std::string);
      void CompileShader(unsigned int, std::string);
      void PrintShaderLog(unsigned int shader);
      std::list<unsigned int> _shaders;
  };
}