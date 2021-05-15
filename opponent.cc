#include "opponent.h"

void Opponent::Draw(graphics::Image &back) {
  std::string variable = "opponent.bmp";
  Helper(back, variable, x_, y_);
}

void Opponent::Move(const graphics::Image &back) {
  if (!IsOutOfBounds(back)) {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  } else {
    is_active = false;
  }
}

void OpponentProjectile::Draw(graphics::Image &back) {
  std::string variable = "oppproj.bmp";
  Helper(back, variable, x_, y_);
}

void OpponentProjectile::Move(const graphics::Image &back) {
  if (!IsOutOfBounds(back)) {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  } else {
    is_active = false;
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  counter_ += 1;
  if (counter_ % 5 == 0) {
    std::unique_ptr<OpponentProjectile> opp_proj =
        std::make_unique<OpponentProjectile>(GetX(), GetY());
    return std::move(opp_proj);
  } else {
    return nullptr;
  }
}
