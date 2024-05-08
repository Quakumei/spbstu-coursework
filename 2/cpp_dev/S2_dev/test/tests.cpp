
#include <map>
#include "../src/Dictionary.hpp"
#include "../src/ForwardList.hpp"
#include <forward_list>


#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("1==1", "[Sanity]")
{
  REQUIRE(1 == 1);
}

TEST_CASE("ForwardList works as <forward_list>", "[Unit]")
{
  REQUIRE(1 == 1);

  tampio::ForwardList< int > tamp_fl;
  std::forward_list< int > stl_fl;

  // Basic operations
  for (int i = 0; i < 10; i++)
  {
    tamp_fl.pushFront(i);
    stl_fl.push_front(i);
  }
  for (int i = 0; i < 10; i++)
  {
    REQUIRE(tamp_fl.front() == stl_fl.front());
    stl_fl.pop_front();
    tamp_fl.deleteFront();
  }

  for (int i = 0; i < 100; i++)
  {
    tamp_fl.pushFront(i);
    stl_fl.push_front(i);
  }

  for (int i = 0; i < 100; i++)
  {
    REQUIRE(tamp_fl.front() == stl_fl.front());
    stl_fl.pop_front();
    tamp_fl.deleteFront();
  }

  // "Calling front on an empty container is undefined"
  // REQUIRE_THROWS(stl_fl.front());
  // REQUIRE_THROWS(tamp_fl.top());
  REQUIRE(stl_fl.empty());
  REQUIRE(tamp_fl.empty());
}

TEST_CASE("Custom iterator doing good!", "[Unit]")
{
  tampio::ForwardList< int > tamp_fl;
  std::forward_list< int > stl_fl;
  // Iteration
  for (int i = 0; i < 5; i++)
  {
    tamp_fl.pushFront(i);
    stl_fl.push_front(i);
  }
  std::forward_list< int >::iterator it_stl = stl_fl.begin();
  tampio::ForwardList< int >::Iterator it_tamp = tamp_fl.begin();
  for (int i = 0; i < 5; i++)
  {
    REQUIRE(*(it_stl++) == *(it_tamp++));
  }

  std::forward_list< int >::iterator it_stl_bb = stl_fl.before_begin();
  tampio::ForwardList< int >::Iterator it_tamp_bb = tamp_fl.beforeBegin();
  for (int i = 0; i < 5; i++)
  {
    REQUIRE(*(++it_stl_bb) == *(++it_tamp_bb));
  }

  // insertAfter
  // first
  const int HOLY = 42;
  tamp_fl.insertAfter(tamp_fl.beforeBegin(), HOLY);
  stl_fl.insert_after(stl_fl.before_begin(), HOLY);
  it_stl = stl_fl.begin();
  it_tamp = tamp_fl.begin();
  REQUIRE(*(it_stl) == *(it_tamp));
  REQUIRE(HOLY == *(it_tamp));

  //   // last
  const int HOLY_2 = 43;
  // std::cout <<  "insert ready 0\n";
  tamp_fl.insertAfter(tamp_fl.beforeEnd(), HOLY_2);
  REQUIRE(HOLY_2 == *(tamp_fl.beforeEnd()));
  // std::cout <<  "insert done 1\n";

  // it_stl_bb = stl_fl.before_begin();
  // it_tamp_bb = tamp_fl.beforeBegin();
  for (tampio::ForwardList< int >::Iterator i = tamp_fl.begin(); i != tamp_fl.end(); i++)
  {
    // std::cout <<  '\n' << *i;
  }
  // std::cout <<  '\n';
  // std::cout <<  "delete2, commesnce\n";
  tamp_fl.deleteNode(tamp_fl.begin());
  // std::cout <<  "delete2, successful\n";
  for (tampio::ForwardList< int >::Iterator i = tamp_fl.begin(); i != tamp_fl.end(); i++)
  {
    // std::cout <<  ' ' << *i;
  }
  REQUIRE(4 == *(tamp_fl.begin()));
  for (tampio::ForwardList< int >::Iterator i = tamp_fl.begin(); i != tamp_fl.end(); i++)
  {
    // std::cout <<  ' ' << *i;
  }
  // std::cout <<  '\n';

  // std::cout <<  "delete, commesnce\n";
  tamp_fl.deleteNode(tamp_fl.beforeEnd());
  // std::cout <<  "delete, successful\n";
  for (tampio::ForwardList< int >::Iterator i = tamp_fl.begin(); i != tamp_fl.end(); i++)
  {
    // std::cout <<  '\n' << *i;
  }
  // std::cout <<  '\n';

  REQUIRE(0 == *(tamp_fl.beforeEnd()));

  // std::cout <<  "delete3, commesnce\n";
  tamp_fl.deleteNode(++(++tamp_fl.begin()));
  // std::cout <<  "delete3, successful\n";
  for (tampio::ForwardList< int >::Iterator i = tamp_fl.begin(); i != tamp_fl.end(); i++)
  {
    // std::cout <<  '\n' << *i;
  }
  // std::cout <<  '\n';

  REQUIRE(1 == *(++(++tamp_fl.begin())));

  // stl_fl.insert_after(stl_fl.end(), HOLY_2);
  // // std::cout <<  "insert done 2";
  // it_stl = stl_fl.end();
  // it_tamp = tamp_fl.end();

  // REQUIRE(*(it_stl) == *(it_tamp));
}

TEST_CASE("Dictionary works as std::map", "[InSanity]")
{
  tampio::Dictionary< std::string, std::string, std::less< std::string > > tamp_dict;
  std::map< std::string, std::string, std::less< std::string > > stl_dict;

  // TODO:  Replace with operator []
  tamp_dict.push("cock", "suck");
  tamp_dict.push("cock", "suck1");
  tamp_dict.push("cock2", "suck2");
  tamp_dict.push("cock3", "suck3");

  stl_dict["cock"] = "suck";
  stl_dict["cock"] = "suck1";
  stl_dict["cock2"] = "suck2";
  stl_dict["cock3"] = "suck3";
  REQUIRE(stl_dict["cock2"] == tamp_dict.get("cock2"));
  REQUIRE(stl_dict["cock3"] == tamp_dict.get("cock3"));
  REQUIRE(stl_dict["cock"] == tamp_dict.get("cock"));

  stl_dict.erase("cock");
  tamp_dict.drop("cock");
  REQUIRE_FALSE(tamp_dict.doesKeyExist("cock"));
  REQUIRE_FALSE(stl_dict.find("cock") != stl_dict.end());
}
