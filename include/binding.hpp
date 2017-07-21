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
      void BindInput(Input* input);
      void BindController(int index);
      void BindButton(int button, Key::Key key);
      void BindButton(int button, Controller::Button controllerButton);
      void BindStick(int stick, Key::Key up, Key::Key left, Key::Key down, Key::Key right);
      void BindStick(int stick, Controller::ThumbStick joystick);
      bool IsButtonDown(int button);
      bool IsButtonUp(int button);
      bool ButtonJustPressed(int button);
      Vector2 GetStick(int stick);
    private:
      Controller* _controller = nullptr;
      Input* _input = nullptr;
      std::multimap<int, Key::Key> _boundKeyButtons;
      std::multimap<int, Controller::Button> _boundControllerButtons;
      std::multimap<int, std::array<Key::Key, 4>> _boundKeySticks;
      std::multimap<int, Controller::ThumbStick> _boundControllerSticks;
  };
}