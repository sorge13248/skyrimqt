#ifndef WEAPON_H
#define WEAPON_H

#include "../core.h"
#include "item.h"

namespace Skyrim {

    class Weapon : public Skyrim::Item {
    private:
        ushort damage;
    public:
        string const type = "Weapon";

        explicit Weapon(string name, ushort level = 1, ushort damage = 15);

        ushort getDamage() const;
    };
}

#endif // WEAPON_H
