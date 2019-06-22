//
// Created by fsorge on 6/8/19.
//

#include "raiderboss.h"

Skyrim::RaiderBoss::RaiderBoss(ushort level) : Raider(level, 100) {
    name = "Raider [BOSS]";
}

ushort Skyrim::RaiderBoss::attack() {
    return 5 * level;
}
