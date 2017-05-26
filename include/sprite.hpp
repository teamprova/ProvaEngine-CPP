#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include "vector2.hpp"

class Vector2;
class Canvas;
class Animation;

// animations use an id as an int
// but use enums
class Sprite
{
  friend class Canvas;

  public:
    Sprite(std::string, int, int);
    Vector2 origin;
    Vector2 scale;
    int angle = 0;
    bool looping = false;
    void CreateAnimation(int id, int row, int frameCount, float frameDuration);
    void PlayAnimation(int id, bool loop);
    bool IsAnimationFinished();
    float GetCurrentTime();
    float GetCurrentFrame();
    void Update();
  private:
    std::unordered_map<int, Animation*> _animations;
    Animation* _currentAnimation = NULL;
    SDL_Texture* _texture = NULL;
    SDL_Rect _clip;
    std::string _path;
    Uint32 _startTime;
    void SetTexture(SDL_Texture*);
    ~Sprite();
};