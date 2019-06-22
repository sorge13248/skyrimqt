#include "Item/shield.h"

Skyrim::Shield::Shield(string name, ushort level, ushort absorb) : Item(name, level), absorb(absorb) {}

ushort Skyrim::Shield::getAbsorb() const {
    return absorb + level;
}

string Skyrim::Shield::getType() const {
    return type;
}

const string Skyrim::Shield::type = "Shield";
