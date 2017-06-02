#include "rect.hpp"

Rect::Rect()
  : Rect(0, 0, 0, 0) {}

Rect::Rect(float left, float top, float width, float height)
{
  this->left = left;
  this->top = top;
  this->width = width;
  this->height = height;
}