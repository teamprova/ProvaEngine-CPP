#include "color.hpp"

using namespace Prova;

Color::Color() { }

Color::Color(float r, float g, float b)
  : Color(r, g, b, 1) { }

Color::Color(float r, float g, float b, float a)
{
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}

bool Color::operator==(Color& color) const
{
  return color.r == r &&
         color.g == g &&
         color.b == b &&
         color.a == a;
}

bool Color::operator!=(Color& color) const
{
  return color.r != r ||
         color.g != g ||
         color.b != b ||
         color.a != a;
}