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

void Opponent::Move(const graphics::Image& image) {
  SetX(GetX() + 1);
  SetY(GetY() + 1);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
    graphics::Image opponent_; //Maybe delete these two lines to make it work
    Draw(opponent_);
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  counter_ += 1;
  if (counter_ == 5) {
    std::unique_ptr<OpponentProjectile> projectile;
    projectile = std::make_unique<OpponentProjectile>();
    counter_ = 0;
    return projectile;
  } else {
    return nullptr;
  }
}

void OpponentProjectile::Move(const graphics::Image& image) {
  SetY(GetY() + 3);
  if (IsOutOfBounds(image) == true) {
    SetIsActive(false);
  } else {
    graphics::Image o_projectile; //same here maybe delete two lines
    Draw(o_projectile);
  }
}
