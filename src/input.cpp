#include <SDL2/SDL.h>
#include "input.hpp"
#include "keys.hpp"
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

bool Input::IsKeyDown(Keys::Keys key)
{
  return _keystate[key];
}

bool Input::IsKeyUp(Keys::Keys key)
{
  return !_keystate[key];
}

bool Input::KeyJustPressed(Keys::Keys key)
{
  return !_oldkeystate[key] && _keystate[key];
}

Vector2 Input::SimulateAxis(Keys::Keys up, Keys::Keys left, Keys::Keys down, Keys::Keys right)
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