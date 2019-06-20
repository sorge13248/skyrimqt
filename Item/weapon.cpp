#include "Item/weapon.h"

Skyrim::Weapon::Weapon(string name, ushort level, ushort damage) : Item(name, level), damage(damage) {}

ushort Skyrim::Weapon::getDamage() const {
    return damage;
}
