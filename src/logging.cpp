#include <SDL.h>
#include <iostream>
#include <string>
#include "logging.hpp"

using namespace Prova;

void Prova::Log(float number)
{
  Log(std::to_string(number));
}

void Prova::Log(std::string message)
{
  SDL_Log(message.c_str());
}