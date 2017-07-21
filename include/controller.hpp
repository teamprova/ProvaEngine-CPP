#pragma once
#include <map>
#include "vector2.hpp"

namespace Prova
{
  class Vector2;

  class Controller
  {
    friend class Input;

    public:
      enum ThumbStick { THUMBSTICK_LEFT, THUMBSTICK_RIGHT };
      enum Button {
        A, B, X, Y, BACK, GUIDE, START,
        LEFT_STICK, RIGHT_STICK, BUMPER_LEFT, BUMPER_RIGHT,
        DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT,
        // simulated buttons
        TRIGGER_LEFT, TRIGGER_RIGHT
      };

      const int id;
      bool IsConnected();
      bool IsButtonDown(Button button);
      bool IsButtonUp(Button button);
      bool ButtonJustPressed(Button button);
      Vector2 GetStick(ThumbStick joystick);
      // throws an error for non trigger buttons
      float GetTrigger(Button button);
      ~Controller();
    private:
      void* _handle;
      bool _buttonState[17];
      bool _oldButtonState[17];
      Controller(int index);
      void Update();
      bool GetButtonState(Button button);
      float GetAxis(int axis);
  };
}