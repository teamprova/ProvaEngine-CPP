#pragma once

class Rect;

class Vector4
{
  public:
    Vector4();
    Vector4(Rect rect);
    Vector4(float, float, float, float);
    float x;
    float y;
    float z;
    float w;
    Vector4 Normalize();
    float GetMagnitude();
    float DistanceFrom(Vector4);
    Vector4& operator+=(Vector4);
    Vector4& operator-=(Vector4);
    Vector4& operator*=(float);
    Vector4& operator/=(float);
    Vector4 operator+(Vector4);
    Vector4 operator-(Vector4);
    Vector4 operator-();
    Vector4 operator*(float);
    Vector4 operator/(float);
};