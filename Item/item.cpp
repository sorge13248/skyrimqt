#include "Item/item.h"

Skyrim::Item::Item(string name, ushort level = 1) : name(name), level(level) { }

string Skyrim::Item::getName() const {
    return name;
}

ushort Skyrim::Item::getLevel() const {
    return level;
}

void Skyrim::Item::setName(string name) {
    this->name = name;
}

void Skyrim::Item::setLevel(ushort level) {
    this->level = level;
}
