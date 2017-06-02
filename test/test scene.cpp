#include "engine.hpp"
#include "cowboy.cpp"
#include "cactus.cpp"

// junky code to test if things are working fast

class Test : public Scene
{
  public:
    Test()
    {
      // Z sorting for 2D
      // Distance sorting for 3D
      sortingMethod = SortingMethod::Z;

      AddEntity(new Cowboy);
      AddEntity(new Cactus);
      camera.scale.x = 2;
      camera.scale.y = 2;
    }
};