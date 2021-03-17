/**
 * @file visualization_simulator.h
 *
 * @copyright 2020 Parker Patterson
 *
 * @brief The header file for the visualization simulator
 */
#ifndef VISUALIZATION_SIMULATOR_H_
#define VISUALIZATION_SIMULATOR_H_

#include <vector>
#include <list>
#include <ctime>

#include "./web_interface.h"
#include "../../src/config_manager.h"
#include "../../src/bus_factory.h"
#include "../../src/iobserver.hh"

class Route;
class Bus;
class Stop;

class VisualizationSimulator {
    public:
  VisualizationSimulator(WebInterface*, ConfigManager*, BusFactory*);
        ~VisualizationSimulator();

        void Start(const std::vector<int>&, const int&);
        void Update();
	void Pause();
	void ClearListeners();
	void AddListener(std::string* id, IObserver* observer);
	void UpdateTime();
	int GetTime() const {return current_time_;}
	void PrintTime();

    private:
        WebInterface* webInterface_;
        ConfigManager* configManager_;
	BusFactory* busFactory_;
       
        std::vector<int> busStartTimings_;
        std::vector<int> timeSinceLastBus_;
        int numTimeSteps_;
        int simulationTimeElapsed_;
	int current_time_;
        std::vector<Route *> prototypeRoutes_;
        std::vector<Bus *> busses_;

        int busId = 1000;
	bool paused = false;
};

#endif // VISUALIZATION_SIMULATOR_H_
