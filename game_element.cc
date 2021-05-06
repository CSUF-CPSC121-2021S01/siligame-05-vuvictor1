#include "game_element.h"

bool GameElement::IntersectsWith(GameElement *game) {
  return !(GetX() > game->GetX() + game->GetWidth() ||
           game->GetX() > GetX() + GetWidth() ||
           GetY() > game->GetY() + game->GetHeight() ||
           game->GetY() > GetY() + GetHeight());
}

bool GameElement::IsOutOfBounds(const graphics::Image &check) {
  if (GetX() < 0 || GetX() + GetWidth() > check.GetWidth()) {
    return true;
  } else if (GetY() < 0 || GetY() + GetHeight() > check.GetHeight()) {
    return true;
  } else {
    return false;
  }
}
