//
// Created by fsorge on 6/8/19.
//

#ifndef SKYRIM_RAIDERBOSS_H
#define SKYRIM_RAIDERBOSS_H

#include "raider.h"

namespace Skyrim {

    class RaiderBoss : public Raider {
    public:
        explicit RaiderBoss(ushort level = 1);
        ~RaiderBoss() = default;

        virtual ushort attack();
    };
}


#endif //SKYRIM_RAIDERBOSS_H
