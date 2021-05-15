#include "game.h"

void Game::Start() { game_screen.ShowUntilClosed(); }

void Game::LaunchProjectiles() {
  for (int k = 0; k < opponent_obj.size(); k++) {
    if (opponent_obj[k]->LaunchProjectile() != nullptr) {
      std::unique_ptr<OpponentProjectile> new_proj =
          std::make_unique<OpponentProjectile>(opponent_obj[k]->GetX(),
                                               opponent_obj[k]->GetY());
      opponent_proj_.push_back(std::move(new_proj));
    }
  }
}

void Game::RemoveInactive() {
  for (int k = 0; k < opponent_obj.size(); k++) {
    if (opponent_obj[k]->GetIsActive() == false) {
      opponent_obj.erase(opponent_obj.begin());
      k = k - 1;
    }
  }

  for (int k = 0; k < opponent_proj_.size(); k++) {
    if (opponent_proj_[k]->GetIsActive() == false) {
      opponent_proj_.erase(opponent_proj_.begin());
      k = k - 1;
    }
  }

  for (int k = 0; k < player_proj_.size(); k++) {
    if (player_proj_[k]->GetIsActive() == false) {
      player_proj_.erase(player_proj_.begin());
      k = k - 1;
    }
  }
}
