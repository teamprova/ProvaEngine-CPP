#pragma once
#include <unordered_map>

namespace Prova
{
  class Rect;

  class Vector4
  {
    public:
      Vector4();
      Vector4(Rect rect);
      Vector4(float x, float y, float z, float w);
      float x;
      float y;
      float z;
      float w;
      Vector4 Normalize();
      float GetMagnitude();
      float DistanceFrom(Vector4 vector);
      Vector4& operator+=(Vector4 vector);
      Vector4& operator-=(Vector4 vector);
      Vector4& operator*=(float a);
      Vector4& operator/=(float a);
      Vector4 operator+(Vector4 vector);
      Vector4 operator-(Vector4 vector);
      Vector4 operator-();
      Vector4 operator*(float a);
      Vector4 operator/(float a);
      bool operator==(const Vector4 vector) const;
      bool operator!=(const Vector4 vector) const;
  };
}