//
// Created by fsorge on 6/8/19.
//

#include "raider.h"

Skyrim::Raider::Raider(ushort level, ushort health) : Enemy("Raider", level, health) {}

ushort Skyrim::Raider::attack() {
    return FrancescoSorge::Basic::random(1, 5) * level;
}
