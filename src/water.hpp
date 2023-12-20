#pragma once

#include <raylib.h>
#include "platform.hpp"

namespace Arcpp {
  class Water {
  public:
    Water(const Platform &platform);
    Rectangle view;
    Color color;
  };
}
