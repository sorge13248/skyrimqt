//
// Created by fsorge on 6/8/19.
//

#ifndef SKYRIM_RAIDER_H
#define SKYRIM_RAIDER_H

#include "../basic.h"
#include "enemy.h"

namespace Skyrim {
    class Raider : public Enemy {
    public:
        explicit Raider(ushort level = 1, ushort health = 80);

        virtual ushort attack();
    };
}


#endif //SKYRIM_RAIDER_H
