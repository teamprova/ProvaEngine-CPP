#include <SDL2/SDL.h>
#include <math.h>
#include "sprite.hpp"
#include "animation.hpp"

Sprite::Sprite(std::string sheetpath, int width, int height)
{
  _path = sheetpath;
  _clip.x = 0;
  _clip.y = 0;
  _clip.w = width;
  _clip.h = height;
  origin.x = width / 2;
  origin.y = height / 2;
  scale.x = 1;
  scale.y = 1;
}

void Sprite::CreateAnimation(int id, int row, int frameCount, float frameDuration)
{
  Animation* animation = new Animation;
  animation->row = row;
  animation->frameCount = frameCount;
  animation->frameDuration = frameDuration;
  animation->duration = frameCount * frameDuration;

  _animations.emplace(id, animation);
}

void Sprite::PlayAnimation(int id, bool loop)
{
  _startTime = SDL_GetTicks();
  looping = loop;
  
  _currentAnimation = _animations[id];
}

bool Sprite::IsAnimationFinished()
{
  return GetCurrentTime() > _currentAnimation->duration;
}

float Sprite::GetCurrentTime()
{
  float currentTime = SDL_GetTicks() - _startTime;
  currentTime /= 1000.0f;

  if(looping)
    currentTime = fmod(currentTime, _currentAnimation->duration);

  return currentTime;
}

void Sprite::Update()
{
  if(_currentAnimation == NULL)
    return;
  
  int frame = GetCurrentTime() / _currentAnimation->frameDuration;

  if(IsAnimationFinished())
    frame = _currentAnimation->duration / _currentAnimation->frameDuration - 1;
  
  _clip.x = _clip.w * frame;
  _clip.y = _clip.h * _currentAnimation->row;
}

void Sprite::SetTexture(SDL_Texture* texture)
{
  _texture = texture;
}

Sprite::~Sprite()
{
  SDL_DestroyTexture(_texture);

  for(auto it : _animations)
    delete it.second;
}