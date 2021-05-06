#include "game.h"
#include <iostream>
#include <memory>
#include <vector>
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

void Game::CreateOpponents() {
  std::unique_ptr<Opponent> bricks;
  for (int i = 0; i < 2; i++) {
    bricks = std::make_unique<Opponent>();
    bricks->SetX(50 * i + 25);
    bricks->SetY(50);
    brick_.push_back(std::move(bricks));
  }
}

void Game::Init() {
  player_.SetX(500);
  player_.SetY(500);
  screen_.AddMouseEventListener(*this);
  screen_.AddAnimationEventListener(*this);
}

void Game::Start() { screen_.ShowUntilClosed(); }

void Game::MoveGameElements() {
  for (int i = 0; i < brick_.size(); i++) {
    brick_[i]->Move(screen_);
  }
  for (int k = 0; k < brickShot_.size(); k++) {
    brickShot_[k]->Move(screen_);
  }
  for (int p = 0; p < playerShot_.size(); p++) {
    playerShot_[p]->Move(screen_);
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < brick_.size(); i++) {
    if (player_.IntersectsWith(brick_[i].get())) {
      player_.SetIsActive(false);
      brick_[i]->SetIsActive(false);
      lose_ = true;
    }
  }
  for (int h = 0; h < playerShot_.size(); h++) {
    for (int j = 0; j < brick_.size(); j++) {
      if (playerShot_[h]->IntersectsWith(brick_[j].get())) {
        playerShot_[h]->SetIsActive(false);
        brick_[j]->SetIsActive(false);
        if (player_.GetIsActive()) {
          score_ += 1;
        }
      }
    }
  }
  for (int l = 0; l < brickShot_.size(); l++) {
   if (brickShot_[l]->IntersectsWith(&player_)) {
     player_.SetIsActive(false);
     brickShot_[l]->SetIsActive(false);
     lose_ = true;
   }
 }
}

void Game::UpdateScreen() {
  std::string scoreUpdate = std::to_string(GetScore());
  std::string text = "Score: " + scoreUpdate;
  screen_.DrawRectangle(0, 0, 800, 600, 255, 255, 255);
  screen_.DrawText(10, 10, std::to_string(score_), 35, 0, 0, 0);
  for (int i = 0; i < brick_.size(); i++) {
    if (brick_[i]->GetIsActive()) {
      brick_[i]->Draw(screen_);
    }
  }
  for (int j = 0; j < brickShot_.size(); j++) {
    if (brickShot_[j]->GetIsActive()) {
      brickShot_[j]->Draw(screen_);
    }
  }
  for (int k = 0; k < playerShot_.size(); k++) {
    if (playerShot_[k]->GetIsActive()) {
      playerShot_[k]->Draw(screen_);
    }
  }
  if (player_.GetIsActive()) {
    player_.Draw(screen_);
  } else {
    screen_.DrawText(200, 200, "You lose", 125, 245, 70, 65);
  }
}

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

void Game::OnMouseEvent(const graphics::MouseEvent& mouseObject) {
  if (mouseObject.GetMouseAction() == graphics::MouseAction::kPressed ||
      mouseObject.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> bullet;
    bullet = std::make_unique<PlayerProjectile>();
    bullet->SetX(mouseObject.GetX());
    bullet->SetY(mouseObject.GetY());
    playerShot_.push_back(std::move(bullet));
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
      std::unique_ptr<OpponentProjectile> projectile;
      projectile = std::make_unique<OpponentProjectile>();
      projectile->SetX(brick_[i]->GetX());
      projectile->SetY(brick_[i]->GetY());
      brickShot_.push_back(std::move(projectile));
    }
  }
}
