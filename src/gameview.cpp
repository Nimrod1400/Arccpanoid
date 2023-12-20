#include "gameview.hpp"
#include <raylib.h>

namespace Arcpp {
  GameView::GameView(GameModel *gm) : m_gm { gm }, water { gm->platform } {
    m_settings = Settings::instance();
  }

  void GameView::draw() {
    BeginDrawing();
    {

      ClearBackground(WHITE);

      for (Brick &brick : m_gm->current_level.bricks)
        DrawRectangleRec(brick.hitbox, brick.color);

      DrawRectangleRec(m_gm->platform.hitbox, BLACK);

      DrawCircleV(m_gm->ball.center, m_gm->ball.radius, m_gm->ball.color);

      DrawRectangleRec(water.view, water.color);

    }
    EndDrawing();
  }
}
