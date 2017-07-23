#pragma once
#include <map>
#include "vector2.hpp"

namespace Prova
{
  class Vector2;

  enum class ThumbStick { LEFT, RIGHT };
  enum class ControllerButton {
    A, B, X, Y, BACK, GUIDE, START,
    LEFT_STICK, RIGHT_STICK, BUMPER_LEFT, BUMPER_RIGHT,
    DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT,
    // simulated buttons
    TRIGGER_LEFT, TRIGGER_RIGHT
  };

  class Controller
  {
    friend class Input;

    public:

      const int id;
      float deadzone = .15;
      bool IsConnected();
      bool IsButtonDown(ControllerButton button);
      bool IsButtonUp(ControllerButton button);
      bool ButtonJustPressed(ControllerButton button);
      Vector2 GetStick(ThumbStick joystick);
      // throws an error for non trigger buttons
      float GetTrigger(ControllerButton button);
      ~Controller();
    private:
      void* _handle;
      bool _buttonState[17];
      bool _oldButtonState[17];
      Controller(int index);
      void Update();
      bool GetButtonState(ControllerButton button);
      float GetAxis(int axis);
  };
}