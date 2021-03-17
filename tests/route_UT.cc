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
class RouteTests: public ::testing::Test {
protected:
  Stop *stop1, *stop2, *stop3, *stop4;
  Stop* stopArray1[2];
  Stop* stopArray2[2];
  double distances1[1] = {5.5};
  double distances2[1] = {2.2};
  Route* route1, *route2;

  virtual void SetUp() {
    stop1 = new Stop(0, 12.7, 25.75);
    stop2 = new Stop(1, 0.0, 0.0);
    stop3 = new Stop(2, 25.6, 14.7);
    stop4 = new Stop(3, 18.9, 14.5);
    stopArray1[0] = stop1;
    stopArray1[1] = stop2;
    stopArray2[0] = stop3;
    stopArray2[1] = stop4;
    route1 = new Route("route1", stopArray1, distances1, 2, nullptr);
    route2 = new Route("route2", stopArray2, distances2, 2, nullptr);    
  }

  virtual void TearDown() {
    delete stop1; stop1 = NULL;
    delete stop2; stop2 = NULL;
    delete stop3; stop3 = NULL;
    delete stop4; stop4 = NULL;
    delete route1; route1 = NULL;
    delete route2; route2 = NULL;
  }
};
  
/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(RouteTests, GetNameTests){
  EXPECT_EQ(route1->GetName(), "route1");
  EXPECT_EQ(route2->GetName(), "route2");  
}

TEST_F(RouteTests, GetStopsTests){
  EXPECT_EQ(route1->GetStops(), list<Stop*>({stop1, stop2}));
  EXPECT_EQ(route2->GetStops(), list<Stop*>({stop3, stop4}));  
}

TEST_F(RouteTests, GetTotalRouteDistanceTests){
  EXPECT_EQ(route1->GetTotalRouteDistance(), 5.5);
  EXPECT_EQ(route2->GetTotalRouteDistance(), 2.2);  
}

TEST_F(RouteTests, IsAtEndTests){
  EXPECT_EQ(route1->IsAtEnd(), false);
  route1->ToNextStop();
  route1->ToNextStop();
  EXPECT_EQ(route1->IsAtEnd(), true);
}

TEST_F(RouteTests, GetNextStopDistanceTests){
  route1->ToNextStop();
  EXPECT_EQ(route1->GetNextStopDistance(), 5.5);
  route2->ToNextStop();
  EXPECT_EQ(route2->GetNextStopDistance(), 2.2);  
}

TEST_F(RouteTests, GetDestinationStopTests){
  EXPECT_EQ(route1->GetDestinationStop(), stop1);
  route1->ToNextStop();
  EXPECT_EQ(route1->GetDestinationStop(), stop2);
  
  EXPECT_EQ(route2->GetDestinationStop(), stop3);
  route2->ToNextStop();
  EXPECT_EQ(route2->GetDestinationStop(), stop4);
						     
}


