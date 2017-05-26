#include "engine.hpp"
#include "cowboy.cpp"

// junky code to test if things are working fast

class Test : public Scene
{
  public:
    Test()
    {
      AddEntity(new Cowboy);
    }
};