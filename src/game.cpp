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
  SDL_SetWindowTitle((SDL_Window*) _window, title.c_str());
}

void Game::ToggleFullscreen()
{
  _isFullscreen = !_isFullscreen;

  SDL_SetWindowFullscreen(
    (SDL_Window*) _window,
    _isFullscreen ? SDL_WINDOW_FULLSCREEN : 0
  );
}

void Game::Start(Scene* scene)
{
  if(_running)
    throw "Attempt to start game while it is already running";
  
  _running = true;
  SetScene(scene);
  
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
  SDL_Event event;

  while(SDL_PollEvent(&event) != 0)
  {
    switch(event.type)
    {
      case SDL_QUIT:
        Close();
        return;
      case SDL_WINDOWEVENT_SIZE_CHANGED:
        screen->_width = event.window.data1;
        screen->_height = event.window.data2;
        break;
    }
  }

  input.Update();
  scene->Update();
}

void Game::Draw()
{
  screen->Clear();
  screen->BeginDraw();
  scene->Draw(*screen);
  screen->SwapBuffer();
}

void Game::SwapScene(Scene* scene)
{
  if(!_running)
    throw "Set initial scene through Game::Start(Scene*)";
  
  delete this->scene;
  SetScene(scene);
}

void Game::SetScene(Scene* scene)
{
  this->scene = scene;
  this->scene->game = this;
  this->scene->input = &input;
  this->scene->Setup();
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
  
  SDL_DestroyWindow((SDL_Window*) _window);
  SDL_Quit();
}