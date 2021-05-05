#include <iostream>
#include <string>

#include "cpputils/graphics/image.h"
#include "game_element.h"

#ifndef PLAYER_H
#define PLAYER_H

class Opponent;
class OpponentProjectile;

class Player : public GameElement {
 public:
  Player() : Player(0, 0) {}
  Player(int x, int y) : GameElement(x, y, 50, 50) {}

  void Draw(graphics::Image &brick) override;

  void Move(const graphics::Image &image) override;
};

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile() : PlayerProjectile(0, 0) {}
  PlayerProjectile(int x, int y) : GameElement(x, y, 5, 5) {}

  void Draw(graphics::Image &playerShot) override;

  void Move(const graphics::Image &image) override;
};
#endif
