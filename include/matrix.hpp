#pragma once

namespace Prova
{
  class Vector3;
  class Vector4;

  class Matrix
  {
    public:
      static Matrix Identity();
      static Matrix Ortho(float, float, float, float, float, float);
      static Matrix Perspective(float, float, float, float, float);
      Matrix();
      Matrix RotateX(float);
      Matrix RotateY(float);
      Matrix RotateZ(float);
      Matrix Scale(Vector3);
      Matrix Scale(float, float, float);
      Matrix Translate(Vector3);
      Matrix Translate(float, float, float);
      float* operator[](int);
      //Matrix& operator+=(Vector3);
      //Matrix& operator-=(Vector3);
      //Matrix& operator*=(float);
      //Matrix& operator/=(float);
      Matrix operator+(Matrix);
      Matrix operator-(Matrix);
      Matrix operator*(Matrix&);
      Vector4 operator*(Vector4);
      Matrix operator*(float);
      Matrix operator/(float);
    private:
      float _mat[4][4];
  };
}