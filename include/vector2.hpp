#pragma once
#include "vector3.hpp" 

class Vector2 : public Vector3 
{
  public:
    Vector2();
    Vector2(float, float);
    Vector2 Normalize();
    float GetAngle();
    float DistanceFrom(Vector2);
    Vector2& operator+=(Vector2);
    Vector2& operator-=(Vector2);
    Vector2& operator*=(float);
    Vector2& operator/=(float);
    Vector2 operator+(Vector2);
    Vector2 operator-(Vector2);
    Vector2 operator-();
    Vector2 operator*(float);
    Vector2 operator/(float);
  private:
    using Vector3::z;
};