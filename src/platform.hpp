#pragma once

#include <raylib.h>
#include "settings.hpp"

namespace Arcpp {
  class Platform {
  private:
    Settings *m_settings;

  public:
    Platform();

    float speed;
    float velocity;
    Rectangle hitbox;

    void move_right(float dt);
    void move_left(float dt);
    void stop();
  };
}
