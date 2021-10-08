#include "player.h"

#include "cpputils/graphics/image.h"
#include "game.h"
#include "game_element.h"
#include "opponent.h"

void Player::Draw(graphics::Image &player) {
  graphics::Image play(50, 50);

  graphics::Color teal(0, 255, 255);
  graphics::Color black(0, 0, 0);
  graphics::Color white(255, 255, 255);
  graphics::Color red(250, 30, 0);

  play.DrawRectangle(4, 11, 6, 5, red);
  play.DrawRectangle(10, 9, 30, 7, red);
  play.DrawRectangle(9, 16, 30, 23, teal);
  play.DrawCircle(17, 20, 2, black);
  play.DrawCircle(29, 21, 3, black);
  play.DrawCircle(23, 33, 4, white);

  for (int i = 0; i < height_; i++) {
    for (int k = 0; k < width_; k++) {
      player.SetColor(x_ + k, y_ + i, play.GetColor(k, i));
    }
  }
}

void Player::Move(const graphics::Image &image) {}

void PlayerProjectile::Draw(graphics::Image &playerShot) {
  graphics::Image pShot(5, 5);

  graphics::Color gray(55, 55, 55);
  graphics::Color brown(150, 75, 0);

  pShot.DrawRectangle(0, 0, 5, 2, gray);
  pShot.DrawRectangle(2, 2, 1, 3, brown);

  for (int i = 0; i < height_; i++) {
    for (int k = 0; k < width_; k++) {
      playerShot.SetColor(x_ + k, y_ + i, pShot.GetColor(k, i));
    }
  }
}

void PlayerProjectile::Move(const graphics::Image &image) {
  SetY(GetY() - 3);
  SetX(GetX() - 3);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}
