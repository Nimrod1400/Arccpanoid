#include <fstream>
#include "settings.hpp"

namespace Arcpp {
  Settings *Settings::instance() {
    static Settings *instance = new Settings;
    return instance;
  }

  void Settings::load_settings(const std::string &file_path) {
    YAML::Node settings = YAML::LoadFile(file_path);

    if (settings["screen_width"])
      screen_width = settings["screen_width"].as<int>();

    if (settings["screen_height"])
      screen_height = settings["screen_height"].as<int>();

    if (settings["target_fps"])
      target_fps = settings["target_fps"].as<int>();
  }

  void Settings::set_screen_parameters(const std::string &file_path, int width, int height) {
    YAML::Node settings = YAML::LoadFile(file_path);

    settings["screen_width"] = width;
    settings["screen_height"] = height;

    std::ofstream fout { file_path };
    fout << settings;

    fout.close();
  }

  void Settings::set_target_fps_parameter(const std::string &file_path, int target_fps) {
    YAML::Node settings = YAML::LoadFile(file_path);

    settings["target_fps"] = target_fps;

    std::ofstream fout { file_path };
    fout << settings;

    fout.close();
  }
}
