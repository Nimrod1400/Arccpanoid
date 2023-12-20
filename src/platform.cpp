#include "platform.hpp"
#include "settings.hpp"

namespace Arcpp {
  Platform::Platform() {
    m_settings = Settings::instance();
    speed = m_settings->screen_width / 2.5f;

    hitbox.width = m_settings->screen_width / 9.0f;
    hitbox.height = m_settings->screen_height / 25.f;

    hitbox.x = (m_settings->screen_width - hitbox.width) / 2.0f;
    hitbox.y = (m_settings->screen_height - hitbox.height) / 1.075f;
  }

  void Platform::move_right(float dt) {
    velocity = speed;
    if (hitbox.x + hitbox.width < m_settings->screen_width)
      hitbox.x += velocity * dt;
  }

  void Platform::move_left(float dt) {
    velocity = -speed;
    if (hitbox.x > 0)
      hitbox.x += velocity * dt;
  }

  void Platform::stop() {
    velocity = 0.0f;
  }
}
