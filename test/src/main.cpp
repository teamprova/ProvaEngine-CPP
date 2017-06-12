#include <stdexcept>
#include <iostream>
#include "engine.hpp"
#include "test scene.cpp"

int main()
{
  try
  {
    Prova::Game game(800, 600, "Hello World!");
    game.Start(new Test);
  }
  catch(std::exception& e)
  {
    std::cout << e.what() << "\n";
    return 1;
  }
  
  return 0;
}
