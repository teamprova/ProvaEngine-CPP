#include <SDL2/SDL_image.h>
#include <math.h>
#include "canvas.hpp"
#include "vector2.hpp"
#include "sprite.hpp"

void Canvas::DrawSprite(Sprite* sprite, Vector2 vector)
{
  Canvas::DrawSprite(sprite, vector.x, vector.y);
}

void Canvas::DrawSprite(Sprite* sprite, float x, float y)
{
  // load the texture for the first time
  if(sprite->_texture == NULL)
    sprite->_texture = LoadTexture(sprite->_path);
  
  sprite->Update();

  // get the source and destination rectangles
  SDL_Rect source = sprite->_clip;
  SDL_Rect destination = {
    (int)(x - sprite->origin.x * abs(sprite->scale.x)),
    (int)(y - sprite->origin.y * abs(sprite->scale.y)),
    (int)(source.w * abs(sprite->scale.x)),
    (int)(source.h * abs(sprite->scale.y))
  };
  
  SDL_Point center;
  center.x = sprite->origin.x;
  center.y = sprite->origin.y;

  int flip = SDL_FLIP_NONE;

  if(sprite->scale.x < 0)
    flip |= SDL_FLIP_HORIZONTAL;
  
  if(sprite->scale.y < 0)
    flip |= SDL_FLIP_VERTICAL;
    
  // copy the texture onto the canvas
  SDL_RenderCopyEx(
    _renderer,
    sprite->_texture,
    &source, &destination,
    sprite->angle, 
    &center,
    (SDL_RendererFlip) flip
  );
}

void Canvas::Clear(int r, int g, int b)
{
  SDL_SetRenderDrawColor(_renderer, r, g, b, 255);
  SDL_RenderClear(_renderer);
}

void Canvas::SwapBuffer()
{
  SDL_RenderPresent(_renderer);
}

SDL_Texture* Canvas::LoadTexture(std::string path)
{
  SDL_Texture* texture;

  // checking texture cache for existence
  if(_textureCache.count(path) == 0)
  {
    // texture was not cached
    texture = IMG_LoadTexture(_renderer, path.c_str());
    _textureCache.emplace(path, texture);
  }
  else
  {
    // get the cached texture
    texture = _textureCache[path];
  }


  return texture;
}