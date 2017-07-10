#include "engine.hpp"

class Cactus : public Prova::Entity
{
  Prova::Sprite sprite;
  Prova::RectCollider collider = Prova::RectCollider(this, 20, 10);

  public:
    Cactus()
      : sprite("assets/cactus2.png", 32, 46)
    {
      sprite.origin.x = 16;
      sprite.origin.y = 41;

      AddCollider(collider);
    }
    void Draw(Prova::Screen& screen)
    {
      float offsetY = screen.GetHeight() / 2 + scene->camera.position.y;

      float range = scene->camera.zFar - scene->camera.zNear;
      position.z = (position.y + offsetY) / range;

      screen.DrawSprite(sprite, position);
    }
};