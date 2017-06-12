#include "rect.hpp"
#include "vector2.hpp"

using namespace Prova;

Rect::Rect()
  : Rect(0, 0, 0, 0) {}

Rect::Rect(float left, float top, float width, float height)
{
  this->left = left;
  this->top = top;
  this->width = width;
  this->height = height;
}

Vector2 Rect::GetTopLeft()
{
  return Vector2(left, top);
}

Vector2 Rect::GetTopRight()
{
  return Vector2(left + width, top);
}

Vector2 Rect::GetBottomLeft()
{
  return Vector2(left, top + height);
}

Vector2 Rect::GetBottomRight()
{
  return Vector2(left + width, top + height);
}