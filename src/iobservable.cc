/**
 * @file iobservable.cc
 * @copyright 2020 Parker Patterson
 * @brief implementation for IObservable class methods
 */

#include "iobservable.hh"

using namespace std;

void IObservable::RegisterObserver(IObserver* observer){
  observer_.push_back(observer);
}

void IObservable::ClearObservers(){
  observer_.erase(observer_.begin(), observer_.end());
}

void IObservable::NotifyObservers(struct BusData* data){
  for (vector<IObserver*>::const_iterator iter = observer_.begin();
       iter != observer_.end(); ++iter){
    if (*iter != 0)
      (*iter)->Notify(data);
  }
}
