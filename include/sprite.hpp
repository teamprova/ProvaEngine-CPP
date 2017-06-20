#pragma once
#include <string>
#include <unordered_map>
#include "mesh.hpp"
#include "rect.hpp"
#include "texture.hpp"
#include "vector2.hpp"

namespace Prova
{
  class Animation;
  class Model;
  class Rect;
  class Screen;
  class Texture;
  class Vector2;

  // animations use an id as an int
  // but use enums
  class Sprite
  {
    friend class Screen;

    public:
      Sprite(std::string sheetpath, int width, int height);
      Texture texture;
      Mesh mesh;
      Vector2 origin;
      Vector2 scale;
      int width;
      int height;
      int angle = 0;
      bool looping = false;
      void CreateAnimation(int id, int row, int frameCount, float frameDuration);
      void PlayAnimation(int id, bool loop);
      bool IsAnimationFinished();
      float GetCurrentTime();
      int GetCurrentFrame();
      int GetCurrentAnimation();
      void Update();
      ~Sprite();
    private:
      std::unordered_map<int, Animation*> _animations;
      Animation* _currentAnimation = NULL;
      Rect _clip;
      unsigned int _startTime;
  };
}