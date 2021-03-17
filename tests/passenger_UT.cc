/*
<<<<<<< HEAD
 * This file is used by the CS3081W auto-grading system.
 *
 * Please note, the assessment tests for grading, will use the same include
 * files, class names, and function names for accessing students' code that you
 * find in this file.  So students, if you write your code so that it passes
 * these feedback tests, you can be assured that the auto-grader will at least
 * be able to properly link with your code.
=======
 * Students: Use this file as a guide to writing your own unit tests.
 * See the project instructions for more information on which classes
 * and methods must be tested.
>>>>>>> support-code
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <list>
#include <string>

#include "../src/passenger_loader.h"
#include "../src/passenger_unloader.h"
#include "../src/passenger.h"
#include "../src/stop.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class PassengerTests : public ::testing::Test {
protected:
  PassengerLoader* pass_loader;
  PassengerUnloader* pass_unloader;
  Passenger *passenger, *passenger1, *passenger2;

  virtual void SetUp() {
    pass_loader = new PassengerLoader();
    pass_unloader = new PassengerUnloader();
    passenger1 = new Passenger(0, "John Doe");
    passenger2 = new Passenger(1, "Jane Buck");
  }

  virtual void TearDown() {
    delete pass_loader;
    delete pass_unloader;
    delete passenger;
    delete passenger1;
    delete passenger2;
    passenger = NULL;
    passenger1 = NULL;
    passenger2 = NULL;
    pass_loader = NULL;
    pass_unloader = NULL;
  }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(PassengerTests, Constructor) {
  passenger = new Passenger();
  EXPECT_EQ(passenger->IsOnBus(), false);
  passenger->GetOnBus();
  EXPECT_EQ(passenger->IsOnBus(), true);
};

TEST_F(PassengerTests, NameTests){
  string expected_output_1 = "Name: John Doe";
  string expected_output_2 = "Name: Jane Buck";
  testing::internal::CaptureStdout();
  passenger1->Report(cout);
  string output1 = testing::internal::GetCapturedStdout();
  testing::internal::CaptureStdout();
  passenger2->Report(cout);
  string output2 = testing::internal::GetCapturedStdout();
  int p1 = output1.find(expected_output_1);
  int p2 = output2.find(expected_output_2);
  EXPECT_GE(p1, 0);
  EXPECT_GE(p2, 0);
}

TEST_F(PassengerTests, GetDestinationTests){
  EXPECT_EQ(passenger1->GetDestination(), 0);
  EXPECT_EQ(passenger2->GetDestination(), 1);  
}

TEST_F(PassengerTests, GetTotalWaitTests){
  EXPECT_EQ(passenger1->GetTotalWait(), 0);
  EXPECT_EQ(passenger2->GetTotalWait(), 0);  
} 

TEST_F(PassengerTests, GetOnBusTests){
  EXPECT_EQ(passenger1->IsOnBus(), false);
  passenger1->GetOnBus();
  EXPECT_EQ(passenger1->IsOnBus(), true);
}

TEST_F(PassengerTests, UpdateTests){
  EXPECT_EQ(passenger1->GetTotalWait(), 0);
  passenger1->Update();
  EXPECT_EQ(passenger1->GetTotalWait(), 1);
  EXPECT_EQ(passenger2->GetTotalWait(), 0);
  passenger2->Update();
  EXPECT_EQ(passenger2->GetTotalWait(), 1);
}

