#include "brick.hpp"

namespace Arcpp {
  Brick::Brick(int health, BonusType bonus_type, Rectangle hitbox) :
    health { health },
    bonus_type { bonus_type },
    hitbox { hitbox } {
      update_color();
  }

  void Brick::get_damage(int damage) {
    health -= damage;
    update_color();
  }

  void Brick::update_color() {
    int max_health = 5;
    unsigned char green = 255 - (255.0f / max_health) * health;
    color = { 255, green, 0, 255 };
  }
}
