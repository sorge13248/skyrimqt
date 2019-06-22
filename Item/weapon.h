#ifndef WEAPON_H
#define WEAPON_H

#include "../core.h"
#include "item.h"

namespace Skyrim {

    class Weapon : public Item {
    private:
        ushort damage;
        const static string type;

    public:
        explicit Weapon(string name, ushort level = 1, ushort damage = 15);
        ~Weapon() = default;

        ushort getDamage() const;
        virtual string getType() const;
    };
}

#endif // WEAPON_H
