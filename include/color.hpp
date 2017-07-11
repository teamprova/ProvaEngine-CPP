#pragma once

namespace Prova
{
  class Color
  {
    public:
      Color();
      Color(float, float, float, float);
      Color(float, float, float);
      float r = 0;
      float g = 0;
      float b = 0;
      float a = 1;
  };
}
