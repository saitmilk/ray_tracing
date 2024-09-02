#ifndef INTERVAL_H
#define INTERVAL_H

#include "Rtweekend.hpp"

class Interval {
public:
    double min, max;

    Interval()
        : min(+infinity)
        , max(-infinity) { } // Default interval is empty

    Interval(double min, double max)
        : min(min)
        , max(max) { }

    double size() const {
        return max - min;
    }

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }

    static const Interval empty, universe;
};

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);

#endif