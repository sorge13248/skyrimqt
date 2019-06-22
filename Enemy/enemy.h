#ifndef ENEMY_H
#define ENEMY_H

#include "../core.h"
#include "../basic.h"

namespace Skyrim {

    // ENEMIES
    class Enemy {
    protected:
        string name;
        ushort health;
        ushort level;
        ushort damage;
        const ushort MAX_HEALTH;
    public:
        explicit Enemy(string, ushort level = 1, ushort health = 100, ushort damage = 1);
        virtual ~Enemy() = default;

        virtual ushort attack();

        string getName() const;
        ushort getHealth() const;
        ushort getLevel() const;
        bool getsAttacked(ushort);
        ushort getMaxHealth() const;
        ushort getDamage() const;
    };
}

#endif // ENEMY_H
