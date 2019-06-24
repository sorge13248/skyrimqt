#include "Item/weapon.h"

Skyrim::Weapon::Weapon(string name, ushort level, ushort damage) : Item(name, level), damage(damage) {}

ushort Skyrim::Weapon::getDamage() const {
    return damage + level;
}

string Skyrim::Weapon::getType() const {
    return type;
}

string Skyrim::Weapon::getImage() const {
   return image;
}

const string Skyrim::Weapon::type = "Weapon";
const string Skyrim::Weapon::image = ":/items/images/sword.png";
