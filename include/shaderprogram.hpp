#pragma once
#include <list>
#include <string>

namespace Prova
{
  class Color;
  class Matrix;
  class Mesh;
  class Texture;
  class Vector2;
  class Vector3;
  class Vector4;

  class ShaderProgram
  {
    public:
      enum DrawMode {
        POINTS = 0,
        LINES = 1,
        LINE_LOOP = 2,
        LINE_STRIP = 3,
        TRIANGLES = 4,
        TRIANGLE_STRIP = 5,
        TRIANGLE_FAN = 6
      };

      ShaderProgram();
      unsigned int id;
      unsigned int GetVariable(std::string name);
      unsigned int GetAttribute(std::string name);
      unsigned int GetUniform(std::string name);
      void SetVector2(std::string name, Vector2 vector);
      void SetVector3(std::string name, Vector3 vector);
      void SetVector4(std::string name, Vector4 vector);
      void SetVector4(std::string name, Color color);
      void SetMatrix(std::string name, Matrix matrix);
      void SetTexture(int sampler, Texture texture);
      void SetTexture(int sampler, unsigned int texture);
      void SetTexture(std::string name, Texture texture);
      void SetTexture(std::string name, unsigned int texture);
      void DrawMesh(DrawMode mode, Mesh& mesh);
      // from file
      void LoadFragmentShader(std::string sourceFile);
      void LoadVertexShader(std::string sourceFile);
      void LoadGeometryShader(std::string sourceFile);
      // from source
      void AttachFragmentShader(std::string source);
      void AttachVertexShader(std::string source);
      void AttachGeometryShader(std::string source);
      void Link();
      void PrintProgramLog();
      ~ShaderProgram();
    private:
      std::list<unsigned int> _shaders;
      void LoadShader(unsigned int shaderType, std::string sourceFile);
      void CompileShader(unsigned int shaderType, std::string source);
      void PrintShaderLog(unsigned int shader);
  };
}