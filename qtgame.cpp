#include "qtgame.h"

//
// Created by fsorge on 6/8/19.
//

Skyrim::QtGame::QtGame() { }

Skyrim::Player* Skyrim::QtGame::getPlayer() const {
    return player;
}

Skyrim::Enemy* Skyrim::QtGame::getEnemy() const {
    return enemy;
}

bool Skyrim::QtGame::newGame(string playerName) {
    player = new Player(playerName);
    return true;
}

bool Skyrim::QtGame::loadGame(string name, ushort health, ushort experience, ushort level, ushort healPotion) {
    player = new Player(name, health, experience, level, healPotion);
    return true;
}

bool Skyrim::QtGame::startMatch() {
    if (player == nullptr) {
        throw Skyrim::NoPlayerLoaded();
    }

    if (enemy != nullptr) {
        enemy = nullptr;
    }

    return true;
}

bool Skyrim::QtGame::isEnemySpawned() const {
    return enemy != nullptr;
}

bool Skyrim::QtGame::setPlayer(Player* const player) {
    if (player != nullptr) {
        this->player = player;
        return true;
    } else {
        return false;
    }
}

void Skyrim::QtGame::setEnemy(Enemy* const enemy) {
    this->enemy = enemy;
}

bool Skyrim::QtGame::playerEquipItem(Item* const item) {
    return player->equipItem(item);
}

void Skyrim::QtGame::enemyDie() {
    player->gainExperience(10 * enemy->getLevel());
    player->addHealPotion(enemy->getLevel());

    if (enemy) delete enemy;
    setEnemy(nullptr);
}

const QStringList Skyrim::QtGame::scenes = {QString::fromStdString(":/levels/images/generic.jpg"), QString::fromStdString(":/levels/images/dwemer.jpg"), QString::fromStdString(":/levels/images/forest.jpg"), QString::fromStdString(":/levels/images/fort.jpg")};

const QStringList Skyrim::QtGame::weapons = {QString::fromStdString("Iron Sword"), QString::fromStdString("Steel Sword"), QString::fromStdString("Diamond Sword"), QString::fromStdString("Daedra Sword"), QString::fromStdString("Sword of Blade's master"), QString::fromStdString("Bow"), QString::fromStdString("Wood Bow"), QString::fromStdString("Axe"), QString::fromStdString("Knife"), QString::fromStdString("Staff of fire"), QString::fromStdString("Staff of ice"), QString::fromStdString("Enchanted Sword")};

const QStringList Skyrim::QtGame::shields = {QString::fromStdString("Wood Shield"), QString::fromStdString("Iron Shield"), QString::fromStdString("Marvel S.H.I.E.L.D."), QString::fromStdString("Iron Dome"), QString::fromStdString("Shield Spell")};
