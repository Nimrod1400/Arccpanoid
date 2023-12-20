#include <raylib.h>
#include "gamecontroller.hpp"

namespace Arcpp {
  Arcpp::GameController::GameController(GameModel *gm) : m_gm { gm } { }

  void Arcpp::GameController::handle_input() {
    if (IsKeyDown(KeyboardKey::KEY_D))
      m_gm->platform.move_right(GetFrameTime());

    if (IsKeyDown(KeyboardKey::KEY_A))
      m_gm->platform.move_left(GetFrameTime());

    if (!IsKeyDown(KeyboardKey::KEY_D) && !IsKeyDown(KeyboardKey::KEY_A))
      m_gm->platform.stop();

    if (IsKeyPressed(KeyboardKey::KEY_SPACE))
      m_gm->ball.is_active = true;
  }
}
