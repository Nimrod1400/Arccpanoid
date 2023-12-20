#pragma once

#include <raylib.h>
#include "gamemodel.hpp"
#include "settings.hpp"
#include "water.hpp"

namespace Arcpp {
  class GameView {
  private:
    Settings* m_settings;
    GameModel *m_gm;
    Water water;

    void m_draw_water();
    void m_draw_ball();
    void m_draw_platform();
    void m_draw_level();

  public:
    GameView(GameModel *gm);
    void draw();
  };
}
