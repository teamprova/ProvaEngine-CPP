#pragma once
#include "matrix.hpp"

namespace Prova
{
  class Matrix;
  class ShaderProgram;

  class Mesh
  {
    friend class ShaderProgram;
    
    public:
      Mesh();
      Matrix transform = Matrix::Identity();
      unsigned int VAO;
      void SetVBO(float vertices[], int length, int dimensions);
      void SetIBO(unsigned int indexes[], int length);
      ~Mesh();
    private:
      void CreateBuffer(unsigned int& buffer);
      unsigned int VBO = -1;
      unsigned int IBO = -1;
      int _indexCount;
  };
}