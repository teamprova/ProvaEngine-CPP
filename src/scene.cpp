#include <SDL2/SDL.h>
#include "scene.hpp"

void Scene::PreUpdate()
{
  _keystate = SDL_GetKeyboardState(NULL);
}

bool Scene::IsKeyDown(int keycode)
{
  return _keystate[keycode];
}

bool Scene::IsKeyUp(int keycode)
{
  return !IsKeyDown(keycode);
}