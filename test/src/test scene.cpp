#include "engine.hpp"
#include "cowboy.cpp"
#include "cactus.cpp"

// junky code to test if things are working fast

class Test : public Prova::Scene
{
  Cowboy player;
  Cactus cactus;
  
  public:
    Test()
    {
      // Z sorting for 2D
      // Distance sorting for 3D
      sortingMethod = SortingMethod::Z;
      camera.scale.x = 2;
      camera.scale.y = 2;

      AddEntity(cactus);
      AddEntity(player);
    }
};