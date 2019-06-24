//
// Created by fsorge on 6/8/19.
//

#ifndef SKYRIM_GHOST_H
#define SKYRIM_GHOST_H

#include "enemy.h"

namespace Skyrim {

    class Ghost : public Enemy {
    public:
        explicit Ghost(ushort level = 1);
        ~Ghost() = default;

        virtual ushort attack();
    };
}

#endif //SKYRIM_GHOST_H
