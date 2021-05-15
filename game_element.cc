#include "game_element.h"

#include "cpputils/graphics/image.h"

void GameElement::Helper(graphics::Image &back, std::string &front, int &x_,
                         int &y_) {
  graphics::Image picture;
  picture.Load(front);
  for (int k = 0; k < picture.GetWidth(); k++) {
    for (int n = 0; n < picture.GetHeight(); n++) {
      back.SetColor(k + x_, n + y_, picture.GetColor(k, n));
    }
  }
}

bool GameElement::IsOutOfBounds(const graphics::Image &back) {
  if (x_ < 0 || y_ < 0 || x_ > back.GetWidth() || y_ > back.GetHeight()) {
    return true;
  } else {
    return false;
  }
}
