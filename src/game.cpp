#include <SDL2/SDL.h>
#include <string>
#include "game.hpp"
#include "scene.hpp"
#include "canvas.hpp"

Game::Game(int width, int height, std::string title)
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::string error(SDL_GetError());
    throw "Initialization Error: " + error;
  }
  
  _window = SDL_CreateWindow(
    title.c_str(),
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    width, height,
    SDL_WINDOW_OPENGL
  );

  _canvas = new Canvas();
  _canvas->_renderer = SDL_CreateRenderer(_window, -1, 0);
}

void Game::SetTitle(std::string title)
{
  SDL_SetWindowTitle(_window, title.c_str());
}

void Game::Start(Scene* scene)
{
  if(_running)
    throw "Attempt to start game while it is already running";
  
  _running = true;
  _scene = scene;
  _scene->game = this;


  while(_running)
  {
    int frameDuration = 1000/FPS;
    int frameStart = SDL_GetTicks();

    Update();
    
    int usedTime = frameStart - SDL_GetTicks();

    if(usedTime < frameDuration)
      SDL_Delay(frameDuration - usedTime);
  }
}

void Game::SwapScene(Scene* scene)
{
  if(!_running)
    throw "Set initial scene through Game::Start(Scene*)";
  
  delete _scene;
  _scene = scene;
  _scene->game = this;
}

void Game::Update()
{
  SDL_Event e;

  while(SDL_PollEvent( &e ) != 0)
  {
    if(e.type == SDL_QUIT)
    {
      Close();
      return;
    }
  }

  _scene->Draw(_canvas);

  _scene->PreUpdate();
  _scene->Update();
}

void Game::Close()
{
  if(_running)
    delete _scene;
  
  SDL_DestroyRenderer(_canvas->_renderer);
  delete _canvas;
  
  SDL_DestroyWindow(_window);
  SDL_Quit();

  _running = false;
}