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
      void SetVBO(float[], int, int);
      void SetIBO(unsigned int[], int);
      ~Mesh();
    private:
      void CreateBuffer(unsigned int&);
      unsigned int VBO = -1;
      unsigned int IBO = -1;
      int _indexCount;
  };
}