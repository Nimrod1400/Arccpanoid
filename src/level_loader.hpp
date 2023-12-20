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
    Vector2 m_bricks_amount;
    Vector2 m_brick_size;
    float m_spacer;

    void m_parse_player_health(Level &level, const YAML::Node &node);
    void m_parse_bricks_amount(Level &level, const YAML::Node &node);
    void m_parse_all_bricks(Level &level, const YAML::Node &node);
    Brick m_parse_brick(const YAML::Node &node);
    Vector2 m_adjust_coordinates(const Vector2 &position);

  public:
    Level load_level(const std::string &file_path, const std::string &level_name);
  };
}
