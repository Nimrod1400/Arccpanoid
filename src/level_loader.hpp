#pragma once

#include <string>
#include <yaml-cpp/node/node.h>
#include "brick.hpp"
#include "level.hpp"
#include "settings.hpp"

namespace Arcpp {
  class LevelLoader {
  private:
    Settings *m_settings = Settings::instance();

    void m_parse_player_health(Level &level, const YAML::Node &node);
    void m_parse_bricks_amount(Level &level, const YAML::Node &node);
    void m_parse_all_bricks(Level &level, const YAML::Node &node);
    Brick m_parse_brick(const YAML::Node &node);

  public:
    float spacer;
    Vector2 bricks_amount;
    Vector2 brick_size;

    Level load_level(const YAML::Node &levels, const std::string &level_name);
    float calculate_spacer(Vector2 screen_params);
    Vector2 adjust_coordinates(const Vector2 &position);
  };
}
