//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Current.h"

Current::Current(double value_, unsigned int ID_, unsigned long start_, unsigned long stop_)
        : value(value_), ID(ID_), start(start_ * C::TIME_CONVERTER), stop(stop_ * C::TIME_CONVERTER)
    {}

double Current::getValue(unsigned long time) const {

    assert(start <= stop);

    return (time >= start && time <= stop) ? value : 0;
}
