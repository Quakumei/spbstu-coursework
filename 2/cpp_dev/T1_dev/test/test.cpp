#define CATCH_CONFIG_MAIN
#include "../src/shape.hpp"
#include "../src/shapecollection.hpp"
#include "base-types.hpp"
#include "catch.hpp"
#include "rectangle.hpp"

using namespace tampio;

TEST_CASE("Basic assert", "[sanity]")
{
  REQUIRE(1 == 1);

  ShapeCollection< std::shared_ptr< Shape > > sc;
  std::shared_ptr< Shape > fig = nullptr;
}
