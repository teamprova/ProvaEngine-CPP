#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

class Canvas;
class Animation;

// animations use an id as an int
// but use enums
class Sprite
{
  friend class Canvas;

  public:
    Sprite(std::string, int, int);
    int angle = 0;
    int scaleX = 1;
    int scaleY = 1;
    int originX;
    int originY;
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