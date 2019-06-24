//
// Created by fsorge on 6/8/19.
//

#include "ghost.h"

Skyrim::Ghost::Ghost(ushort level) : Enemy("Ghost", level, 30, ":/enemies/images/ghost.png") {}

ushort Skyrim::Ghost::attack() {
    ushort damage = FrancescoSorge::Basic::random(2, 5) * level;
    return damage;
}
