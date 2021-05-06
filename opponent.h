#include <iostream>

#ifndef OPPONENT_H
#define OPPONENT_H
#include "cpputils/graphics/image.h"
#include "game_element.h"
#include <memory>

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : OpponentProjectile(0, 0) {}
  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}

  void Draw(graphics::Image &brickShot) override;

  void Move(const graphics::Image &brickShot) override;
};

class Opponent : public GameElement {
 public:
  Opponent() : Opponent(0, 0) {}
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}

  void Draw(graphics::Image &brick) override;

  void Move(const graphics::Image &brick) override;

  std::unique_ptr<OpponentProjectile> LaunchProjectile();

 private:
  int rateCounter = 0;
};
#endif
