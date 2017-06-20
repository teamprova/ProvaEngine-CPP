#include <SDL2/SDL.h>
#include <math.h>
#include "sprite.hpp"
#include "animation.hpp"
#include "texture.hpp"
#include "vector2.hpp"

using namespace Prova;

Sprite::Sprite(std::string sheetpath, int width, int height)
  : texture(sheetpath)
{
  this->width = width;
  this->height = height;
  _clip.left = 0;
  _clip.top = 0;
  _clip.width = width / (float) texture.width;
  _clip.height = height / (float) texture.height;
  origin.x = width / 2;
  origin.y = height / 2;
  scale.x = 1;
  scale.y = 1;

  float vertices[] = {
    0, 0, 0, 1,
    1, 0, 0, 1,
    1, 1, 0, 1,
    0, 1, 0, 1
  };

  unsigned int indexes[] = { 0, 1, 2, 3 };

  mesh.SetIBO(indexes, 4);
  mesh.SetVBO(vertices, 16, 4);
}

void Sprite::CreateAnimation(int id, int row, int frameCount, float frameDuration)
{
  Animation* animation = new Animation;
  animation->id = id;
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

int Sprite::GetCurrentFrame()
{
  if(_currentAnimation == NULL)
    return 0;
  
  int frame = GetCurrentTime() / _currentAnimation->frameDuration;

  if(IsAnimationFinished())
    frame = _currentAnimation->duration / _currentAnimation->frameDuration - 1;
  
  return frame;
}

int Sprite::GetCurrentAnimation()
{
  return _currentAnimation->id;
}

void Sprite::Update()
{
  if(_currentAnimation == NULL)
    return;
  
  _clip.left = _clip.width * GetCurrentFrame();
  _clip.top = _clip.height * _currentAnimation->row;
}

Sprite::~Sprite()
{
  for(auto it : _animations)
    delete it.second;
}