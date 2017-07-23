#pragma once
#include <map>
#include <vector>
#include "controller.hpp"
#include "keys.hpp"
#include "vector2.hpp"

namespace Prova
{
  class Vector2;

  class Input
  {
    public:
      Vector2 mouse;
      void Init();
      void Update();
      Controller& GetController(int index);
      bool IsKeyDown(Key key);
      bool IsKeyUp(Key key);
      bool KeyJustPressed(Key key);
      Vector2 SimulateStick(Key up, Key left, Key down, Key right);
      bool IsMouseButtonDown(int mouseButton);
      bool IsMouseButtonUp(int mouseButton);
    private:
      std::map<int, Controller*> _controllers;
      std::vector<bool> _keystate;
      std::vector<bool> _oldKeystate;
      void UpdateKeystate();
  };
}