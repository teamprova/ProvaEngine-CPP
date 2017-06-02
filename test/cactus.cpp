#include "engine.hpp"

class Cactus : public Entity
{
  Sprite* sprite;

  public:
    Cactus()
    {
      sprite = new Sprite("assets/cactus2.png", 32, 46);
      sprite->origin.x = 16;
      sprite->origin.y = 46;
      position.x = 0;
      position.y = 0;
    }
    void Draw(Screen* screen)
    {
      position.z = position.y;
      screen->DrawSprite(sprite, position);
    }
    ~Cactus()
    {
      delete sprite;
    }
};