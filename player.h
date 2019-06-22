#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include "core.h"
#include "Item/item.h"
#include "Item/weapon.h"
#include "Item/shield.h"
#include "qcontainer.h"

namespace Skyrim {

    // PLAYER
    class Player {
    private:
        string name;
        ushort health;
        ushort experience;
        ushort level;
        ushort healPotion;

        Weapon *weapon = nullptr;
        Shield *shield = nullptr;
        FrancescoSorge::QContainer<Item*>* inventory;

        static ushort MAX_HEAL_POTION;
        static ushort MAX_HEALTH;
        static ushort MAX_INVENTORY;


    public:
        explicit Player(string name, ushort health = 100, ushort experience = 0, ushort level = 1, ushort healPotion = 2);

        string getName() const;
        ushort getHealth() const;
        ushort getLevel() const;
        ushort getHealPotion() const;
        FrancescoSorge::QContainer<Item*>* getInventory() const;
        ushort getMaxInventory() const;
        ushort getMaxHealth() const;
        ushort getExperience() const;
        ushort getMaxHealPotion() const;

        ushort attack() const;

        Item* addToInventory(Item*);
        bool removeFromInventory(ushort);
        void addHealPotion(ushort);
        bool equipItem(Item*, bool f=false);
        bool getsAttacked(ushort);
        void gainExperience(ushort);
        void heals();
    };

}

#endif // PLAYER_H
