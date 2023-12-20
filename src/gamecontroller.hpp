#pragma once

#include "gamemodel.hpp"

namespace Arcpp {
  class GameController {
  private:
    GameModel *m_gm;

  public:
    GameController(GameModel *gm);
    void handle_input();
  };
}
