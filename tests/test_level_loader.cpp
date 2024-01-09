#include <boost/test/tools/old/interface.hpp>
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "../src/level_loader.hpp"
#include <yaml-cpp/node/node.h>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>

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

BOOST_AUTO_TEST_SUITE_END()
