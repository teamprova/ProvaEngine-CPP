#pragma once
#include <string>
#include <unordered_map>
#include "animation.hpp"
#include "mesh.hpp"
#include "rect.hpp"
#include "spriteprimitive.hpp"
#include "spritebatch.hpp"
#include "texture.hpp"
#include "vector2.hpp"

namespace Prova
{
  class SpriteBatch;
  
  // animations use an id as an int
  // but use enums
  class Sprite : public SpritePrimitive
  {
    friend class SpriteBatch;

    public:
      Sprite(std::string sheetpath, int width, int height);
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
      unsigned int _startTime;
  };
}