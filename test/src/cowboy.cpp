#include "engine.hpp"

class Cowboy : public Entity
{
  Sprite sprite;

  enum Animations {
    WALK,
    SHOOT
  };

  public:
    Cowboy()
      : sprite("assets/cowboy.png", 31, 36)
    {
      sprite.CreateAnimation(Animations::SHOOT, 0, 15, .07f);
      sprite.CreateAnimation(Animations::WALK, 1, 6, .1f);
      sprite.PlayAnimation(Animations::WALK, true);
      sprite.origin.x = 12;
      sprite.origin.y = 36;

      position.x = 0;
      position.y = 0;
    }
    void Update() override
    {
      int currentAnimation = sprite.GetCurrentAnimation();
      bool animationFinished = sprite.IsAnimationFinished();
      bool shooting = currentAnimation == Animations::SHOOT && !animationFinished;
      
      if(IsKeyDown(Keys::SPACE) && !shooting)
        sprite.PlayAnimation(Animations::SHOOT, false);
      if(animationFinished)
        sprite.PlayAnimation(Animations::WALK, true);
      
      //sprite.angle += 1;

      if(!shooting)
        Walk();
    }
    void Walk()
    {
      Vector2 displacement;

      if(IsKeyDown(Keys::W))
        displacement.y -= 1;
      if(IsKeyDown(Keys::S))
        displacement.y += 1;
      if(IsKeyDown(Keys::A))
      {
        displacement.x -= 1;
        sprite.scale.x = -1;
      }
      if(IsKeyDown(Keys::D))
      {
        displacement.x += 1;
        sprite.scale.x = 1;
      }

      position += displacement.Normalize() * 2;
    }
    void Draw(Screen& screen) override
    {
      position.z = position.y;
      screen.DrawSprite(sprite, position);
    }
};