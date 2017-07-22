#pragma once

namespace Prova
{
  class Color
  {
    public:
      Color();
      Color(float r, float g, float b, float a);
      Color(float r, float g, float b);
      float r = 0;
      float g = 0;
      float b = 0;
      float a = 1;
      bool operator==(Color& color) const;
      bool operator!=(Color& color) const;
  };
}
