#include <SDL2/SDL.h>
#include <string>
#include <stdexcept>
#include "game.hpp"
#include "scene.hpp"
#include "screen.hpp"
#include "watch.hpp"

using namespace Prova;

Game::Game(int width, int height, std::string title)
{
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    std::string error(SDL_GetError());
    throw std::runtime_error("Initialization Error: " + error);
  }
  
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  _window = SDL_CreateWindow(
    title.c_str(),
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    width, height,
    SDL_WINDOW_OPENGL
  );

  screen = new Screen(this);
  screen->_width = width;
  screen->_height = height;
}

void Game::SetTitle(std::string title)
{
  SDL_SetWindowTitle(_window, title.c_str());
}

void Game::ToggleFullscreen()
{
  _isFullscreen = !_isFullscreen;

  SDL_SetWindowFullscreen(
    _window,
    _isFullscreen ? SDL_WINDOW_FULLSCREEN : 0
  );
}

void Game::Start(Scene* scene)
{
  if(_running)
    throw "Attempt to start game while it is already running";
  
  _running = true;
  this->scene = scene;
  this->scene->game = this;
  this->scene->input = &input;
  
  Loop();

  // cleanup after finishing the final loop
  CleanUp();
}

void Game::Loop()
{
  int lag = 0;
  Watch watch;
  watch.Start();

  while(_running)
  {
    int frameDuration = 1000/FPS;
    lag += watch.GetElapsedMilliseconds();
    watch.Restart();

    while(lag >= frameDuration)
    {
      Update();
      lag -= frameDuration;
    }

    Draw();

    // give the processor a break if we are ahead of schedule
    int sleepTime = frameDuration - watch.GetElapsedMilliseconds() - lag;

    if(sleepTime > 0)
      SDL_Delay(sleepTime);
  }
}

void Game::Update()
{
  SDL_Event e;

  while(SDL_PollEvent(&e) != 0)
  {
    if(e.type == SDL_QUIT)
    {
      Close();
      return;
    }
  }

  input.Update();
  scene->Update();
}

void Game::Draw()
{
  screen->BeginDraw();
  scene->Draw(*screen);
}

void Game::SwapScene(Scene* scene)
{
  if(!_running)
    throw "Set initial scene through Game::Start(Scene*)";
  
  delete this->scene;
  this->scene = scene;
  this->scene->game = this;
  this->scene->input = &input;
}

void Game::Close()
{
  _running = false;
}

void Game::CleanUp()
{
  if(scene != nullptr)
    delete scene;
  
  delete screen;
  
  SDL_DestroyWindow(_window);
  SDL_Quit();
}