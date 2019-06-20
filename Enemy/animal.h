//
// Created by fsorge on 6/8/19.
//

#ifndef SKYRIM_ANIMAL_H
#define SKYRIM_ANIMAL_H

#include "enemy.h"

namespace Skyrim {

    class Animal : public Enemy {
    public:
        explicit Animal(ushort level = 1);

        virtual ushort attack();
    };
}


#endif //SKYRIM_ANIMAL_H
