#pragma once

struct Rect
{
  public:
    Rect();
    Rect(float, float, float, float);
    float left;
    float top;
    float width;
    float height;
};