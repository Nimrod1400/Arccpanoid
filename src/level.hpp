#pragma once

#include <string>
#include <vector>
#include <raylib.h>
#include "brick.hpp"
#include "ball.hpp"

namespace Arcpp {
  class Level {
  public:
    std::string m_level_name;
    Vector2 bricks_amounts;
    std::vector<Brick> bricks;
    int max_player_health;

    void strike_brick(Ball &ball);
  };
}
