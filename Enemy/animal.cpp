//
// Created by fsorge on 6/8/19.
//

#include "animal.h"

Skyrim::Animal::Animal(ushort level) : Enemy("Animal", level, 40, ":/enemies/images/animal.png") {}

ushort Skyrim::Animal::attack() {
    return FrancescoSorge::Basic::random(1, 10) * level;
}
