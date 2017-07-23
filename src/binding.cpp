#include <stdexcept>
#include <utility>
#include <map>
#include "binding.hpp"
#include "controller.hpp"
#include "input.hpp"
#include "vector2.hpp"

using namespace Prova;

void Binding::BindInput(Input* input)
{
  _input = input;
}

void Binding::BindController(int index)
{
  if(_input == nullptr)
    throw std::runtime_error("Input has not been binded yet");
  
  _controller = &_input->GetController(index);
}

void Binding::BindButton(int button, Keys::Key key)
{
  _boundKeyButtons.emplace(button, key);
}

void Binding::BindButton(int button, Controller::Button controllerButton)
{
  _boundControllerButtons.emplace(button, controllerButton);
}

void Binding::BindStick(int stick, Keys::Key up, Keys::Key left, Keys::Key down, Keys::Key right)
{
  std::array<Keys::Key, 4> simulatedStick = {up, left, down, right};
  _boundKeySticks.emplace(stick, simulatedStick);
}

void Binding::BindStick(int stick, Controller::ThumbStick joystick)
{
  _boundControllerSticks.emplace(stick, joystick);
}

bool Binding::IsButtonDown(int button)
{
  if(_input == nullptr)
    throw std::runtime_error("Input has not been binded yet");
  
  // loop through bound keys and return true if pressed
  auto keyRange = _boundKeyButtons.equal_range(button);

  for(auto it = keyRange.first; it != keyRange.second; ++it)
    if(_input->IsKeyDown(it->second))
      return true;

  // do not test controller bindings if the controller isn't set
  if(_controller == nullptr)
    return false;

  // loop through bound buttons and return true if pressed
  auto controllerRange = _boundControllerButtons.equal_range(button);

  for(auto it = controllerRange.first; it != controllerRange.second; ++it)
    if(_controller->IsButtonDown(it->second))
      return true;

  return false;
}

bool Binding::IsButtonUp(int button)
{
  return !IsButtonDown(button);
}

bool Binding::ButtonJustPressed(int button)
{
  if(_input == nullptr)
    throw std::runtime_error("Input has not been binded yet");
  
  // loop through bound keys and return true if just pressed
  auto keyRange = _boundKeyButtons.equal_range(button);
  
  for(auto it = keyRange.first; it != keyRange.second; ++it)
    if(_input->KeyJustPressed(it->second))
      return true;

  // do not test controller bindings if the controller isn't set
  if(_controller == nullptr)
    return false;

  // loop through bound buttons and return true if just pressed
  auto controllerRange = _boundControllerButtons.equal_range(button);

  for(auto it = controllerRange.first; it != controllerRange.second; ++it)
    if(_controller->ButtonJustPressed(it->second))
      return true;

  return false;
}

Vector2 Binding::GetStick(int stick)
{
  if(_input == nullptr)
    throw std::runtime_error("Input has not been binded yet");
  
  Vector2 zero;

  // loop through bound sticks and return only if it does not equal zero
  auto keyRange = _boundKeySticks.equal_range(stick);

  for(auto it = keyRange.first; it != keyRange.second; ++it)
  {
    std::array<Keys::Key, 4> simulatedStick = it->second;
    Vector2 vector = _input->SimulateStick(
      simulatedStick[0], simulatedStick[1], simulatedStick[2], simulatedStick[3]
    );
    
    if(vector != zero)
      return vector;
  }

  // do not test controller bindings if the controller isn't set
  if(_controller == nullptr)
    return zero;

  // loop through bound sticks and return only if it does not equal zero
  auto controllerRange = _boundControllerSticks.equal_range(stick);

  for(auto it = controllerRange.first; it != controllerRange.second; ++it)
  {
    Vector2 vector = _controller->GetStick(it->second);

    if(vector.GetMagnitude() > deadzone)
      return vector;
  }

  return zero;
}