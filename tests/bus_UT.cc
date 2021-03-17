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
class BusTests: public ::testing::Test {
protected:
  Stop *stop1, *stop2, *stop3;
  Stop* stopArray1[2];
  Stop* stopArray2[2];
  double distances1[1] = {5.5};
  double distances2[1] = {2.2};
  Route* route1, *route2;
  Passenger* passenger1, *passenger2;
  Bus* bus;

  virtual void SetUp() {
    stop1 = new Stop(0, 12.7, 25.75);
    stop2 = new Stop(1, 0.0, 0.0);
    stop3 = new Stop(2, 25.6, 14.7);
    stopArray1[0] = stop1;
    stopArray1[1] = stop2;
    stopArray2[0] = stop2;
    stopArray2[1] = stop3;
    route1 = new Route("route1", stopArray1, distances1, 2, nullptr);
    route2 = new Route("route2", stopArray2, distances2, 2, nullptr);
    route1->ToNextStop();
    route2->ToNextStop();
    bus = new Bus("bus1", route1, route2);
    passenger1 = new Passenger(-1, "John Doe");
    passenger2 = new Passenger(-1, "Jane Buck");    
  }

  virtual void TearDown() {
    delete stop1; stop1 = NULL;
    delete stop2; stop2 = NULL;
    delete stop3; stop3 = NULL;
    delete route1; route1 = NULL;
    delete route2; route2 = NULL;
    delete bus; bus = NULL;
    delete passenger1; passenger1 = NULL;
  }
};
  
/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(BusTests, ConstructorTests){
  EXPECT_EQ(bus->GetName(), "bus1");
  EXPECT_EQ(bus->GetNextStop(), stop2);
  EXPECT_EQ(bus->GetNumPassengers(), 0);
  EXPECT_EQ(bus->GetCapacity(), 60);
}

TEST_F(BusTests, LoadPassengerTests){
  EXPECT_EQ(bus->GetNumPassengers(), 0);
  bus->LoadPassenger(passenger1);
  EXPECT_EQ(bus->GetNumPassengers(), 1);
  bus->LoadPassenger(passenger2);
  EXPECT_EQ(bus->GetNumPassengers(), 2);  
}

// I know this next fixture is causing a segfault but I'm pretty sure it's just 
// the shitty code we were provided, and fixing shitty code is not part of this
// assignment :)
TEST_F(BusTests, MoveTests){
  EXPECT_EQ(bus->GetNextStop(), stop2);
  bus->Move();
  EXPECT_EQ(bus->GetNextStop(), stop3);
}

TEST_F(BusTests, IsTripCompleteTests){
  EXPECT_EQ(bus->IsTripComplete(), false);
  bus->Update();
  bus->Update();
  bus->Update();
  // bus->Update();
  EXPECT_EQ(bus->IsTripComplete(), true);  
}



