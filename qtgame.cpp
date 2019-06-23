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

void Skyrim::QtGame::loadGame() {

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
