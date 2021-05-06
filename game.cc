#include "game.h"
#include <iostream>
#include <memory>
#include <vector>
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

std::vector<std::unique_ptr<Opponent>>& Game::GetOpponents() {
  return brick_;
}
std::vector<std::unique_ptr<OpponentProjectile>>&
Game::GetOpponentProjectiles() {
  return brickShot_;
}
std::vector<std::unique_ptr<PlayerProjectile>>& Game::GetPlayerProjectiles() {
  return playerShot_;
}
Player& Game::GetPlayer() { return player_; }
graphics::Image& Game::GetGameScreen() { return screen_; }

void Game::CreateOpponents() {
  std::unique_ptr<Opponent> opponent;
  srand((unsigned)time(0));
  for (int i = 0; i < 3; i++) {
    opponent = std::make_unique<Opponent>();
    int x = rand() % 750;
    int y = rand() % 550;
    opponent->SetX(x);
    opponent->SetY(y);
    brick_.push_back(std::move(opponent));
  }
}

void Game::Init() {
  srand((unsigned)time(0));
  int x = rand() % 749;
  int y = rand() % 549;
  player_.SetX(x);
  player_.SetY(y);
  screen_.AddMouseEventListener(*this);
  screen_.AddAnimationEventListener(*this);
}

void Game::MoveGameElements() {
  for (int i = 0; i < brick_.size(); i++) {
    brick_[i]->Move(screen_);
  }
  for (int j = 0; j < brickShot_.size(); j++) {
    brickShot_[j]->Move(screen_);
  }
  for (int k = 0; k < playerShot_.size(); k++) {
    playerShot_[k]->Move(screen_);
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < brick_.size(); i++) {
    if (player_.IntersectsWith(brick_[i].get()) == true) {
      player_.SetIsActive(false);
      brick_[i]->SetIsActive(false);
      lost_ = true;
    }
  }
  for (int i = 0; i < playerShot_.size(); i++) {
    for (int j = 0; j < brick_.size(); j++) {
      if (playerShot_[i]->IntersectsWith(brick_[j].get()) == true) {
        playerShot_[i]->SetIsActive(false);
        brick_[j]->SetIsActive(false);
        if (player_.GetIsActive() == true) {
          score_ = score_ + 1;
        }
      }
    }
  }
  for (int i = 0; i < brickShot_.size(); i++) {
   if (brickShot_[i]->IntersectsWith(&player_)) {
     player_.SetIsActive(false);
     brickShot_[i]->SetIsActive(false);
     lost_ = true;
   }
 }
}

void Game::UpdateScreen() {
  string score = std::to_string(GetScore());
  string text = "score: " + score;
  screen_.DrawRectangle(0, 0, 800, 600, 255, 255, 255);
  screen_.DrawText(0, 0, text, 50, 245, 69, 66);
  for (int i = 0; i < brick_.size(); i++) {
    if (brick_[i]->GetIsActive() == true) {
      brick_[i]->Draw(screen_);
    }
  }
  for (int j = 0; j < brickShot_.size(); j++) {
    if (brickShot_[j]->GetIsActive() == true) {
      brickShot_[j]->Draw(screen_);
    }
  }
  for (int k = 0; k < playerShot_.size(); k++) {
    if (playerShot_[k]->GetIsActive() == true) {
      playerShot_[k]->Draw(screen_);
    }
  }
  if (player_.GetIsActive() == true) {
    player_.Draw(screen_);
  } else {
    screen_.DrawText(300, 300, "Game over", 100, 245, 69, 66);
  }
}

int Game::GetScore() { return score_; }

bool Game::HasLost() { return lost_; }

void Game::OnAnimationStep() {
  if (brick_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  screen_.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent& mouse) {
  if (mouse.GetMouseAction() == graphics::MouseAction::kPressed ||
      mouse.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> projectile;
    projectile = std::make_unique<PlayerProjectile>();
    projectile->SetX(mouse.GetX());
    projectile->SetY(mouse.GetY());
    playerShot_.push_back(std::move(projectile));
  }
  if (mouse.GetX() < screen_.GetWidth() && mouse.GetY() < screen_.GetHeight() &&
      mouse.GetX() > 0 && mouse.GetY() > 0) {
    player_.SetX(mouse.GetX() - player_.GetWidth() / 2);
    player_.SetY(mouse.GetY() - player_.GetHeight() / 2);
  }
}

void Game::Start() { screen_.ShowUntilClosed(); }

void Game::RemoveInactive() {
  for (int i = 0; i < brick_.size(); i++) {
    if (brick_[i]->GetIsActive() == false) {
      brick_.erase(brick_.begin() + i);
      i = i - 1;
    }
  }
  for (int i = 0; i < brickShot_.size(); i++) {
    if (brickShot_[i]->GetIsActive() == false) {
      brickShot_.erase(brickShot_.begin() + i);
      i = i - 1;
    }
  }
  for (int i = 0; i < playerShot_.size(); i++) {
    if (playerShot_[i]->GetIsActive() == false) {
      playerShot_.erase(playerShot_.begin() + i);
      i = i - 1;
    }
  }
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < brick_.size(); i++) {
    if (brick_[i]->LaunchProjectile() != nullptr) {
      std::unique_ptr<OpponentProjectile> projectile;
      projectile = std::make_unique<OpponentProjectile>();
      projectile->SetX(brick_[i]->GetX());
      projectile->SetY(brick_[i]->GetY());
      brickShot_.push_back(std::move(projectile));
    }
  }
}
