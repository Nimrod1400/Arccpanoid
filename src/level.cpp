#include "level.hpp"

namespace Arcpp {
  void Level::strike_brick(Ball &ball) {
    for (auto ibr = bricks.begin(); ibr != bricks.end(); ++ibr) {
      Brick &brick = *ibr;

      if (!CheckCollisionCircleRec(ball.center, ball.radius, brick.hitbox))
        continue;

      ball.brick_bounce(brick);
        brick.get_damage(ball.damage);

      if (brick.health <= 0)
        bricks.erase(ibr);
    }
  }
}
