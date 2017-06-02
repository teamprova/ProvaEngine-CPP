#include <math.h>
#include "vector3.hpp"
#include "vector4.hpp"

Vector3::Vector3() {}

Vector3::Vector3(float x, float y, float z)
  : Vector4(x, y, z, 0) {}


Vector3 Vector3::Normalize()
{
  float magnitude = GetMagnitude();

  Vector3 result;

  if(magnitude != 0)
  {
    result.x = x / magnitude;
    result.y = y / magnitude;
    result.z = z / magnitude;
  }
  
  return result;
}

float Vector3::DistanceFrom(Vector3 vector)
{
  float a = vector.x - x;
  float b = vector.y - y;
  float c = vector.z - z;

  return sqrt(a * a + b * b + c * c);
}


// assignment overloading
Vector3& Vector3::operator+=(Vector3 vector)
{
  x += vector.x;
  y += vector.y;
  z += vector.z;

  return *this;
}

Vector3& Vector3::operator-=(Vector3 vector)
{
  x -= vector.x;
  y -= vector.y;
  z -= vector.z;

  return *this;
}

Vector3& Vector3::operator*=(float a)
{
  x *= a;
  y *= a;
  z *= a;

  return *this;
}

Vector3& Vector3::operator/=(float a)
{
  x /= a;
  y /= a;
  z /= a;

  return *this;
}


// arithmetic overloading
Vector3 Vector3::operator+(Vector3 vector)
{
  vector.x += x;
  vector.y += y;
  vector.z += z;

  return vector;
}

Vector3 Vector3::operator-(Vector3 vector)
{
  vector.x = x - vector.x;
  vector.y = y - vector.y;
  vector.z = z - vector.z;

  return vector; 
}

Vector3 Vector3::operator-()
{
  Vector3 vector;
  vector.x = -x;
  vector.y = -y;
  vector.z = -z;

  return vector;
}

Vector3 Vector3::operator*(float a)
{
  Vector3 vector;
  vector.x = x * a;
  vector.y = y * a;
  vector.z = z * a;

  return vector; 
}

Vector3 Vector3::operator/(float a)
{
  Vector3 vector;
  vector.x = x / a;
  vector.y = y / a;
  vector.z = z / a;

  return vector; 
}