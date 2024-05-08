#include "../src/main.cpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

 TEST_CASE("Good case", "[getAuthor]"){
     REQUIRE(getAuthor()=="tampio.ilya");
 }

 TEST_CASE("Fail case", "[getAuthor]"){
     REQUIRE_FALSE(getAuthor() == "sergey.sviridenko");
 }

