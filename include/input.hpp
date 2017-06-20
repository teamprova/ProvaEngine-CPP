#pragma once
#include "vector2.hpp"
#include <SDL2/SDL.h>

namespace Prova
{
  class Vector2;

  class Input
  {
    public:
      void Update();
      Vector2 mouse;
      bool IsKeyDown(int key);
      bool IsKeyUp(int key);
      bool KeyJustPressed(int key);
      Vector2 SimulateAxis(int up, int left, int down, int right);
      bool IsMouseButtonDown(int button);
      bool IsMouseButtonUp(int button);
    private:
      const Uint8* _keystate;
      const Uint8* _oldkeystate;
  };
}