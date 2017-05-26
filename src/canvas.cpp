#include <SDL2/SDL_image.h>
#include <math.h>
#include <unordered_map>
#include <string>
#include "canvas.hpp"
#include "sprite.hpp"

void Canvas::DrawSprite(Sprite* sprite, int x, int y)
{
  // load the texture for the first time
  if(sprite->_texture == NULL)
    sprite->_texture = LoadTexture(sprite->_path);
  
  sprite->Update();

  // get the source and destination rectangles
  SDL_Rect source = sprite->_clip;
  SDL_Rect destination = {
    x - sprite->originX * abs(sprite->scaleX),
    y - sprite->originY * abs(sprite->scaleY),
    source.w * abs(sprite->scaleX),
    source.h * abs(sprite->scaleY)
  };
  
  SDL_Point center;
  center.x = -source.w;
  center.y = -source.h;

  int flip = SDL_FLIP_NONE;

  if(sprite->scaleX < 0)
    flip |= SDL_FLIP_HORIZONTAL;
  
  if(sprite->scaleY < 0)
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