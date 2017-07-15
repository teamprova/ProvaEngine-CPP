#include <SDL.h>
#include "input.hpp"
#include "controller.hpp"
#include "keys.hpp"
#include "vector2.hpp"

using namespace Prova;

void Input::Update()
{
  // update controller state
  for(auto controllerIt : _controllers)
    controllerIt.second->Update();

  // update keystate
  _oldKeystate = _keystate;
  _keystate = SDL_GetKeyboardState(NULL);

  if(_oldKeystate == nullptr)
    _oldKeystate = _keystate;

  // update mouse state
  int x, y;
  SDL_GetMouseState(&x, &y);

  mouse.x = x;
  mouse.y = y;
}

Controller& Input::GetController(int index)
{
  // controller not found then add it to our list
  // of updated controllers
  if(_controllers.find(index) == _controllers.end())
    _controllers.emplace(index, new Controller(index));
  
  return *_controllers[index];
}

bool Input::IsKeyDown(Key::Key key)
{
  return _keystate[key];
}

bool Input::IsKeyUp(Key::Key key)
{
  return !_keystate[key];
}

bool Input::KeyJustPressed(Key::Key key)
{
  return !_oldKeystate[key] && _keystate[key];
}

Vector2 Input::SimulateStick(Key::Key up, Key::Key left, Key::Key down, Key::Key right)
{
  Vector2 vector(
    IsKeyDown(right)-IsKeyDown(left),
    IsKeyDown(down)-IsKeyDown(up)
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