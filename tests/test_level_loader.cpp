#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "../src/level_loader.hpp"
#include <yaml-cpp/node/node.h>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/tools/old/interface.hpp>
#include <utility>

BOOST_AUTO_TEST_SUITE(TestLevelLoaderFacade)

BOOST_AUTO_TEST_CASE(LoadSingleBrickLevel) {
  std::string level_name = "single_brick";

  int bricks_amount = 1;
  int player_health = 1;

  int bricks_width = 1;
  int bricks_height = 1;
  
  YAML::Node level_node = YAML::LoadFile("./tests/single_brick_level.yaml");
  
  Arcpp::LevelLoader ll;
  Arcpp::Level level = ll.load_level(level_node, level_name); 
 
  BOOST_REQUIRE_EQUAL(level.level_name, level_name);
  BOOST_REQUIRE_EQUAL(level.max_player_health, player_health);
  BOOST_REQUIRE_EQUAL(level.bricks_amounts.x, bricks_width);
  BOOST_REQUIRE_EQUAL(level.bricks_amounts.y, bricks_height);
  BOOST_REQUIRE_EQUAL(level.bricks.size(), bricks_amount);
  BOOST_REQUIRE_EQUAL(level.bricks[0].health, 1);
}

BOOST_AUTO_TEST_CASE(LoadFourBricksLevel) {
  std::string level_name = "four_bricks";

  int bricks_amount = 4;
  int player_health = 5;

  int bricks_width = 4;
  int bricks_height = 1;

  std::vector<int> bricks_healths = { 1, 3, 3, 1, };
  
  YAML::Node level_node = YAML::LoadFile("./tests/four_bricks_level.yaml");
  
  Arcpp::LevelLoader ll;
  Arcpp::Level level = ll.load_level(level_node, level_name); 
 
  BOOST_REQUIRE_EQUAL(level.level_name, level_name);
  BOOST_REQUIRE_EQUAL(level.max_player_health, player_health);
  BOOST_REQUIRE_EQUAL(level.bricks_amounts.x, bricks_width);
  BOOST_REQUIRE_EQUAL(level.bricks_amounts.y, bricks_height);
  BOOST_REQUIRE_EQUAL(level.bricks.size(), bricks_amount);
  for (int i = 0; i < bricks_healths.size(); ++i)
    BOOST_REQUIRE_EQUAL(level.bricks[i].health, bricks_healths[i]);
}

BOOST_AUTO_TEST_CASE(SpacerCalculation) {
  std::string level_name = "single_brick";

  Vector2 screen_params = { 1920, 1080 };
  float expected = std::sqrt(std::pow(screen_params.x, 2.0f) + std::pow(screen_params.y, 2.0f)) / 200.0f;

  YAML::Node level_node = YAML::LoadFile("./tests/single_brick_level.yaml");

  Arcpp::LevelLoader ll;
  ll.load_level(level_node, level_name);

  BOOST_REQUIRE_EQUAL(ll.calculate_spacer(screen_params), expected);
}

BOOST_AUTO_TEST_CASE(SingleBrickAdjustment) {
  Vector2 brick_pos = { 0, 0 };
  
  std::string level_name = "single_brick";
  
  YAML::Node level_node = YAML::LoadFile("./tests/single_brick_level.yaml");
  
  Arcpp::LevelLoader ll;
  Arcpp::Level level = ll.load_level(level_node, level_name); 

  Vector2 expected_coordinates = 
  {
    (brick_pos.x + 1) * ll.spacer + brick_pos.x * ll.brick_size.x,
    (brick_pos.y + 1) * ll.spacer + brick_pos.y * ll.brick_size.y,  
  }; 
 
  BOOST_REQUIRE_EQUAL(level.bricks[0].hitbox.x, expected_coordinates.x);
  BOOST_REQUIRE_EQUAL(level.bricks[0].hitbox.y, expected_coordinates.y);
}

BOOST_AUTO_TEST_CASE(FourBricksAdjustment) {
  std::vector<Vector2> bricks_pos = 
  { 
    { 0, 0 },
    { 1, 0 },
    { 2, 0 },
    { 3, 0 }, 
  };
  
  std::string level_name = "four_bricks";
  
  YAML::Node level_node = YAML::LoadFile("./tests/four_bricks_level.yaml");
  
  Arcpp::LevelLoader ll;
  Arcpp::Level level = ll.load_level(level_node, level_name); 

  std::vector<Vector2> expected_coords;

  for (int i = 0; i < bricks_pos.size(); ++i) 
    expected_coords.push_back(
    std::move<Vector2>({
      (bricks_pos[i].x + 1) * ll.spacer + bricks_pos[i].x * ll.brick_size.x,
      (bricks_pos[i].y + 1) * ll.spacer + bricks_pos[i].y * ll.brick_size.y,  
    }));
      
  for (int i = 0; i < bricks_pos.size(); ++i) {
    BOOST_REQUIRE_EQUAL(level.bricks[i].hitbox.x, expected_coords[i].x);
    BOOST_REQUIRE_EQUAL(level.bricks[i].hitbox.y, expected_coords[i].y);
  }
}

BOOST_AUTO_TEST_SUITE_END()
