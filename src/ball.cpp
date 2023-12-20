#include <cmath>
#include <random>
#include "ball.hpp"

namespace Arcpp {
  Ball::Ball(const Platform &platform) {
    m_settings = Settings::instance();
    is_active = false;

    m_velocity_scalar = m_settings->screen_width / 1.6f;
    m_spacer = m_settings->screen_width / 1280.0f;

    damage = 1;

    color = { 0, 80, 0, 255 };

    follow_platform(platform);
    m_randomise_velocity();
  }

  void Ball::update_position(float dt) {
    center.x += velocity.x * dt;
    center.y -= velocity.y * dt;
  }

  void Ball::follow_platform(const Platform &platform) {
    radius = m_settings->screen_height / 40.0f;
    center = { platform.hitbox.x + platform.hitbox.width / 2.0f, platform.hitbox.y - radius };
  }

  void Ball::reset() {
    is_active = false;

    damage = 1;

    color = { 0, 80, 0, 255 };

    m_randomise_velocity();
  }

  bool Ball::is_lost() {
    return center.y - 2.0f * radius > m_settings->screen_height;
  }

  void Ball::wall_bounce() {
    bool hit_upper = center.y - radius <= 0;
    bool hit_right = (center.x + radius) >= (m_settings->screen_width);
    bool hit_left = (center.x - radius) <= 0;

    if (hit_upper) {
      center.y = m_spacer * 2.0f + radius;
      velocity.y *= -1.0f;
    }
    if (hit_right) {
      center.x = -m_spacer * 2.0f - radius + m_settings->screen_width;
      velocity.x *= -1.0f;
    }
    if (hit_left) {
      center.x = m_spacer * 2.0f + radius;
      velocity.x *= -1.0f;
    }
  }

  void Ball::platform_bounce(const Platform &platform) {
    if (m_rectangle_bounce(platform.hitbox)) {
      float dx = platform.velocity / 5.0f;
      velocity.x += dx;
    }

  }

  void Ball::brick_bounce(const Brick &brick) {
    m_rectangle_bounce(brick.hitbox);
  }

  bool Ball::m_rectangle_bounce(const Rectangle &rec) {
    if (!(CheckCollisionCircleRec(center, radius, rec))) return false;

    if (center.x + radius >= rec.x &&
        center.x - radius <= rec.x + rec.width &&
        center.y < rec.y) { // Hit from the above.
      center.y = -m_spacer - radius + rec.y;
      velocity.y *= -1;
    }
    else if (center.x + radius >= rec.x &&
             center.x - radius <= rec.x + rec.width &&
             center.y > rec.y + rec.height) { // Hit from the below.
      center.y = m_spacer + radius + rec.y + rec.height;
      velocity.y *= -1;
    }

    if (center.y + radius >= rec.y &&
        center.y - radius <= rec.y + rec.height &&
        center.x > rec.x + rec.width) { // Hit from the right.
      center.x = m_spacer + radius + rec.x + rec.width;
      velocity.x *= -1;
    }
    else if (center.y + radius >= rec.y &&
             center.y - radius <= rec.y + rec.height &&
             center.x < rec.x) { // Hit from the left.
      center.x = -m_spacer - radius + rec.x;
      velocity.x *= -1;
    }
    return true;
  }

  void Ball::m_randomise_velocity() {
    constexpr float pi = M_PI;

    std::random_device rd;
    std::mt19937 gen { rd() };
    std::uniform_real_distribution<float> distrib { 2.0f * pi / 3.0f, pi / 3.0f};
    float angle = distrib(gen);

    velocity = { cosf(angle) * m_velocity_scalar, sinf(1.0) * m_velocity_scalar };
  }
}
