#include "engine.hpp"

class Scorpion : public Prova::Entity
{
  Prova::Sprite sprite;

  enum Animations {
    WALK
  };

  public:
    Scorpion()
      : sprite("assets/scorpion.png", 6, 4)
    {
      sprite.CreateAnimation(Animations::WALK, 0, 2, .2f);
      sprite.PlayAnimation(Animations::WALK, true);
      sprite.origin.x = 4;
      sprite.origin.y = 4;
    }
    void Update() override
    {
      Entity& entity = scene->FindClosestEntity(*this);
      
      velocity = entity.position - position;
      velocity = velocity.Normalize();
    }
    void Draw(Prova::Screen& screen) override
    {
      float offsetY = screen.GetHeight() / 2 + scene->camera.position.y;

      float range = scene->camera.zFar - scene->camera.zNear;
      position.z = (position.y + offsetY) / range;

      screen.DrawSprite(sprite, position);
    }
};