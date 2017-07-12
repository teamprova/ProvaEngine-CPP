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
      Matrix RotateX(float degrees);
      Matrix RotateY(float degrees);
      Matrix RotateZ(float degrees);
      Matrix Scale(Vector3 vector);
      Matrix Scale(float x, float y, float z);
      Matrix Translate(Vector3 vector);
      Matrix Translate(float x, float y, float z);
      float* operator[](int i);
      //Matrix& operator+=(Vector3);
      //Matrix& operator-=(Vector3);
      //Matrix& operator*=(float);
      //Matrix& operator/=(float);
      Matrix operator+(Matrix matrix);
      Matrix operator-(Matrix matrix);
      Matrix operator*(Matrix& matrix);
      Vector4 operator*(Vector4 vector);
      Matrix operator*(float a);
      Matrix operator/(float a);
    private:
      float _mat[4][4];
  };
}