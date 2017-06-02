#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include <math.h>
#include "sprite.hpp"
#include "animation.hpp"
#include "vector2.hpp"

Sprite::Sprite(std::string sheetpath, int width, int height)
{
  texture = SOIL_load_OGL_texture
	(
		sheetpath.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		0
	);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
  int sheetWidth, sheetHeight;
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &sheetWidth);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &sheetHeight);
  _sheetSize.x = sheetWidth;
  _sheetSize.y = sheetHeight;

  this->width = width;
  this->height = height;
  _clip.left = 0;
  _clip.top = 0;
  _clip.width = width / _sheetSize.x;
  _clip.height = height / _sheetSize.y;
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
  glDeleteTextures(1, &texture);

  for(auto it : _animations)
    delete it.second;
}