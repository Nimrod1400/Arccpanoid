#include <iostream>
#include <string>
#include "gameview.hpp"
#include "gamecontroller.hpp"
#include "settings.hpp"

int main() {
  std::string game_title = "Arcpp";

  // Init resources {
  std::string settings_file_path = "gamedata/settings.yaml";
  std::string levels_file_path = "gamedata/levels.yaml";

  Arcpp::Settings *s = Arcpp::Settings::instance();
  s->load_settings(settings_file_path);

  std::string current_level = "level2";
  Arcpp::GameModel *gm  = new Arcpp::GameModel { levels_file_path, current_level };
  Arcpp::GameController gc { gm };
  Arcpp::GameView gv { gm };
  // }

  // Init screen parameters {
  InitWindow(s->screen_width,
      s->screen_height,
      game_title.c_str());
  SetTargetFPS(s->target_fps);
  // }

  // Main loop {
  while (!WindowShouldClose()) {
    DrawFPS(0, 0);
    gc.handle_input();
    gm->update_state();
    gv.draw();
  }
  // }

  // Cleanup {
  delete gm;
  delete s;
  // }

  CloseWindow();
  return 0;
}
