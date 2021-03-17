/**
 * @file visualization_simulator.cc
 *
 * @copyright 2020 Parker Patterson
 *
 * @brief Contains method definitions for the Visualization Simulator class
 */
#include "visualization_simulator.h"
#include "bus.h"
#include "route.h"

VisualizationSimulator::VisualizationSimulator(WebInterface* webI,
					       ConfigManager* configM,
					       BusFactory* factory) {
  webInterface_ = webI;
  configManager_ = configM;
  busFactory_ = factory; 
}

VisualizationSimulator::~VisualizationSimulator() {

}

void VisualizationSimulator::Pause(){
  paused = !paused;
}

void VisualizationSimulator::Start(const std::vector<int>& busStartTimings,
				   const int& numTimeSteps) {
  busStartTimings_ = busStartTimings;
  numTimeSteps_ = numTimeSteps;

  timeSinceLastBus_.resize(busStartTimings_.size());
  for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
    timeSinceLastBus_[i] = 0;
  }

  simulationTimeElapsed_ = 0;

  prototypeRoutes_ = configManager_->GetRoutes();
  for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
    prototypeRoutes_[i]->Report(std::cout);
        
    prototypeRoutes_[i]->UpdateRouteData();
    webInterface_->UpdateRoute(prototypeRoutes_[i]->GetRouteData());
  }
}

void VisualizationSimulator::UpdateTime(){
  time_t time_ptr = time(NULL);
  current_time_ = localtime(&time_ptr)->tm_hour;
};

void VisualizationSimulator::PrintTime(){
  std::cout << "Current time is " << current_time_ << "hrs" << std::endl;
}

void VisualizationSimulator::Update() {
  if (paused) {
    return;
  } else {
    simulationTimeElapsed_++;

    std::cout << "~~~~~~~~~~ The time is now " << simulationTimeElapsed_;
    std::cout << "~~~~~~~~~~" << std::endl;

    std::cout << "~~~~~~~~~~ Generating new busses if needed ";
    std::cout << "~~~~~~~~~~" << std::endl;

    UpdateTime();
    if (current_time_ >= 6 && current_time_ < 8){
      if (busFactory_->GetId() != 0){
	delete busFactory_;
	busFactory_ = new EarlyBusFactory;
      }
    } else if (current_time_ >= 8 && current_time_ < 15){
      if (busFactory_->GetId() != 1){
	delete busFactory_;
	busFactory_ = new MiddayBusFactory;
      }
    } else if (current_time_ >= 15 && current_time_ < 20){
      if (busFactory_->GetId() != 2){
	delete busFactory_;
	busFactory_ = new LateBusFactory;
      }
    } else if (busFactory_->GetId() != -1) {
      delete busFactory_;
      busFactory_ = new SmallBusFactory;
    }
    // Check if we need to generate new busses
    for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
        // Check if we need to make a new bus
        if (0 >= timeSinceLastBus_[i]) {
	  PrintTime();
	  switch (busFactory_->GetId()){
	  case -1:
	    std::cout << "Deploying only small busses" << std::endl;
	    std::cout << "Deploying a small bus" << std::endl;
	    break;
	  case 0:
	    std::cout << "Using the early strategy" << std::endl;
	    break;
	  case 1:
	    std::cout << "Using the midday strategy" << std::endl;
	    break;
	  case 2:
	    std::cout << "Using the late strategy" << std::endl;
	    break;
	  default:
	    std::cout << "Using only medium or only large busses" << std::endl;
	  }
	  Route * outbound = prototypeRoutes_[2 * i];
	  Route * inbound = prototypeRoutes_[2 * i + 1];

	  Bus* newBus =
	    busFactory_->Generate(std::to_string(busId),
				  inbound->Clone(),
				  outbound->Clone());
	  busses_.push_back(newBus);
	  busId++;
            
	  timeSinceLastBus_[i] = busStartTimings_[i];
        } else {
	  timeSinceLastBus_[i]--;
        }
    }   
    
    std::cout << "~~~~~~~~~ Updating busses ";
    std::cout << "~~~~~~~~~" << std::endl;

    // Update busses
    for (int i = static_cast<int>(busses_.size()) - 1; i >= 0; i--) {
        busses_[i]->Update();

        if (busses_[i]->IsTripComplete()) { 
            webInterface_->UpdateBus(busses_[i]->GetBusData(), true);
            busses_.erase(busses_.begin() + i);
            continue;
        }
        
        webInterface_->UpdateBus(busses_[i]->GetBusData());

        busses_[i]->Report(std::cout);
    }
    
    std::cout << "~~~~~~~~~ Updating routes ";
    std::cout << "~~~~~~~~~" << std::endl;
    // Update routes
    for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
        prototypeRoutes_[i]->Update();

        webInterface_->UpdateRoute(prototypeRoutes_[i]->GetRouteData());

        prototypeRoutes_[i]->Report(std::cout);
    }
  }
}

void VisualizationSimulator::ClearListeners(){
  for (std::vector<Bus*>::iterator iter = busses_.begin();
       iter != busses_.end(); ++iter){
    (*iter)->ClearObservers();
  }
}

void VisualizationSimulator::AddListener(std::string* id, IObserver* observer){
  for (std::vector<Bus*>::iterator iter = busses_.begin();
       iter != busses_.end(); ++iter){
    if ((*iter)->GetName().std::string::compare(*id) == 0){
      (*iter)->RegisterObserver(observer);
    }
  }
}
