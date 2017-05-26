#pragma once

class Vector2
{
  public:
    Vector2();
    Vector2(float, float);
    float x;
    float y;
    float GetMagnitude();
    float GetAngle();
    float DistanceFrom(Vector2);
    Vector2& operator+=(Vector2);
    Vector2& operator-=(Vector2);
    Vector2& operator*=(float);
    Vector2& operator/=(float);
    Vector2 operator+(Vector2);
    Vector2 operator-(Vector2);
    Vector2 operator*(float);
    Vector2 operator/(float);
};