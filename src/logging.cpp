#include <SDL.h>
#include <iostream>
#include <string>
#include "logging.hpp"
#include "vector4.hpp"
#include "vector3.hpp"
#include "vector2.hpp"
#include "rect.hpp"

using namespace Prova;

void Prova::Log(float number)
{
  Log(std::to_string(number));
}

void Prova::Log(Vector2 vector)
{
  std::string message = "Vector2(";
  message += std::to_string(vector.x);
  message += ",";
  message += std::to_string(vector.y);
  message +=  ")";
  
  Log(message);
}

void Prova::Log(Vector3 vector)
{
  std::string message = "Vector3(";
  message += std::to_string(vector.x);
  message += ",";
  message += std::to_string(vector.y);
  message += ",";
  message += std::to_string(vector.z);
  message +=  ")";
  
  Log(message);
}

void Prova::Log(Vector4 vector)
{
  std::string message = "Vector4(";
  message += std::to_string(vector.x);
  message += ",";
  message += std::to_string(vector.y);
  message += ",";
  message += std::to_string(vector.z);
  message += ",";
  message += std::to_string(vector.w);
  message +=  ")";

  Log(message);
}

void Prova::Log(Rect rect)
{
  std::string message = "Rect(";
  message += std::to_string(rect.left);
  message += ",";
  message += std::to_string(rect.top);
  message += ",";
  message += std::to_string(rect.width);
  message += ",";
  message += std::to_string(rect.height);
  message +=  ")";

  Log(message);
}

void Prova::Log(std::string message)
{
  SDL_Log(message.c_str());
}