#include "game_element.h"

#include "cpputils/graphics/image.h"

bool GameElement::IntersectsWith(const GameElement *game) {
  return !(GetX() > game->GetX() + game->GetWidth() ||
           game->GetX() > GetX() + GetWidth() ||
           GetY() > game->GetY() + game->GetHeight() ||
           game->GetY() > GetY() + GetHeight());
}

bool GameElement::IsOutOfBounds(const graphics::Image& check) {
  if (GetY() + GetHeight() > check.GetHeight() ||
      GetX() + GetWidth() > check.GetWidth() || GetY() < 0 || GetX() < 0) {
    return true;
  } else {
    return false;
  }
}
