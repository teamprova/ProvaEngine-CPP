#pragma once
#include "vector2.hpp"

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
      const uint8_t* _keystate;
      const uint8_t* _oldkeystate;
  };
}