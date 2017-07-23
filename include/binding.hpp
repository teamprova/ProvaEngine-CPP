#pragma once
#include <utility>
#include <map>
#include "controller.hpp"
#include "keys.hpp"

namespace Prova
{
  class Input;
  class Vector2;

  class Binding
  {
    friend class Input;

    public:
      float deadzone = .15;

      void BindInput(Input* input);
      void BindController(int index);
      void BindButton(int button, Key key);
      void BindButton(int button, ControllerButton controllerButton);
      void BindStick(int stick, Key up, Key left, Key down, Key right);
      void BindStick(int stick, ThumbStick joystick);
      bool IsButtonDown(int button);
      bool IsButtonUp(int button);
      bool ButtonJustPressed(int button);
      Vector2 GetStick(int stick);
    private:
      Controller* _controller = nullptr;
      Input* _input = nullptr;
      std::multimap<int, Key> _boundKeyButtons;
      std::multimap<int, ControllerButton> _boundControllerButtons;
      std::multimap<int, std::array<Key, 4>> _boundKeySticks;
      std::multimap<int, ThumbStick> _boundControllerSticks;
  };
}