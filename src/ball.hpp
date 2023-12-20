#pragma once

#include <raylib.h>
#include "brick.hpp"
#include "platform.hpp"
#include "settings.hpp"

namespace Arcpp {
  class Ball {
  private:
    Settings *m_settings;
    float m_velocity_scalar;
    float m_spacer;
    void m_randomise_velocity();
    bool m_rectangle_bounce(const Rectangle &rec);

  public:
    Ball(const Platform &platform);
    bool is_active;
    int damage;
    Color color;
    Vector2 center;
    float radius;
    Vector2 velocity;

    void update_position(float delta_time);
    void follow_platform(const Platform &platform);
    void reset();
    bool is_lost();
    void wall_bounce();
    void platform_bounce(const Platform &platform);
    void brick_bounce(const Brick &brick);
  };
}
