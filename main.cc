#include <iostream>

#include "game.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

int main() {
  Game gameStart;
  gameStart.Init();
  gameStart.UpdateScreen();
  gameStart.Start();
  return 0;
}
