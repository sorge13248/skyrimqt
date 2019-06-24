#include "Enemy/enemy.h"

Skyrim::Enemy::Enemy(string name, ushort level, ushort health, string image)
: name(name), health(health * level), level(level == 0 ? 1 : level), image(image), MAX_HEALTH(health * level) {}

ushort Skyrim::Enemy::attack() {
    return FrancescoSorge::Basic::random(2, 6) * level;
}

string Skyrim::Enemy::getName() const {
    return name;
}

ushort Skyrim::Enemy::getHealth() const {
    return health;
}

ushort Skyrim::Enemy::getLevel() const {
    return level;
}

string Skyrim::Enemy::getImage() const {
    return image;
}

void Skyrim::Enemy::setHealth(ushort h) {
    health = h;
}

bool Skyrim::Enemy::getsAttacked(ushort damage) {
    if (health - damage <= 0) {
        return true;
    } else {
        health -= damage;
        return false;
    }
}

ushort Skyrim::Enemy::getMaxHealth() const {
    return MAX_HEALTH;
}
