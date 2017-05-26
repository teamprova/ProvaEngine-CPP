#include "engine.hpp"

class Test : public Scene
{
  public:
    Test()
    {
      sprite = new Sprite("assets/cowboy.png", 31, 36);
      sprite->CreateAnimation(0, 0, 15, .07f);
      sprite->CreateAnimation(1, 1, 6, .1f);
      sprite->PlayAnimation(1, true);
      sprite->scaleX = 2;
      sprite->scaleY = 2;
    }
  protected:
    void Update() override
    {
      if(IsKeyDown(Keys::W))
        y -= 1;
      if(IsKeyDown(Keys::S))
        y += 1;
      if(IsKeyDown(Keys::A))
        x -= 1;
      if(IsKeyDown(Keys::D))
        x += 1;
    }
    void Draw(Canvas* canvas) override
    {
      canvas->Clear(0, 0, 0);

      canvas->DrawSprite(sprite, x, y);

      canvas->SwapBuffer();
    }
  private:
    Sprite* sprite;
    int x = 400;
    int y = 300;
};