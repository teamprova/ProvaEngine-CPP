#include <stdexcept>
#include <SDL.h>
#include "controller.hpp"
#include "vector2.hpp"

using namespace Prova;

Controller::Controller(int index)
  : id(index)
{
  _handle = SDL_GameControllerOpen(index);
  
  for(int i = 0; i < 17; ++i)
  {
    _oldButtonState[i] = false;
    _buttonState[i] = false;
  }
}

bool Controller::IsConnected()
{
  return SDL_GameControllerGetAttached((SDL_GameController*) _handle);
}

void Controller::Update()
{
  for(int i = 0; i < 17; ++i)
  {
    _oldButtonState[i] = _buttonState[i];
    _buttonState[i] = GetButtonState((Button) i);
  }
}

bool Controller::GetButtonState(Button button)
{
  if(button == TRIGGER_LEFT || button == TRIGGER_RIGHT)
    return GetTrigger(button) > .3;
  return SDL_GameControllerGetButton((SDL_GameController*) _handle, (SDL_GameControllerButton) button);
}

bool Controller::IsButtonDown(Button button)
{
  return _buttonState[button];
}

bool Controller::IsButtonUp(Button button)
{
  return !_buttonState[button];
}

bool Controller::ButtonJustPressed(Button button)
{
  return _buttonState[button] && !_oldButtonState[button];
}

Vector2 Controller::GetStick(ThumbStick stick)
{
  int xAxis = SDL_CONTROLLER_AXIS_LEFTX;

  if(stick == THUMBSTICK_RIGHT)
    xAxis = SDL_CONTROLLER_AXIS_RIGHTX;
  
  Vector2 displacement(GetAxis(xAxis), -GetAxis(xAxis + 1));

  if(displacement.GetMagnitude() == deadzone)
    return Vector2();
  else
    return displacement;
}

// throws an error for non trigger buttons
float Controller::GetTrigger(Button button)
{
  if(button == TRIGGER_LEFT)
    return GetAxis(SDL_CONTROLLER_AXIS_TRIGGERLEFT);
  if(button == TRIGGER_RIGHT)
    return GetAxis(SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
  
  throw std::runtime_error("Specified button is not a trigger.");
}

float Controller::GetAxis(int axis)
{
  return SDL_GameControllerGetAxis((SDL_GameController*) _handle, (SDL_GameControllerAxis) axis) / (float) 32767;
}

Controller::~Controller()
{
  SDL_GameControllerClose((SDL_GameController*) _handle);
}