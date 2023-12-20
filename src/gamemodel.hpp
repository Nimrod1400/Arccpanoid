#pragma once

#include <string>
#include "ball.hpp"
#include "platform.hpp"
#include "level.hpp"
#include "level_loader.hpp"
#include "settings.hpp"

namespace Arcpp {
  class GameModel {
  private:
    Settings *m_settings;

  public:
    GameModel(const std::string &path_to_levels, const std::string &level_name);

    Level current_level;
    Platform platform;
    Ball ball;
    int player_health;

    void update_state();
    inline bool is_game_over();
  };
}
