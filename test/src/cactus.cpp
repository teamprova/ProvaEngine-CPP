#include "engine.hpp"

class Cactus : public Prova::Entity
{
  Prova::Sprite sprite;
  Prova::RectCollider collider = Prova::RectCollider(this, 31, 10);

  public:
    Cactus()
      : sprite("assets/cactus2.png", 32, 46)
    {
      sprite.origin.x = 16;
      sprite.origin.y = 46;
      
      position.x = 0;
      position.y = 0;

      AddCollider(collider);
    }
    void Draw(Prova::Screen& screen)
    {
      position.z = position.y / 10000;
      screen.DrawSprite(sprite, position);
    }
};