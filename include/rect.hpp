#pragma once

namespace Prova
{
  class Vector2;

  class Rect
  {
    public:
      Rect();
      Rect(float left, float top, float width, float height);
      float left;
      float top;
      float width;
      float height;
      Vector2 GetTopLeft();
      Vector2 GetTopRight();
      Vector2 GetBottomLeft();
      Vector2 GetBottomRight();
  };
}