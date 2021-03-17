/**
 * @file bus_factory.h
 *
 * @copyright 2020 Parker Patterson
 *
 * @brief Contains declarations for several subclasses of the bus factory class.
 * 
 */
#ifndef SRC_BUS_FACTORY_H_
#define SRC_BUS_FACTORY_H_

#include "src/bus.h"
#include <string>


class BusFactory {
protected:
  int id;
public:
  int GetId() const {return id;}
  virtual Bus * Generate(std::string, Route*, Route*) = 0;
};

class SmallBusFactory : public BusFactory {
protected:
  int id = -1;
public:
  Bus * Generate(std::string name, Route* in, Route* out) override;
};

class MediumBusFactory : public BusFactory {
protected:
  int id = -2;
public:
  Bus * Generate(std::string name, Route* in, Route* out) override;
};

class LargeBusFactory : public BusFactory {
protected:
  int id = -3;
public:
  Bus * Generate(std::string name, Route* in, Route* out) override;
};

class TimedBusFactory : public BusFactory{
protected:
  int bus_size_idx_ = 0;
  int num_bus_sizes_ = 2;
};

class EarlyBusFactory : public TimedBusFactory {
protected:
  int id = 0;
  int sizes_[2] = {30, 60};
public:
  Bus * Generate(std::string name, Route* in, Route* out) override;
};

class MiddayBusFactory : public TimedBusFactory {
protected:
  int id = 1;
  int sizes_[2] = {60, 90};
public:
  Bus * Generate(std::string name, Route* in, Route* out) override;
};

class LateBusFactory : public TimedBusFactory {
protected:
  int id = 2;
  int num_bus_sizes_ = 3;
  int sizes_[3] = {30, 60, 90};
public:
  Bus * Generate(std::string name, Route* in, Route* out) override;
};


#endif  // SRC_BUS_FACTORY_H_
