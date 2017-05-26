#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>

class Sprite;

class Canvas
{
  friend class Game;

  public:
    void DrawSprite(Sprite*, int, int);
    void Clear(int, int, int);
    void SwapBuffer();
  private:
    SDL_Texture* LoadTexture(std::string);
    std::unordered_map<std::string, SDL_Texture*> _textureCache;
    SDL_Renderer* _renderer;
};