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
      bool IsKeyDown(Keys::Key key);
      bool IsKeyUp(Keys::Key key);
      bool KeyJustPressed(Keys::Key key);
      Vector2 SimulateStick(Keys::Key up, Keys::Key left, Keys::Key down, Keys::Key right);
      bool IsMouseButtonDown(int mouseButton);
      bool IsMouseButtonUp(int mouseButton);
    private:
      std::map<int, Controller*> _controllers;
      std::vector<bool> _keystate;
      std::vector<bool> _oldKeystate;
      void UpdateKeystate();
  };
}