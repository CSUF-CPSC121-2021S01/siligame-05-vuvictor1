#include <iostream>
#include <vector>
#include "cpputils/graphics/image.h"
#include "game.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

int main() {
  Game my_game;
  my_game.Init();
  my_game.OnAnimationStep();
  my_game.Start();
}
