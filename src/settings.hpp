#pragma once

#include <string>
#include <yaml-cpp/yaml.h>

namespace Arcpp {
  class Settings {
  private:
    Settings() { };
    Settings(const Settings &rhs) = delete;
    Settings &operator=(const Settings &rhs) = delete;

  public:
    static Settings *instance();

    void load_settings(const std::string &file_path);

    static void set_screen_parameters(const std::string &file_path, int width, int height);
    static void set_target_fps_parameter(const std::string &file_path, int target_fps);

    int screen_width;
    int screen_height;
    int target_fps;
  };
}
