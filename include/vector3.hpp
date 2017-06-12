#pragma once
#include "vector4.hpp"

namespace Prova
{
  class Vector3 : public Vector4
  {
    public:
      Vector3();
      Vector3(float, float, float);
      Vector3 Normalize();
      float DistanceFrom(Vector3);
      Vector3& operator+=(Vector3);
      Vector3& operator-=(Vector3);
      Vector3& operator*=(float);
      Vector3& operator/=(float);
      Vector3 operator+(Vector3);
      Vector3 operator-(Vector3);
      Vector3 operator-();
      Vector3 operator*(float);
      Vector3 operator/(float);
    private:
      using Vector4::w;
  };
}