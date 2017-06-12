#include <math.h>
#include "matrix.hpp"
#include "vector4.hpp"
#include "vector3.hpp"

using namespace Prova;

/*/ Debugging
#include <iostream>
void PrintMatrix(Matrix m)
{
  for(int r = 0; r < 4; r++)
  {
    for(int c = 0; c < 4; c++)
      std::cout << m[r][c] << " ";
    std::cout << "\n";
  }
  std::cout << "\n";
}//*/

Matrix::Matrix()
{
  for(int y = 0; y < 4; y++)
    for(int x = 0; x < 4; x++)
      _mat[y][x] = 0;
}

Matrix Matrix::Identity()
{
  Matrix identity;

  for(int i = 0; i < 4; i++)
    identity[i][i] = 1;
  
  return identity;
}

Matrix Matrix::Ortho(float left, float right, float bottom, float top, float near, float far)
{
  /*| 2/x_max   0        0                     -1             |
  *|    0  -2/y_max     0                      1             |
  *|    0      0   2/(zFar-zNear)  (zNear+zFar)/(zNear-zFar) |
  *|    0      0        0                      1             |
  */
  
  Matrix ortho;
  ortho[0][0] = 2/(right - left);
  ortho[1][1] = 2/(top - bottom);
  ortho[2][2] = 2/(far - near);
  ortho[2][3] = (near + far)/(near - far);

  ortho[0][3] = -1;
  ortho[1][3] = 1;
  ortho[3][3] = 1;
  
  return ortho;
}

Matrix Matrix::RotateX(float degrees)
{
  float angle = degrees / 180 * M_PI;

  Matrix rotation = Matrix::Identity();
  rotation[1][1] = cos(-angle);
  rotation[1][2] = -sin(-angle);
  rotation[2][1] = sin(-angle);
  rotation[2][2] = cos(-angle);

  return rotation * *this;
}

Matrix Matrix::RotateY(float degrees)
{
  float angle = degrees / 180 * M_PI;

  Matrix rotation = Matrix::Identity();
  rotation[0][0] = cos(-angle);
  rotation[0][2] = sin(-angle);
  rotation[2][0] = -sin(-angle);
  rotation[2][2] = cos(-angle);

  return rotation * *this;
}

Matrix Matrix::RotateZ(float degrees)
{
  float angle = degrees / 180 * M_PI;

  Matrix rotation = Matrix::Identity();
  rotation[0][0] = cos(-angle);
  rotation[0][1] = -sin(-angle);
  rotation[1][0] = sin(-angle);
  rotation[1][1] = cos(-angle);

  return rotation * *this;
}

Matrix Matrix::Scale(Vector3 vector)
{
  return Scale(vector.x, vector.y, vector.z);
}

Matrix Matrix::Scale(float x, float y, float z)
{
  Matrix result;

  for(int col = 0; col < 4; col++)
  {
    result[0][col] = _mat[0][col] * x;
    result[1][col] = _mat[1][col] * y;
    result[2][col] = _mat[2][col] * z;
    result[3][col] = _mat[3][col];
  }

  return result;
}

Matrix Matrix::Translate(Vector3 vector)
{
  return Translate(vector.x, vector.y, vector.z);
}

Matrix Matrix::Translate(float x, float y, float z)
{
  Matrix translation = Matrix::Identity();
  translation[0][3] = x;
  translation[1][3] = y;
  translation[2][3] = z;

  return translation * *this;
}

float* Matrix::operator[](int i)
{
  return _mat[i];
}

Matrix Matrix::operator+(Matrix matrix)
{
  for(int y = 0; y < 4; y++)
    for(int x = 0; x < 4; x++)
      matrix[y][x] += _mat[x][y];

  return matrix;
}

Matrix Matrix::operator-(Matrix matrix)
{
  for(int y = 0; y < 4; y++)
    for(int x = 0; x < 4; x++)
      matrix[y][x] -= _mat[y][x];

  return matrix;
}

Matrix Matrix::operator*(Matrix matrix)
{
  Matrix result;

  for(int y = 0; y < 4; y++)
    for(int x = 0; x < 4; x++)
      for(int i = 0; i < 4; i++)
        result[y][x] += _mat[y][i] * matrix[i][x];

  return result;
}

Vector4 Matrix::operator*(Vector4 vector)
{
  Vector4 result;

  for(int col = 0; col < 4; col++)
  {
    result.x += _mat[0][col] * vector.x;
    result.y += _mat[1][col] * vector.y;
    result.z += _mat[2][col] * vector.z;
    result.w += _mat[3][col] * vector.w;
  }

  return result;
}

Matrix Matrix::operator*(float a)
{
  Matrix matrix;

  for(int y = 0; y < 4; y++)
    for(int x = 0; x < 4; x++)
      matrix[y][x] = _mat[y][x] * a;

  return matrix;
}

Matrix Matrix::operator/(float a)
{
  Matrix matrix;

  for(int y = 0; y < 4; y++)
    for(int x = 0; x < 4; x++)
      matrix[y][x] = _mat[y][x] / a;

  return matrix;
}