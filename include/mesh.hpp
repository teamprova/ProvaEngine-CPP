#pragma once
#include "matrix.hpp"

class Matrix;

class Mesh
{
  public:
    Mesh();
    Matrix transform = Matrix::Identity();
    unsigned int VAO;
    void SetVBO(float[], int, int);
    void SetIBO(unsigned int[], int);
  private:
    void CreateBuffer(unsigned int*);
    unsigned int VBO = -1;
    unsigned int IBO = -1;
    int _indexCount;
};