#include <vector>
#include <yaml-cpp/node/parse.h>
#include "level_loader.hpp"

namespace Arcpp {
  Level LevelLoader::load_level(const std::string &file_path, const std::string &level_name) {
    Level lg;
    YAML::Node file_node = YAML::LoadFile(file_path);
    YAML::Node level_node = file_node[level_name];

    m_parse_bricks_amount(lg, level_node);
    m_parse_player_health(lg, level_node);
    m_parse_all_bricks(lg, level_node);

    return lg;
  }

  void LevelLoader::m_parse_bricks_amount(Level &level, const YAML::Node &node) {
    level.bricks_amounts.x = node["width"].as<float>();
    level.bricks_amounts.y = node["height"].as<float>();
    m_bricks_amount = level.bricks_amounts;

    m_spacer = m_settings->screen_width / 150.0f;
    float additional_space_x = m_spacer * (level.bricks_amounts.x + 1);
    float additional_space_y = m_spacer * level.bricks_amounts.y;

    this->m_brick_size.x = (m_settings->screen_width - additional_space_x) / level.bricks_amounts.x;
    this->m_brick_size.y = (m_settings->screen_height / 3.0f - additional_space_y) / level.bricks_amounts.y;
  }

  void LevelLoader::m_parse_player_health(Level &level, const YAML::Node &node) {
    level.max_player_health = node["player_health"].as<int>();
  }

  void LevelLoader::m_parse_all_bricks(Level &level, const YAML::Node &node) {
    level.bricks.reserve(level.bricks_amounts.x * level.bricks_amounts.y);

    std::vector<YAML::Node> bricks = node["bricks"].as<std::vector<YAML::Node>>();

    for (auto &brick : bricks)
      level.bricks.push_back(m_parse_brick(brick));
  }

  Brick LevelLoader::m_parse_brick(const YAML::Node &node) {
    Vector2 position { node["position"]["x"].as<float>(), node["position"]["y"].as<float>() };
    Vector2 coordinates = m_adjust_coordinates(position);

    Rectangle hitbox { coordinates.x, coordinates.y, m_brick_size.x, m_brick_size.y };

    int health = node["health"].as<int>();
    BonusType bonus_type = static_cast<BonusType>(node["bonus_type"].as<int>());

    Brick b { health, bonus_type, hitbox };

    return b;
  }

  Vector2 LevelLoader::m_adjust_coordinates(const Vector2 &position) {
    Vector2 res;
    res.x = (position.x + 1) * m_spacer + position.x * m_brick_size.x;
    res.y = (position.y + 1) * m_spacer + position.y * m_brick_size.y;

    return res;
  }
}
