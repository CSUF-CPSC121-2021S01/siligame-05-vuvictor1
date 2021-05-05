#include <iostream>

#include "game.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

int main() {
  Game game0;
  game0.Init();
  game0.UpdateScreen();
  game0.Start();
  return 0;
}
