/**
 * @file web/main.cpp
 * 
 * @copyright 2020 Parker Patterson
 *
 * @brief Main driver for web stuff
 *
 * This main routine uses the ConfigManager class to read config.txt.
 * Next, it instantiates a new VisualizationSimulator object using a randomly 
 * chosen size of BusFactory. Finally, it launches a web server that the user
 * can interact with in their browser.
 */

#include <iostream>
#include <vector>
#include <random>
#include "../../src/config_manager.h"
#include "./visualization_simulator.h"

#include "./my_web_server_session_state.h"
#include "./my_web_server_command.h"
#include "./my_web_server_session.h"
#include "./my_web_server.h"



//#define _USE_MATH_DEFINES
//#include <cmath>
//#include <libwebsockets.h>

//  Random number generation to determine which bus factory size to use
std::random_device dev2;
std::mt19937 rng(dev2());
std::uniform_int_distribution<std::mt19937::result_type> dist1(1, 3);
int rand_int = dist1(rng);

int main(int argc, char**argv) {
  std::cout << "Usage: ./build/bin/ExampleServer 8081" << std::endl;

  if (argc > 1) {
    int port = std::atoi(argv[1]);
    MyWebServerSessionState state;
	  
    MyWebServer* myWS = new MyWebServer();
    ConfigManager* cm = new ConfigManager();
        
    cm->ReadConfig("config.txt");
    std::cout << "Using default config file: config.txt" << std::endl;

    BusFactory* bf = (BusFactory*)nullptr;
    switch (rand_int){
    case 1:
      bf = new SmallBusFactory();
      break;
    case 2:
      bf = new MediumBusFactory();
      break;
    case 3:
    default:
      bf = new LargeBusFactory();
      break;
    }

    VisualizationSimulator* mySim = new VisualizationSimulator(myWS, cm, bf);

    state.commands["getRoutes"] = new GetRoutesCommand(myWS);
    state.commands["getBusses"] = new GetBussesCommand(myWS);
    state.commands["start"] = new StartCommand(mySim);
    state.commands["pause"] = new PauseCommand(mySim);
    state.commands["update"] = new UpdateCommand(mySim);
    state.commands["initRoutes"] = new InitRoutesCommand(cm);
    state.commands["listen"] = new AddListenerCommand(mySim);
    
    WebServerWithState<MyWebServerSession, MyWebServerSessionState>
      server(state, port);
    while (true) {
      server.service();
    }
  }

  return 0;
}


