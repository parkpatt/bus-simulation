/**
 * @file bus_factory.cc
 *
 * @copyright 2020 Parker Patterson
 *
 * @brief defines the Generate() method of three sizes of BusFactory
 * 
 */
#include "src/bus_factory.h"

using namespace std;

Bus * SmallBusFactory::Generate(string name, Route* in, Route* out){
  return new Bus(name, in, out, 30);
}

Bus * MediumBusFactory::Generate(string name, Route* in, Route* out){
  return new Bus(name, in, out, 60);
}

Bus * LargeBusFactory::Generate(string name, Route* in, Route* out){
  return new Bus(name, in, out, 90);
}

Bus * EarlyBusFactory::Generate(string name, Route* in, Route* out){
  int bus_size_ = sizes_[bus_size_idx_];
  if (bus_size_idx_ == 0){
    std::cout << "Deploying a small bus" << endl;
  } else {
    std::cout << "Deploying a regular bus" << endl;
  }
  bus_size_idx_ = (bus_size_idx_ + 1) % num_bus_sizes_;
  return new Bus(name, in, out, bus_size_);
};

Bus * MiddayBusFactory::Generate(string name, Route* in, Route* out){
  int bus_size_ = sizes_[bus_size_idx_];
  if (bus_size_idx_ == 0){
    std::cout << "Deploying a regular bus" << std::endl;
  } else {
    std::cout << "Deploying a large bus" << std::endl;
  }
  bus_size_idx_ = (bus_size_idx_ + 1) % num_bus_sizes_;
  return new Bus(name, in, out, bus_size_);
};

Bus * LateBusFactory::Generate(string name, Route* in, Route* out){
  int bus_size_ = sizes_[bus_size_idx_];
  if (bus_size_idx_ == 0){
    std::cout << "Deploying a small bus" << std::endl;
  } else if (bus_size_idx_ == 1) {
    std::cout << "Deploying a regular bus" << std::endl;
  } else {
    std::cout << "Deploying a large bus" << std::endl;
  }
  bus_size_idx_ = (bus_size_idx_ + 1) % num_bus_sizes_;
  return new Bus(name, in, out, bus_size_);
};
