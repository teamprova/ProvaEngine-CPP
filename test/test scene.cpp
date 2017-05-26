#include "engine.hpp"

// junky code to test if things are working fast

class Test : public Scene
{
  public:
    Test()
    {
      sprite = new Sprite("assets/cowboy.png", 31, 36);
      sprite->CreateAnimation(0, 0, 15, .07f);
      sprite->CreateAnimation(1, 1, 6, .1f);
      sprite->PlayAnimation(1, true);
      sprite->scale.x = 2;
      sprite->scale.y = 2;
      sprite->origin.x = 12;
      sprite->origin.y = 0;

      pos.x = 400;
      pos.y = 300;
    }
  protected:
    void Update() override
    {
      Vector2 vel;

      if(IsKeyDown(Keys::W))
        vel.y -= 1;
      if(IsKeyDown(Keys::S))
        vel.y += 1;
      if(IsKeyDown(Keys::A))
      {
        vel.x -= 1;
        sprite->scale.x = -2;
      }
      if(IsKeyDown(Keys::D))
      {
        vel.x += 1;
        sprite->scale.x = 2;
      }

      vel *= 5;
      pos += vel;
    }
    void Draw(Canvas* canvas) override
    {
      canvas->Clear(0, 0, 0);

      canvas->DrawSprite(sprite, pos);

      canvas->SwapBuffer();
    }
  private:
    Sprite* sprite;
    Vector2 pos;
};