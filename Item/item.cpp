#include "Item/item.h"

Skyrim::Item::Item(string name, ushort level = 1) : name(name), level(level), quality(Quality::Normal) {

}

string Skyrim::Item::getName() const {
    return name;
}

ushort Skyrim::Item::getLevel() const {
    return level;
}

Skyrim::Item::Quality Skyrim::Item::getQuality() const {
    return quality;
}

void Skyrim::Item::setName(string name) {
    this->name = name;
}
