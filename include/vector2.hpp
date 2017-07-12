#pragma once
#include "vector3.hpp" 

namespace Prova
{
  class Vector2 : public Vector3 
  {
    public:
      Vector2();
      Vector2(float x, float y);
      Vector2 Normalize();
      float GetAngle();
      float DistanceFrom(Vector2 vector);
      Vector2& operator+=(Vector2 vector);
      Vector2& operator-=(Vector2 vector);
      Vector2& operator*=(float a);
      Vector2& operator/=(float a);
      Vector2 operator+(Vector2 vector);
      Vector2 operator-(Vector2 vector);
      Vector2 operator-();
      Vector2 operator*(float a);
      Vector2 operator/(float a);
    private:
      using Vector3::z;
  };
}