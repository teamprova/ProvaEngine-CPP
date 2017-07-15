#pragma once
#include <map>
#include "controller.hpp"
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
      Controller& GetController(int index);
      bool IsKeyDown(Key::Key key);
      bool IsKeyUp(Key::Key key);
      bool KeyJustPressed(Key::Key key);
      Vector2 SimulateStick(Key::Key up, Key::Key left, Key::Key down, Key::Key right);
      bool IsMouseButtonDown(int mouseButton);
      bool IsMouseButtonUp(int mouseButton);
    private:
      std::map<int, Controller*> _controllers;
      const uint8_t* _keystate;
      const uint8_t* _oldKeystate;
  };
}