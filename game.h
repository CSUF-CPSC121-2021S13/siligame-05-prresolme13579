#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() : Game(800, 600) {}
  Game(const int &width, const int &height) {
    game_screen.Initialize(width, height);
  }

  void CreateOpponents() {
    std::unique_ptr<Opponent> panda =
        std::make_unique<Opponent>(game_screen.GetWidth() * 0.5, 0);
    opponent_obj.push_back(std::move(panda));
  }

  void Init() {
    game_screen.AddMouseEventListener(*this);
    game_screen.AddAnimationEventListener(*this);

    CreateOpponents();

    player_.SetX(300);
    player_.SetY(400);
  }

  void Start();

  Player &GetPlayer() { return player_; }
  graphics::Image &GetGameScreen() { return game_screen; }
  std::vector<std::unique_ptr<Opponent>> &GetOpponents() {
    return opponent_obj;
  }
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return opponent_proj_;
  }
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return player_proj_;
  }

  void MoveGameElements() {
    for (int k = 0; k < opponent_obj.size(); k++) {
      if (opponent_obj[k]->GetIsActive()) {
        opponent_obj[k]->Move(game_screen);
      }
    }
    for (int k = 0; k < opponent_proj_.size(); k++) {
      if (opponent_proj_[k]->GetIsActive()) {
        opponent_proj_[k]->Move(game_screen);
      }
    }
    for (int k = 0; k < player_proj_.size(); k++) {
      if (player_proj_[k]->GetIsActive()) {
        player_proj_[k]->Move(game_screen);
      }
    }
  }

  void FilterIntersections() {
    for (int k = 0; k < opponent_obj.size(); k++) {
      if (opponent_obj[k]->IntersectsWith(&player_)) {
        opponent_obj[k]->SetIsActive(false);
        player_.SetIsActive(false);
        has_lost_ = true;
      }
    }
    for (int k = 0; k < opponent_proj_.size(); k++) {
      if (opponent_proj_[k]->IntersectsWith(&player_)) {
        opponent_proj_[k]->SetIsActive(false);
        player_.SetIsActive(false);
        has_lost_ = true;
      }
    }
    for (int k = 0; k < player_proj_.size(); k++) {
      for (int n = 0; n < opponent_obj.size(); n++) {
        if (player_proj_[k]->IntersectsWith(opponent_obj[n].get())) {
          player_proj_[k]->SetIsActive(false);
          opponent_obj[n]->SetIsActive(false);
          if (player_.GetIsActive() == true) {
            p_score_ = p_score_ + 1;
          }
        }
      }
    }
  }

  void UpdateScreen() {
    std::string score_message = "score: ";
    score_message += p_score_;
    game_screen.DrawRectangle(0, 0, game_screen.GetWidth(),
                              game_screen.GetHeight(), 255, 255, 255);
    game_screen.DrawText(0, 0, score_message, 20, 0, 200, 225);
    if (has_lost_ == true) {
      game_screen.DrawText(game_screen.GetWidth() * 0.5,
                           game_screen.GetHeight() * 0.25, "game over", 20, 0,
                           200, 225);
    }

    for (int k = 0; k < opponent_obj.size(); k++) {
      if (opponent_obj[k]->GetIsActive()) {
        opponent_obj[k]->Draw(game_screen);
      }
    }
    for (int k = 0; k < opponent_proj_.size(); k++) {
      if (opponent_proj_[k]->GetIsActive()) {
        opponent_proj_[k]->Draw(game_screen);
      }
    }
    for (int k = 0; k < player_proj_.size(); k++) {
      if (player_proj_[k]->GetIsActive()) {
        player_proj_[k]->Draw(game_screen);
      }
    }
    if (player_.GetIsActive()) {
      player_.Draw(game_screen);
    }
  }

  void OnAnimationStep() override {
    if (opponent_obj.size() == 0) {
      CreateOpponents();
    }
    MoveGameElements();
    LaunchProjectiles();
    FilterIntersections();
    UpdateScreen();
    RemoveInactive();
    game_screen.Flush();
  }

  void OnMouseEvent(const graphics::MouseEvent &event) override {
    if (event.GetX() > 0 && event.GetX() < game_screen.GetWidth() &&
        event.GetY() > 0 && event.GetY() < game_screen.GetHeight()) {
      player_.SetX(event.GetX() - (player_.GetWidth() * 0.5));
      player_.SetY(event.GetY() - (player_.GetHeight() * 0.5));
    }
    if (event.GetMouseAction() == graphics::MouseAction::kPressed ||
        event.GetMouseAction() == graphics::MouseAction::kDragged) {
      std::unique_ptr<PlayerProjectile> fresh_proj_b =
          std::make_unique<PlayerProjectile>(player_.GetX(), player_.GetY());
      player_proj_.push_back(std::move(fresh_proj_b));
    }
  }

  int GetScore() const { return p_score_; }
  bool HasLost() const { return has_lost_; }

  void LaunchProjectiles();
  void RemoveInactive();

 private:
  int p_score_ = 0;
  bool has_lost_ = false;
  Player player_;
  graphics::Image game_screen;
  std::vector<std::unique_ptr<Opponent>> opponent_obj;
  std::vector<std::unique_ptr<OpponentProjectile>> opponent_proj_;
  std::vector<std::unique_ptr<PlayerProjectile>> player_proj_;
};

#endif
