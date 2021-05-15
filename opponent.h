#ifndef OPPONENT_H
#define OPPONENT_H

#include "cpputils/graphics/image.h"
#include "game_element.h"
class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : GameElement(0, 0, 15, 15) {}
  OpponentProjectile(const int x, const int y) : GameElement(x, y, 15, 15) {}

  void Draw(graphics::Image &back) override;
  void Move(const graphics::Image &back) override;
};

class Opponent : public GameElement {
 public:
  Opponent() : GameElement(0, 0, 50, 50) {}
  Opponent(const int x, const int y) : GameElement(x, y, 50, 50) {}

  void Draw(graphics::Image &back) override;
  void Move(const graphics::Image &back) override;

  std::unique_ptr<OpponentProjectile> LaunchProjectile();

 private:
  int counter_ = 0;
};

#endif
