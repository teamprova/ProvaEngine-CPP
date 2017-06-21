#include <SDL2/SDL.h>
#include <stdexcept>
#include "watch.hpp"

using namespace Prova;

void Watch::Start()
{
  isRunning = true;
  
  // reset
  if(startTime == 0)
  {
    breakLength = 0;
    lastStopTime = 0;
    startTime = SDL_GetTicks();
  }
  
  if(lastStopTime != 0)
  {
    breakLength += startTime - lastStopTime;
    lastStopTime = 0;
  }
}

void Watch::Stop()
{
  isRunning = false;
  lastStopTime = SDL_GetTicks();
}

void Watch::Reset()
{
  isRunning = false;
  startTime = 0;
  lastStopTime = 0;
}

void Watch::Restart()
{
  startTime = SDL_GetTicks();
  
  Start();
}

int Watch::GetElapsedMilliseconds()
{
  if(!isRunning)
    throw std::runtime_error("StopWatch not running");
  
  return SDL_GetTicks() - startTime - breakLength;
}