#include <math.h>
#include "vector2.hpp"

Vector2::Vector2()
{
  this->x = 0;
  this->y = 0;
}

Vector2::Vector2(float x, float y)
{
  this->x = x;
  this->y = y;
}

float Vector2::GetMagnitude()
{
  return sqrt(x * x + y * y);
}

float Vector2::GetAngle()
{
  return atan2(y, x);
}

float Vector2::DistanceFrom(Vector2 vector)
{
  float a = vector.x - x;
  float b = vector.y - y;

  return sqrt(a * a + b * b);
}


// assignment overloading
Vector2& Vector2::operator+=(Vector2 vector)
{
  x += vector.x;
  y += vector.y;

  return *this;
}

Vector2& Vector2::operator-=(Vector2 vector)
{
  x -= vector.x;
  y -= vector.y;

  return *this;
}

Vector2& Vector2::operator*=(float a)
{
  x *= a;
  y *= a;

  return *this;
}

Vector2& Vector2::operator/=(float a)
{
  x /= a;
  y /= a;

  return *this;
}


// arithmetic overloading
Vector2 Vector2::operator+(Vector2 vector)
{
  vector.x += x;
  vector.y += y;

  return vector;
}

Vector2 Vector2::operator-(Vector2 vector)
{
  vector.x = x - vector.x ;
  vector.y = y - vector.y;

  return vector; 
}

Vector2 Vector2::operator*(float a)
{
  Vector2 vector;
  vector.x = x / a;
  vector.y = y / a;

  return vector; 
}

Vector2 Vector2::operator/(float a)
{
  Vector2 vector;
  vector.x = x / a;
  vector.y = y / a;

  return vector; 
}