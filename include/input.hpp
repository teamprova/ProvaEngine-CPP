#pragma once
#include "keys.hpp"
#include "vector2.hpp"

namespace Prova
{
  class Vector2;

  class Input
  {
    public:
      void Update();
      Vector2 mouse;
      bool IsKeyDown(Keys::Keys key);
      bool IsKeyUp(Keys::Keys key);
      bool KeyJustPressed(Keys::Keys key);
      Vector2 SimulateAxis(Keys::Keys up, Keys::Keys left, Keys::Keys down, Keys::Keys right);
      bool IsMouseButtonDown(int mouseButton);
      bool IsMouseButtonUp(int mouseButton);
    private:
      const uint8_t* _keystate;
      const uint8_t* _oldkeystate;
  };
}