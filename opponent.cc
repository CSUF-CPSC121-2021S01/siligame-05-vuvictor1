#include "opponent.h"

#include <iostream>
#include <string>

#include "cpputils/graphics/image.h"
#include "game_element.h"

void Opponent::Draw(graphics::Image &brick) {
  graphics::Color red(250, 30, 0);
  graphics::Color white(255, 255, 255);

  graphics::Image brickO(50, 50);

  brickO.DrawRectangle(4, 4, 41, 41, red);
  brickO.DrawRectangle(16, 4, 1, 9, white);
  brickO.DrawRectangle(35, 4, 1, 9, white);
  brickO.DrawRectangle(4, 14, 41, 1, white);
  brickO.DrawRectangle(11, 16, 1, 9, white);
  brickO.DrawRectangle(26, 16, 1, 9, white);
  brickO.DrawRectangle(4, 25, 41, 1, white);
  brickO.DrawRectangle(19, 27, 1, 9, white);
  brickO.DrawRectangle(35, 27, 1, 9, white);
  brickO.DrawRectangle(4, 35, 41, 1, white);
  brickO.DrawRectangle(11, 37, 1, 9, white);
  brickO.DrawRectangle(28, 37, 1, 9, white);

  for (int i = 0; i < height_; i++) {
    for (int k = 0; k < width_; k++) {
      brick.SetColor(x_ + k, y_ + i, brickO.GetColor(k, i));
    }
  }
}

void Opponent::Move(const graphics::Image &image) {
  SetY(GetY() + 1);
  SetX(GetX() + 1);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  if(rateCounter >= 10) {
    std::unique_ptr<OpponentProjectile> Bullet =
    std::make_unique<OpponentProjectile>();
    return Bullet;
  } else {
    rateCounter += 1;
    return nullptr;
  }
}

void OpponentProjectile::Draw(graphics::Image &brickShot) {
  graphics::Image bShot(5, 5);

  graphics::Color red(250, 30, 0);
  graphics::Color yellow(255, 205, 0);

  bShot.DrawCircle(2, 2, 2, yellow);
  bShot.DrawRectangle(2, 2, 1, 1, red);

  for (int i = 0; i < height_; i++) {
    for (int k = 0; k < width_; k++) {
      brickShot.SetColor(x_ + k, y_ + i, bShot.GetColor(k, i));
    }
  }
}

void OpponentProjectile::Move(const graphics::Image &image) {
  SetY(GetY() + 3);
  SetX(GetX() + 3);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}
