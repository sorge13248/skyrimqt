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
        ushort MAX_HEALTH;
        const string image;
    public:
        explicit Enemy(string, ushort level = 1, ushort health = 100, string image = ":/icons/images/logo.png");
        virtual ~Enemy() = default;

        virtual ushort attack();

        string getName() const;
        ushort getHealth() const;
        ushort getLevel() const;
        ushort getMaxHealth() const;
        string getImage() const;

        bool getsAttacked(ushort);
        void setHealth(ushort);
        void setMaxHealth(ushort);
    };
}

#endif // ENEMY_H
