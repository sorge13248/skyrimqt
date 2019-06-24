#include "Item/shield.h"

Skyrim::Shield::Shield(string name, ushort level, ushort absorb) : Item(name, level), absorb(absorb) {}

ushort Skyrim::Shield::getAbsorb() const {
    return absorb + level;
}

string Skyrim::Shield::getType() const {
    return type;
}

string Skyrim::Shield::getImage() const {
   return image;
}

const string Skyrim::Shield::type = "Shield";
const string Skyrim::Shield::image = ":/items/images/zelda.png";
