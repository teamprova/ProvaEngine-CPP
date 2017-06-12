#include "engine.hpp"

class Cactus : public Prova::Entity
{
  Prova::Sprite sprite;

  public:
    Cactus()
      : sprite("assets/cactus2.png", 32, 46)
    {
      sprite.origin.x = 16;
      sprite.origin.y = 46;
      
      position.x = 0;
      position.y = 0;
    }
    void Draw(Prova::Screen& screen)
    {
      position.z = position.y;
      screen.DrawSprite(sprite, position);
    }
};