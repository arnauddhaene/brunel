//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Current.h"

Current::Current(double value_, unsigned int ID_, unsigned long start_, unsigned long stop_)
        : value(value_), ID(ID_), start(start_ * C::TIME_CONVERTER), stop(stop_ * C::TIME_CONVERTER)
    {}

Current::Current(double value_, unsigned int ID_)
        : value(value_), ID(ID_), start(0), stop((unsigned long)1e9)
{}

double Current::getValue(unsigned long time) const {
   return (time >= start && time <= stop) ? value : 0;
}

double Current::getStart() const {
    return start;
}

double Current::getStop() const {
    return stop;
}

void Current::setValue(double val) {
    value = val;
}

void Current::setStop(unsigned long sto) {
    stop = sto;
}

void Current::setStart(unsigned long sta) {
    start = sta;
}