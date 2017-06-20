#include <SDL2/SDL.h>
#include "input.hpp"
#include "vector2.hpp"

using namespace Prova;

void Input::Update()
{
  _oldkeystate = _keystate;
  _keystate = SDL_GetKeyboardState(NULL);

  if(_oldkeystate == nullptr)
    _oldkeystate = _keystate;

  int x, y;
  SDL_GetMouseState(&x, &y);

  mouse.x = x;
  mouse.y = y;
}

bool Input::IsKeyDown(int key)
{
  return _keystate[key];
}

bool Input::IsKeyUp(int key)
{
  return !_keystate[key];
}

bool Input::KeyJustPressed(int key)
{
  return !_oldkeystate[key] && _keystate[key];
}

Vector2 Input::SimulateAxis(int up, int left, int down, int right)
{
  Vector2 vector(
    IsKeyDown(right)-IsKeyDown(left),
    IsKeyDown(down)-IsKeyDown(up)
  );

  return vector.Normalize();
}

bool Input::IsMouseButtonDown(int button)
{
  return SDL_BUTTON(button);
}

bool Input::IsMouseButtonUp(int button)
{
  return !SDL_BUTTON(button);
}