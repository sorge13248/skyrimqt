#include "player.h"

Skyrim::Player::Player(const QString& name, ushort health, ushort experience, ushort level, ushort healPotion) : name(name), health(health == 0 ? 1 : health), experience(experience), level(level == 0 ? 1 : level), healPotion(healPotion), inventory(new FrancescoSorge::QContainer<Item*>()) {

}

const QString& Skyrim::Player::getName() const {
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
    return MAX_INVENTORY * level;
}

Skyrim::Item* Skyrim::Player::addToInventory(Item* item) {
    if (inventory->count() < getMaxInventory()) {
        inventory->insertBack(item);
        return item;
    }
    return nullptr;
}


void Skyrim::Player::addHealPotion(ushort potion) {
    healPotion += potion;

    if (healPotion > MAX_HEAL_POTION * level) {
        cout << "You're carrying the max amount of healing potion (" << (MAX_HEAL_POTION * level) << ")"
             << endl;
        healPotion = MAX_HEAL_POTION * level;
    }
}

bool Skyrim::Player::equipItem(Item* item) {
    bool isTheSame = false;
    if (Weapon* wp = dynamic_cast<Weapon*>(item)) {
        if (wp == weapon) {
            isTheSame = true;
        } else {
            if (weapon) delete weapon;
            weapon = wp;
        }
    } else if (Shield* sh = dynamic_cast<Shield*>(item)) {
        if (sh == shield) {
            isTheSame = true;
        } else {
            if (shield) delete shield;
            shield = sh;
        }
    }
    return !isTheSame;
}

void Skyrim::Player::dropItem(Item* item) {

}

ushort Skyrim::Player::attack() const {
    return ((weapon->getDamage() + weapon->getQuality()) * weapon->getLevel()) + level;
}

bool Skyrim::Player::getsAttacked(ushort damage) {
    damage -= shield->getAbsorb();
    if (damage < 0) damage = 0;

    if (health - damage <= 0) {
        return true;
    } else {
        health -= damage;
        return false;
    }
}

void Skyrim::Player::gainExperience(ushort xp) {
    cout << "Gained " << xp << " experience points" << endl;
    experience += xp;

    if (experience >= 20 * level) { // level up
        level++;
        cout << "Level up! You've reached level " << level << ". Congrats!" << endl;
    }
}

void Skyrim::Player::heals() {
    if (this->healPotion > 0) {
        this->healPotion--;

        this->health += 10 * level;
        if (this->health > MAX_HEALTH * level) {
            this->health = MAX_HEALTH;
        }
    }
}

ushort Skyrim::Player::MAX_HEALTH = 100;
ushort Skyrim::Player::MAX_HEAL_POTION = 2;
ushort Skyrim::Player::MAX_INVENTORY = 10;
