/**
 * @file iobserver.hh
 * @copyright 2020 Parker Patterson
 * @brief The header file for the IObserver class
 */

#ifndef SRC_IOBSERVER_HH_
#define SRC_IOBSERVER_HH_

#include "./data_structs.h"

class IObserver {
public:
  virtual void Notify(BusData* info) = 0;
};

#endif  // SRC_IOBSERVER_HH_
