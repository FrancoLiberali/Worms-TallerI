/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_WormMovingTest_init = false;
#include "worm_moving_tests.h"

static WormMovingTest suite_WormMovingTest;

static CxxTest::List Tests_WormMovingTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_WormMovingTest( "worm_moving_tests.h", 12, "WormMovingTest", suite_WormMovingTest, Tests_WormMovingTest );

static class TestDescription_suite_WormMovingTest_test_not_inactive_after_move : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormMovingTest_test_not_inactive_after_move() : CxxTest::RealTestDescription( Tests_WormMovingTest, suiteDescription_WormMovingTest, 24, "test_not_inactive_after_move" ) {}
 void runTest() { suite_WormMovingTest.test_not_inactive_after_move(); }
} testDescription_suite_WormMovingTest_test_not_inactive_after_move;

static class TestDescription_suite_WormMovingTest_test_first_move_to_the_opposite_side_inactive : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormMovingTest_test_first_move_to_the_opposite_side_inactive() : CxxTest::RealTestDescription( Tests_WormMovingTest, suiteDescription_WormMovingTest, 43, "test_first_move_to_the_opposite_side_inactive" ) {}
 void runTest() { suite_WormMovingTest.test_first_move_to_the_opposite_side_inactive(); }
} testDescription_suite_WormMovingTest_test_first_move_to_the_opposite_side_inactive;

static class TestDescription_suite_WormMovingTest_test_one_step : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormMovingTest_test_one_step() : CxxTest::RealTestDescription( Tests_WormMovingTest, suiteDescription_WormMovingTest, 65, "test_one_step" ) {}
 void runTest() { suite_WormMovingTest.test_one_step(); }
} testDescription_suite_WormMovingTest_test_one_step;

static class TestDescription_suite_WormMovingTest_test_velocity : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormMovingTest_test_velocity() : CxxTest::RealTestDescription( Tests_WormMovingTest, suiteDescription_WormMovingTest, 99, "test_velocity" ) {}
 void runTest() { suite_WormMovingTest.test_velocity(); }
} testDescription_suite_WormMovingTest_test_velocity;

static class TestDescription_suite_WormMovingTest_test_until_45_degress_not_fall : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormMovingTest_test_until_45_degress_not_fall() : CxxTest::RealTestDescription( Tests_WormMovingTest, suiteDescription_WormMovingTest, 134, "test_until_45_degress_not_fall" ) {}
 void runTest() { suite_WormMovingTest.test_until_45_degress_not_fall(); }
} testDescription_suite_WormMovingTest_test_until_45_degress_not_fall;

static class TestDescription_suite_WormMovingTest_test_more_than_45_degress_fall : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormMovingTest_test_more_than_45_degress_fall() : CxxTest::RealTestDescription( Tests_WormMovingTest, suiteDescription_WormMovingTest, 175, "test_more_than_45_degress_fall" ) {}
 void runTest() { suite_WormMovingTest.test_more_than_45_degress_fall(); }
} testDescription_suite_WormMovingTest_test_more_than_45_degress_fall;

static class TestDescription_suite_WormMovingTest_test_one_step_inclined : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormMovingTest_test_one_step_inclined() : CxxTest::RealTestDescription( Tests_WormMovingTest, suiteDescription_WormMovingTest, 218, "test_one_step_inclined" ) {}
 void runTest() { suite_WormMovingTest.test_one_step_inclined(); }
} testDescription_suite_WormMovingTest_test_one_step_inclined;

static class TestDescription_suite_WormMovingTest_test_one_step_declined : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormMovingTest_test_one_step_declined() : CxxTest::RealTestDescription( Tests_WormMovingTest, suiteDescription_WormMovingTest, 253, "test_one_step_declined" ) {}
 void runTest() { suite_WormMovingTest.test_one_step_declined(); }
} testDescription_suite_WormMovingTest_test_one_step_declined;

static class TestDescription_suite_WormMovingTest_test_fall_when_finish_beam : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormMovingTest_test_fall_when_finish_beam() : CxxTest::RealTestDescription( Tests_WormMovingTest, suiteDescription_WormMovingTest, 288, "test_fall_when_finish_beam" ) {}
 void runTest() { suite_WormMovingTest.test_fall_when_finish_beam(); }
} testDescription_suite_WormMovingTest_test_fall_when_finish_beam;

static class TestDescription_suite_WormMovingTest_test_take_ground_angle : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormMovingTest_test_take_ground_angle() : CxxTest::RealTestDescription( Tests_WormMovingTest, suiteDescription_WormMovingTest, 324, "test_take_ground_angle" ) {}
 void runTest() { suite_WormMovingTest.test_take_ground_angle(); }
} testDescription_suite_WormMovingTest_test_take_ground_angle;

static class TestDescription_suite_WormMovingTest_test_fall_and_take_ground_angle_when_land : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormMovingTest_test_fall_and_take_ground_angle_when_land() : CxxTest::RealTestDescription( Tests_WormMovingTest, suiteDescription_WormMovingTest, 349, "test_fall_and_take_ground_angle_when_land" ) {}
 void runTest() { suite_WormMovingTest.test_fall_and_take_ground_angle_when_land(); }
} testDescription_suite_WormMovingTest_test_fall_and_take_ground_angle_when_land;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
