
#ifndef USER_MANAGEMENT_FULLTEST_HPP
#define USER_MANAGEMENT_FULLTEST_HPP

#include "oatpp-test/UnitTest.hpp"

class FullTest : public oatpp::test::UnitTest {
public:
  FullTest() : oatpp::test::UnitTest("[MyTest]")
  {}

  void onRun() override;

};


#endif //USER_MANAGEMENT_FULLTEST_HPP
