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
    _buttonState[i] = GetButtonState((ControllerButton) i);
  }
}

bool Controller::GetButtonState(ControllerButton button)
{
  if(button == ControllerButton::TRIGGER_LEFT || button == ControllerButton::TRIGGER_RIGHT)
    return GetTrigger(button) > .3;
  return SDL_GameControllerGetButton((SDL_GameController*) _handle, (SDL_GameControllerButton) button);
}

bool Controller::IsButtonDown(ControllerButton button)
{
  return _buttonState[(int) button];
}

bool Controller::IsButtonUp(ControllerButton button)
{
  return !_buttonState[(int) button];
}

bool Controller::ButtonJustPressed(ControllerButton button)
{
  return _buttonState[(int) button] && !_oldButtonState[(int) button];
}

Vector2 Controller::GetStick(ThumbStick stick)
{
  int xAxis = SDL_CONTROLLER_AXIS_LEFTX;

  if(stick == ThumbStick::RIGHT)
    xAxis = SDL_CONTROLLER_AXIS_RIGHTX;
  
  Vector2 displacement(GetAxis(xAxis), -GetAxis(xAxis + 1));

  if(displacement.GetMagnitude() <= deadzone)
    return Vector2();
  else
    return displacement;
}

// throws an error for non trigger buttons
float Controller::GetTrigger(ControllerButton button)
{
  if(button == ControllerButton::TRIGGER_LEFT)
    return GetAxis(SDL_CONTROLLER_AXIS_TRIGGERLEFT);
  if(button == ControllerButton::TRIGGER_RIGHT)
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