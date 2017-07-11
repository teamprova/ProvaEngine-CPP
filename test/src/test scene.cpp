#include "engine.hpp"
#include "cowboy.cpp"
#include "cactus.cpp"
#include "scorpion.cpp"
#include <list>

// junky code to test if things are working fast

class Test : public Prova::Scene
{
  Cowboy player;
  std::list<Cactus> cacti;
  Scorpion scorpion;
  
  public:
    void Setup() override
    {
      game->screen->SetClearColor(1.00, 0.75, 0.49);

      // Z sorting for 2D
      // Distance sorting for 3D
      camera.projection = Projection::Orthographic;
      camera.sortingMethod = SortingMethod::Z;
      camera.useDepthBuffer = false;
      camera.scale.x = 2;
      camera.scale.y = -2;
      //Debug = true;

      AddEntity(player);
      AddEntity(scorpion);

      for(int x = -10; x < 10; x++)
      {
        cacti.emplace_back();
        Cactus& cactus = cacti.back();
        cactus.position.x = Prova::Math::RandomF(-1, 1) * 200;
        cactus.position.y = Prova::Math::RandomF(-1, 1) * 150;

        AddEntity(cactus);
      }
    }
    void Update() override
    {
      Scene::Update();

      if(input->IsKeyDown(Keys::F11))
        game->ToggleFullscreen();
      
      camera.position.x = player.position.x;
      camera.position.y = player.position.y;

      Prova::Vector2 cameraInput = input->SimulateAxis(Keys::UP, Keys::LEFT, Keys::DOWN, Keys::RIGHT);

      camera.rotation.y -= cameraInput.x;
      camera.position.z += cameraInput.y * 4;
    }
};