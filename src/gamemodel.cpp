#include <algorithm>
#include <raylib.h>
#include "brick.hpp"
#include "gamemodel.hpp"

namespace Arcpp {
  GameModel::GameModel(const std::string &path_to_levels, const std::string &level_name) :
    platform { },
    ball { platform }
  {
    LevelLoader ll;
    current_level = ll.load_level(path_to_levels, level_name);
    m_settings = Settings::instance();
  }

  void GameModel::update_state() {
    if (!ball.is_active)
      ball.follow_platform(platform);
    else {
      ball.update_position(GetFrameTime());
      ball.platform_bounce(platform);
      ball.wall_bounce();

      current_level.strike_brick(ball);

      if (ball.is_lost()) {
        player_health--;
        ball.reset();
      }
    }
  }

  inline bool GameModel::is_game_over() {
    return player_health <= 0;
  }
}
