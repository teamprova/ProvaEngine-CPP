#include "engine.hpp"

class Cowboy : public Prova::Entity
{
  Prova::Sprite sprite;
  Prova::RectCollider collider = Prova::RectCollider(this, 20, 5);

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
      sprite.origin.y = 34;

      position.x = 0;
      position.y = 0;

      AddCollider(collider);
    }
    void Update() override
    {
      int currentAnimation = sprite.GetCurrentAnimation();
      bool animationFinished = sprite.IsAnimationFinished();
      bool shooting = currentAnimation == Animations::SHOOT && !animationFinished;
      
      if(scene->input->IsKeyDown(Keys::SPACE) && !shooting)
        sprite.PlayAnimation(Animations::SHOOT, false);
      if(animationFinished)
        sprite.PlayAnimation(Animations::WALK, true);
      
      //sprite.angle += 1;

      if(!shooting)
        Walk();
    }
    void Walk()
    {
      Prova::Vector2 displacement = scene->input->SimulateAxis(Keys::W, Keys::A, Keys::S, Keys::D);

      if(displacement.x < 0)
        sprite.scale.x = -1;
      else if(displacement.x > 0)
        sprite.scale.x = 1;

      position += displacement * 2;
    }
    void Draw(Prova::Screen& screen) override
    {
      float offsetY = screen.GetHeight() / 2 + scene->camera.position.y;

      float range = scene->camera.zFar - scene->camera.zNear;
      position.z = (position.y + offsetY) / range;

      screen.DrawSprite(sprite, position);
    }
};