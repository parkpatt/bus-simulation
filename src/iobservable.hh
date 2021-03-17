/**
 * @file iobservable.hh
 * @copyright 2020 Parker Patterson
 * @brief The header file for the IObservable/ISubject class
 */

#ifndef SRC_IOBSERVABLE_HH_
#define SRC_IOBSERVABLE_HH_

#include "./iobserver.hh"

class IObservable {
protected:
  std::vector<IObserver*> observer_;
public:
  void RegisterObserver (IObserver* observer);
  void ClearObservers();
  void NotifyObservers(BusData* data);
};

#endif  // SRC_IOBSERVABLE_HH_
