#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <list>
#include <string>

#include "../src/passenger_generator.h"
#include "../src/passenger.h"
#include "../src/stop.h"
#include "../src/bus.h"
#include "../src/route.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class StopTests: public ::testing::Test {
protected:
  Stop *stop1, *stop2, *stop3, *stop4;
  Stop* stopArray1[2] = {stop1, stop2};
  Stop* stopArray2[2] = {stop3, stop4};
  double distances1[1] = {5.5};
  double distances2[1] = {2.2};
  Route* route1, *route2;
  Passenger* passenger1, *passenger2;
  Bus* bus;

  virtual void SetUp() {
    stop1 = new Stop(0, 12.7, 25.75);
    stop2 = new Stop(1, 0.0, 0.0);
    stop3 = new Stop(2, 25.6, 14.7);
    route1 = new Route("route1", stopArray1, distances1, 2, nullptr);
    route2 = new Route("route2", stopArray2, distances2, 2, nullptr);
    bus = new Bus("bus1", route1, route2);
    passenger1 = new Passenger(-1, "John Doe");
    passenger2 = new Passenger(-1, "Jane Buck");    
  }

  virtual void TearDown() {
    delete stop1; stop1 = NULL;
    delete stop2; stop2 = NULL;
    delete stop3; stop3 = NULL;
    delete stop4; stop4 = NULL;
    delete route1; route1 = NULL;
    delete route2; route2 = NULL;
    delete bus; bus = NULL;
    delete passenger1; passenger1 = NULL;
  }

};
  
/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(StopTests, AddPassengersTests){
  EXPECT_EQ(stop1->GetNumPassengersPresent(), 0);
  stop1->AddPassengers(passenger1);
  EXPECT_EQ(stop1->GetNumPassengersPresent(), 1);
  stop1->AddPassengers(passenger2);
  EXPECT_EQ(stop1->GetNumPassengersPresent(), 2);
}

TEST_F(StopTests, LoadPassengersTests){
  stop1->AddPassengers(passenger1);
  stop1->LoadPassengers(bus);
  EXPECT_EQ(stop1->GetNumPassengersPresent(), 0);
  stop1->AddPassengers(passenger2);
  stop1->LoadPassengers(bus);
  EXPECT_EQ(stop1->GetNumPassengersPresent(), 0);
}

TEST_F(StopTests, GetIdTests){
  EXPECT_EQ(stop1->GetId(), 0);
  EXPECT_EQ(stop2->GetId(), 1);
}

TEST_F(StopTests, LatLongTests){
  EXPECT_EQ(stop1->GetLatitude(), 25.75);
  EXPECT_EQ(stop1->GetLongitude(), 12.7);
  EXPECT_EQ(stop2->GetLatitude(), 0.0);
  EXPECT_EQ(stop2->GetLongitude(), 0.0);
}

TEST_F(StopTests, UpdateTests){
  stop1->AddPassengers(passenger1);
  stop1->AddPassengers(passenger2);
  EXPECT_EQ(passenger1->GetTotalWait(), 0);
  EXPECT_EQ(passenger2->GetTotalWait(), 0);
  stop1->Update();
  EXPECT_EQ(passenger1->GetTotalWait(), 1);
  EXPECT_EQ(passenger1->GetTotalWait(), 1);
  stop1->Update();
  EXPECT_EQ(passenger1->GetTotalWait(), 2);
  EXPECT_EQ(passenger1->GetTotalWait(), 2);  
}

TEST_F(StopTests, ReportTests){
  stop1->AddPassengers(passenger1);
  stop1->AddPassengers(passenger2);
  testing::internal::CaptureStdout();
  stop1->Report(cout);
  string report = testing::internal::GetCapturedStdout();
  int a = report.find("ID: 0");
  int b = report.find("Passengers waiting: 2");
  EXPECT_GE(a, 0);
  EXPECT_GE(b, 0);  
}
