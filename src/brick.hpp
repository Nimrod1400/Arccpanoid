#pragma once

#include <raylib.h>
#include "bonus_type.hpp"

namespace Arcpp {
  class Brick {
  public:
    Brick(int health, BonusType bonus_type, Rectangle hitbox);

    int health;
    Color color;
    BonusType bonus_type;
    Rectangle hitbox;

    void get_damage(int damage);
    void update_color();
  };
}
