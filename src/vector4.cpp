#include <math.h>
#include "vector4.hpp"
#include "rect.hpp"

using namespace Prova;

Vector4::Vector4()
  :Vector4(0, 0, 0, 0) {}

Vector4::Vector4(Rect rect)
  :Vector4(rect.left, rect.top, rect.width, rect.height) {}

Vector4::Vector4(float x, float y, float z, float w)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

Vector4 Vector4::Normalize()
{
  float magnitude = GetMagnitude();

  Vector4 result;
  
  if(magnitude != 0)
  {
    result.x = x / magnitude;
    result.y = y / magnitude;
    result.z = z / magnitude;
    result.w = w / magnitude;
  }
  
  return result;
}

float Vector4::GetMagnitude()
{
  return sqrt(x * x + y * y + z * z + w * w);
}

float Vector4::DistanceFrom(Vector4 vector)
{
  float a = vector.x - x;
  float b = vector.y - y;
  float c = vector.z - z;
  float d = vector.w - w;

  return sqrt(a * a + b * b + c * c + d * d);
}


// assignment overloading
Vector4& Vector4::operator+=(Vector4 vector)
{
  x += vector.x;
  y += vector.y;
  z += vector.z;
  w += vector.w;

  return *this;
}

Vector4& Vector4::operator-=(Vector4 vector)
{
  x -= vector.x;
  y -= vector.y;
  z -= vector.z;
  w -= vector.w;

  return *this;
}

Vector4& Vector4::operator*=(float a)
{
  x *= a;
  y *= a;
  z *= a;
  w *= a;

  return *this;
}

Vector4& Vector4::operator/=(float a)
{
  x /= a;
  y /= a;
  z /= a;
  w /= a;

  return *this;
}


// arithmetic overloading
Vector4 Vector4::operator+(Vector4 vector)
{
  vector.x += x;
  vector.y += y;
  vector.z += z;
  vector.w += w;

  return vector;
}

Vector4 Vector4::operator-(Vector4 vector)
{
  vector.x = x - vector.x;
  vector.y = y - vector.y;
  vector.z = z - vector.z;
  vector.w = w - vector.w;

  return vector; 
}

Vector4 Vector4::operator-()
{
  Vector4 vector;
  vector.x = -x;
  vector.y = -y;
  vector.z = -z;
  vector.w = -w;

  return vector;
}

Vector4 Vector4::operator*(float a)
{
  Vector4 vector;
  vector.x = x * a;
  vector.y = y * a;
  vector.z = z * a;
  vector.w = w * a;

  return vector; 
}

Vector4 Vector4::operator/(float a)
{
  Vector4 vector;
  vector.x = x / a;
  vector.y = y / a;
  vector.z = z / a;
  vector.w = w / a;

  return vector; 
}

bool Vector4::operator==(const Vector4& vector) const
{
  return vector.x == x &&
        vector.y == y &&
        vector.z == z &&
        vector.w == w;
}

bool Vector4::operator!=(const Vector4& vector) const
{
  return vector.x != x &&
        vector.y != y &&
        vector.z != z &&
        vector.w != w;
}