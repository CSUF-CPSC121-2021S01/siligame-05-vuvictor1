#include "game.h"

#include <iostream>
#include <vector>
#include <memory>

#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"


void Game::CreateOpponents() {
  for (int i = 0; i < 4; i++) {
    brick_.push_back(std::make_unique<Opponent>(50 * i + 15, 50));
  }
}

void Game::Init() {
  player_.SetX(500);
  player_.SetY(500);
  CreateOpponents();

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
  for (int p = 0; p < playerShot_.size(); p++) {
    playerShot_[p]->Move(screen_);
  }
}

void Game::Start() { screen_.ShowUntilClosed(); }

void Game::FilterIntersections() {
  for (int i = 0; i < brick_.size(); i++) {
    if (player_.IntersectsWith(brick_[i].get())) {
      player_.SetIsActive(false);
      brick_[i]->SetIsActive(false);
      lose_ = true;
    }
  }
  for (int i = 0; i < brickShot_.size(); i++) {
    if (brickShot_[i]->IntersectsWith(&player_)) {
      player_.SetIsActive(false);
      brickShot_[i]->SetIsActive(false);
      lose_ = true;
    }
  }
  for (int p = 0; p < playerShot_.size(); p++) {
    for (int k = 0; k < brick_.size(); k++) {
      if (playerShot_[p]->IntersectsWith(brick_[k].get())) {
        playerShot_[p]->SetIsActive(false);
        brick_[k]->SetIsActive(false);
        if(player_.GetIsActive()) {
          score_++;
        }
      }
    }
  }
}

void Game::UpdateScreen() {
  screen_.DrawRectangle(0, 0, 800, 600, 255, 255, 255);
  screen_.DrawText(10, 10, std::to_string(score_), 35, 0, 0, 0);
  for (int i = 0; i < brick_.size(); i++) {
    if (brick_[i]->GetIsActive() == true) brick_[i]->Draw(screen_);
  }
  for (int i = 0; i < brickShot_.size(); i++) {
    if (brickShot_[i]->GetIsActive() == true) brickShot_[i]->Draw(screen_);
  }
  for (int i = 0; i < playerShot_.size(); i++) {
    if (playerShot_[i]->GetIsActive() == true) playerShot_[i]->Draw(screen_);
  }
  if (player_.GetIsActive() == true) player_.Draw(screen_);
  else screen_.DrawText(200, 200, "You lose", 125, 245, 70, 65);
}


void Game::OnAnimationStep() {
  if (brick_.size() == 0) CreateOpponents();
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  screen_.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent &mouseObject) {
  if (mouseObject.GetMouseAction() == graphics::MouseAction::kPressed ||
        mouseObject.GetMouseAction() == graphics::MouseAction::kDragged) {
      std::unique_ptr<PlayerProjectile> projectile;
      projectile = std::make_unique<PlayerProjectile>();
      projectile->SetX(mouseObject.GetX());
      projectile->SetY(mouseObject.GetY());
      playerShot_.push_back(std::move(projectile));
    }
    if (mouseObject.GetX() < screen_.GetWidth() && mouseObject.GetY() < screen_.GetHeight() &&
        mouseObject.GetX() > 0 && mouseObject.GetY() > 0) {
      player_.SetX(mouseObject.GetX() - player_.GetWidth() / 2);
      player_.SetY(mouseObject.GetY() - player_.GetHeight() / 2);
    }
}
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
      std::unique_ptr<OpponentProjectile> Fire;
      Fire = std::unique_ptr<OpponentProjectile>();
      Fire->SetX(brick_[i]->GetX());
      Fire->SetY(brick_[i]->GetY());
      brickShot_.push_back(std::move(Fire));
    }
  }
}
