#include <iostream>
#include <vector>
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"
using namespace std;

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() : Game(800, 600) {}
  Game(int width, int height) : screen_(width, height) {}
  std::vector<std::unique_ptr<Opponent>>& GetOpponents();
  std::vector<std::unique_ptr<OpponentProjectile>>& GetOpponentProjectiles();
  std::vector<std::unique_ptr<PlayerProjectile>>& GetPlayerProjectiles();
  Player& GetPlayer();
  graphics::Image& GetGameScreen();
  void CreateOpponents();
  void CreateOpponentProjectiles();
  void CreatePlayerProjectiles();
  void Init();
  void UpdateScreen();
  void MoveGameElements();
  void FilterIntersections();
  void OnAnimationStep();
  void OnMouseEvent(const graphics::MouseEvent& mouse);
  void Start();
  int GetScore();
  bool HasLost();
  void RemoveInactive();
  void LaunchProjectiles();

 private:
  graphics::Image screen_;
  std::vector<std::unique_ptr<Opponent>> brick_;
  std::vector<std::unique_ptr<OpponentProjectile>> brickShot_;
  std::vector<std::unique_ptr<PlayerProjectile>> playerShot_;
  Player player_;
  int score_ = 0;
  bool lost_;
};
