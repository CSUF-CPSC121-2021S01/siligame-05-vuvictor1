#include <iostream>
#include <vector>

#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

#ifndef GAME_H
#define GAME_H
class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() { screen_.Initialize(800, 600); }
  Game(int width, int height) : screen_(width, height) {}

  std::vector<std::unique_ptr<Opponent>> &GetOpponents() { return brick_; }

  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return brickShot_;
  }

  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() { return playerShot_; }

  Player &GetPlayer() { return player_; }

  // Create member functions
  graphics::Image &GetGameScreen() { return screen_; }

  void Init();
  void Start();
  void CreateOpponents();
  void MoveGameElements();
  void OnAnimationStep();
  void FilterIntersections();
  void LaunchProjectiles();
  void RemoveInactive();
  void UpdateScreen();

  int GetScore() {return score_; }
  bool HasLost() { return lose_; }
  void OnMouseEvent(const graphics::MouseEvent &mouseObject);

 private:
  graphics::Image screen_;
  std::vector<std::unique_ptr<Opponent>> brick_;
  std::vector<std::unique_ptr<OpponentProjectile>> brickShot_;
  std::vector<std::unique_ptr<PlayerProjectile>> playerShot_;
  Player player_;
  int width_;
  int height_;
  int score_ = 0;
  bool lose_;
};
#endif
