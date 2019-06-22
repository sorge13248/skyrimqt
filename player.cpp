#include "player.h"

Skyrim::Player::Player(string name, ushort health, ushort experience, ushort level, ushort healPotion) : name(name), health(health), experience(experience), level(level == 0 ? 1 : level), healPotion(healPotion), inventory(new FrancescoSorge::QContainer<Item*>()) {

}

string Skyrim::Player::getName() const {
    return name;
}

ushort Skyrim::Player::getHealth() const {
    return health;
}

ushort Skyrim::Player::getLevel() const {
    return level;
}

ushort Skyrim::Player::getHealPotion() const {
    return healPotion;
}

FrancescoSorge::QContainer<Skyrim::Item*>* Skyrim::Player::getInventory() const {
    return inventory;
}

ushort Skyrim::Player::getMaxInventory() const {
    return MAX_INVENTORY + level;
}

Skyrim::Item* Skyrim::Player::addToInventory(Item* item) {
    if (inventory->getCount() < getMaxInventory()) {
        inventory->insertBack(item);
        return item;
    }
    return nullptr;
}


void Skyrim::Player::addHealPotion(ushort potion) {
    healPotion += potion;

    if (healPotion > getMaxHealPotion()) {
        healPotion = getMaxHealPotion();
    }
}

bool Skyrim::Player::equipItem(Item* item, bool fake) {
    bool isTheSame = false;
    if (Weapon* wp = dynamic_cast<Weapon*>(item)) {
        if (wp == weapon) {
            isTheSame = true;
        } else {
            if(!fake) weapon = wp;
        }
    } else if (Shield* sh = dynamic_cast<Shield*>(item)) {
        if (sh == shield) {
            isTheSame = true;
        } else {
            if(!fake) shield = sh;
        }
    }
    return !isTheSame;
}

bool Skyrim::Player::removeFromInventory(ushort index) {
    return inventory->remove(index);
}

ushort Skyrim::Player::attack() const {
    return ((weapon->getDamage() + weapon->getQuality()) * weapon->getLevel()) + level;
}

bool Skyrim::Player::getsAttacked(ushort damage) {
    if (damage - shield->getAbsorb() <= 0) {
        damage = 1;
    } else {
        damage -= shield->getAbsorb();
    }


    if (health - damage <= 0) {
        return true;
    } else {
        health -= damage;
        return false;
    }
}

void Skyrim::Player::gainExperience(ushort xp) {
    experience += xp;

    if (experience >= 30 * level) { // level up
        level++;
    }
}

ushort Skyrim::Player::getMaxHealth() const {
    return MAX_HEALTH * level;
}

void Skyrim::Player::heals() {
    if (this->healPotion > 0) {
        this->healPotion--;

        this->health += 10 * level;
        if (this->health > getMaxHealth()) {
            this->health = getMaxHealth();
        }
    }
}

ushort Skyrim::Player::getExperience() const {
    return experience;
}

ushort Skyrim::Player::getMaxHealPotion() const {
    return MAX_HEAL_POTION * level;
}

ushort Skyrim::Player::MAX_HEALTH = 100;
ushort Skyrim::Player::MAX_HEAL_POTION = 2;
ushort Skyrim::Player::MAX_INVENTORY = 9;
