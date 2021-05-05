#include "game_element.h"

#include "cpputils/graphics/image.h"

bool GameElement::IntersectsWith(const GameElement* game) {
  return !(GetX() > game->GetX() + game->GetWidth() ||
           game->GetX() > GetX() + GetWidth() ||
           GetY() > game->GetY() + game->GetHeight() ||
           game->GetY() > GetY() + GetHeight());
}

bool GameElement::IsOutOfBounds(const graphics::Image &image) {
  if (GetX() < 0 || GetX() + GetWidth() > image.GetWidth()) {
    return true;
  } else if (GetY() < 0 || GetY() + GetHeight() > image.GetHeight()) {
    return true;
  } else {
    return false;
  }
}
