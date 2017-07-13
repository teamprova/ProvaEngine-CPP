#include <SDL.h>
#include <stdexcept>
#include "watch.hpp"

using namespace Prova;

// Acts as a start/resume function
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

void Watch::Pause()
{
  isRunning = false;
  lastStopTime = SDL_GetTicks();
}

// Stops timing and resets
void Watch::Reset()
{
  isRunning = false;
  startTime = 0;
  lastStopTime = 0;
}

// Resets and starts again
void Watch::Restart()
{
  startTime = 0;
  
  Start();
}

// we currently only track using milliseconds so,
// maybe this should be renamed?
int Watch::GetElapsedMilliseconds()
{
  if(startTime == 0)
    throw std::runtime_error("Watch never started");
  
  return SDL_GetTicks() - startTime - breakLength;
}