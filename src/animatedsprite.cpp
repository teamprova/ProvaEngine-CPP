#include <SDL.h>
#include <math.h>
#include "animatedsprite.hpp"
#include "sprite.hpp"
#include "animation.hpp"
#include "texture.hpp"
#include "vector2.hpp"

using namespace Prova;

AnimatedSprite::AnimatedSprite(std::string sheetpath, int width, int height)
  : Sprite(sheetpath, width, height) { }

void AnimatedSprite::CreateAnimation(int id, int row, int frameCount, float frameDuration)
{
  Animation* animation = new Animation;
  animation->id = id;
  animation->row = row;
  animation->frameCount = frameCount;
  animation->frameDuration = frameDuration;
  animation->duration = frameCount * frameDuration;

  _animations.emplace(id, animation);
}

void AnimatedSprite::PlayAnimation(int id, bool loop)
{
  _startTime = SDL_GetTicks();
  looping = loop;
  
  _currentAnimation = _animations[id];
}

bool AnimatedSprite::IsAnimationFinished()
{
  return GetCurrentTime() > _currentAnimation->duration;
}

float AnimatedSprite::GetCurrentTime()
{
  float currentTime = SDL_GetTicks() - _startTime;
  currentTime /= 1000.0f;

  if(looping)
    currentTime = fmod(currentTime, _currentAnimation->duration);

  return currentTime;
}

int AnimatedSprite::GetCurrentFrame()
{
  if(_currentAnimation == NULL)
    return 0;
  
  int frame = GetCurrentTime() / _currentAnimation->frameDuration;

  if(IsAnimationFinished())
    frame = _currentAnimation->duration / _currentAnimation->frameDuration - 1;
  
  return frame;
}

int AnimatedSprite::GetCurrentAnimation()
{
  return _currentAnimation->id;
}

void AnimatedSprite::Update()
{
  if(_currentAnimation == NULL)
    return;
  
  clip.left = clip.width * GetCurrentFrame();
  clip.top = 1 - clip.height * (_currentAnimation->row + 1);
}

AnimatedSprite::~AnimatedSprite()
{
  for(auto it : _animations)
    delete it.second;
}