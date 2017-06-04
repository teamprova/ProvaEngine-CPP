#pragma once
#include <unordered_map>

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
    bool operator==(const Vector4&) const;
};

namespace std {
  template <>
  struct hash<Vector4>
  {
    std::size_t operator()(const Vector4& vector) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      return ((((int)(vector.x) ^
               ((int)(vector.y) << 1)) >> 1) ^
               ((int)(vector.z) << 1) >> 1) ^
               ((int)(vector.w) << 1);
    }
  };
}