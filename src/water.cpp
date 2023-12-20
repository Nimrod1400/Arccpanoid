#include "water.hpp"
#include "settings.hpp"

namespace Arcpp {
  Water::Water(const Platform &platform) {
    Settings *s = Settings::instance();

    color = { 64, 64, 255, 127 };

    view.width = s->screen_width;
    view.x = 0.0f;
    view.height = s->screen_height - platform.hitbox.height - platform.hitbox.height;
    view.y = platform.hitbox.y + platform.hitbox.height;
  }
}
