#include "engine.hpp"

class Cowboy : public Entity
{
  Sprite* sprite;

  public:
    Cowboy()
    {
      sprite = new Sprite("assets/cowboy.png", 31, 36);
      sprite->CreateAnimation(0, 0, 15, .07f);
      sprite->CreateAnimation(1, 1, 6, .1f);
      sprite->PlayAnimation(1, true);
      sprite->scale.x = 2;
      sprite->scale.y = 2;
      position.x = 400;
      position.y = 300;
    }
    void Update() override
    {
      Vector2 displacement;

      if(IsKeyDown(Keys::W))
        displacement.y -= 1;
      if(IsKeyDown(Keys::S))
        displacement.y += 1;
      if(IsKeyDown(Keys::A))
      {
        displacement.x -= 1;
        sprite->scale.x = -2;
      }
      if(IsKeyDown(Keys::D))
      {
        displacement.x += 1;
        sprite->scale.x = 2;
      }

      displacement *= 5;
      position += displacement;
    }
    void Draw(Canvas* canvas) override
    {
      canvas->DrawSprite(sprite, position);
    }
};