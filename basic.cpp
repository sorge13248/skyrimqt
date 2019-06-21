//
// Created by fsorge on 6/8/19.
//

#include <string>
#include "core.h"
#include "basic.h"

ushort FrancescoSorge::Basic::random(ushort min, ushort max) { // both inclusive
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(min, max); // define the range

    return static_cast<ushort>(distr(eng));
}
