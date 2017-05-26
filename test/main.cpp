#include "engine.hpp"
#include "test scene.cpp"

int main()
{
  Game game(800, 600, "Hello World!");
  game.Start(new Test);
  
  return 0;
}
