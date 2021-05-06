#include "game_element.h"

#include <iostream>
#include <string>

#include "cpputils/graphics/image.h"

bool GameElement::IntersectsWith(GameElement* game) {
  if (GetX() > game->GetX() + game->GetWidth() ||
      game->GetX() > GetX() + GetWidth() ||
      GetY() > game->GetY() + game->GetHeight() ||
      game->GetY() > GetY() + GetHeight()) {
    return false;
  } else {
    return true;
  }
}

bool GameElement::IsOutOfBounds(const graphics::Image& image) {
  if (GetY() + GetHeight() > image.GetHeight() ||
      GetX() + GetWidth() > image.GetWidth() || GetY() < 0 || GetX() < 0) {
    return true;
  } else {
    return false;
  }
}
