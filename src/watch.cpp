#include <SDL.h>
#include <stdexcept>
#include "watch.hpp"

using namespace Prova;

// Acts as a start/resume function
void Watch::Start()
{
  _isRunning = true;
  
  // reset
  if(_startTime == 0)
  {
    _breakLength = 0;
    _lastStopTime = 0;
    _startTime = SDL_GetTicks();
  }
  
  if(_lastStopTime != 0)
  {
    _breakLength += _startTime - _lastStopTime;
    _lastStopTime = 0;
  }
}

void Watch::Pause()
{
  _isRunning = false;
  _lastStopTime = SDL_GetTicks();
}

// Stops timing and resets
void Watch::Reset()
{
  _isRunning = false;
  _startTime = 0;
  _lastStopTime = 0;
}

// Resets and starts again
void Watch::Restart()
{
  _startTime = 0;
  
  Start();
}

// we currently only track using milliseconds so,
// maybe this should be renamed?
int Watch::GetElapsedMilliseconds()
{
  if(_startTime == 0)
    throw std::runtime_error("Watch never started");
  
  return SDL_GetTicks() - _startTime - _breakLength;
}

bool Watch::IsRunning()
{
  return _isRunning;
}