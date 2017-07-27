#pragma once
#include <string>
#include "vector4.hpp"
#include "vector3.hpp"
#include "vector2.hpp"
#include "rect.hpp"

namespace Prova
{
  void Log(float number);
  void Log(Vector2 vector);
  void Log(Vector3 vector);
  void Log(Vector4 vector);
  void Log(Rect rect);
  void Log(std::string message);
}