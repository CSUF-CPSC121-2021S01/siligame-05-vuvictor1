#include "cpputils/graphics/image.h"

#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

class GameElement {
 public:
  GameElement() : GameElement(0, 0, 50, 50) {}

  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height) {}

  int GetX() const { return x_; }
  int GetY() const { return y_; }
  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }

  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }

  virtual void Draw(graphics::Image &image) = 0;
  virtual void Move(const graphics::Image &image) = 0;

  bool GetIsActive() { return is_active_; }
  void SetIsActive(bool is_active) { is_active_ = is_active; }

  bool IntersectsWith(const GameElement *game);
  bool IsOutOfBounds(const graphics::Image &image);

 protected:
  int x_;
  int y_;
  int width_;
  int height_;
  bool is_active_ = true;
};

#endif
