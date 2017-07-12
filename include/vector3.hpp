#pragma once
#include "vector4.hpp"

namespace Prova
{
  class Vector3 : public Vector4
  {
    public:
      Vector3();
      Vector3(float x, float y, float z);
      Vector3 Normalize();
      float DistanceFrom(Vector3 vector);
      Vector3& operator+=(Vector3 vector);
      Vector3& operator-=(Vector3 vector);
      Vector3& operator*=(float a);
      Vector3& operator/=(float a);
      Vector3 operator+(Vector3 vector);
      Vector3 operator-(Vector3 vector);
      Vector3 operator-();
      Vector3 operator*(float a);
      Vector3 operator/(float a);
    private:
      using Vector4::w;
  };
}