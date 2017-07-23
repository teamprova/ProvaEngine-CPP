#include <SDL.h>
#include "input.hpp"
#include "controller.hpp"
#include "keys.hpp"
#include "vector2.hpp"

using namespace Prova;

void Input::Init()
{
  UpdateKeystate();
  _oldKeystate = _keystate;
}

void Input::Update()
{
  // update controller state
  for(auto controllerIt : _controllers)
    controllerIt.second->Update();

  // update keystate
  _oldKeystate = _keystate;
  UpdateKeystate();

  // update mouse state
  int x, y;
  SDL_GetMouseState(&x, &y);

  mouse.x = x;
  mouse.y = y;
}

void Input::UpdateKeystate()
{
  int keystateLength;
  const Uint8* SDLKeystate = SDL_GetKeyboardState(&keystateLength);

  _keystate.resize(keystateLength);
  std::copy(SDLKeystate, SDLKeystate + keystateLength, _keystate.begin());
}

Controller& Input::GetController(int index)
{
  // controller not found then add it to our list
  // of updated controllers
  if(_controllers.find(index) == _controllers.end())
    _controllers.emplace(index, new Controller(index));
  
  return *_controllers[index];
}

bool Input::IsKeyDown(Key key)
{
  return _keystate[(int) key];
}

bool Input::IsKeyUp(Key key)
{
  return !_keystate[(int) key];
}

bool Input::KeyJustPressed(Key key)
{
  return !_oldKeystate[(int) key] && _keystate[(int) key];
}

Vector2 Input::SimulateStick(Key up, Key left, Key down, Key right)
{
  Vector2 vector(
    IsKeyDown(right)-IsKeyDown(left),
    IsKeyDown(up)-IsKeyDown(down)
  );

  return vector.Normalize();
}

bool Input::IsMouseButtonDown(int mouseButton)
{
  return SDL_BUTTON(mouseButton);
}

bool Input::IsMouseButtonUp(int mouseButton)
{
  return !SDL_BUTTON(mouseButton);
}