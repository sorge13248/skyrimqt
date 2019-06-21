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

bool Skyrim::QtGame::newGame(const QString& playerName) {
    if (player != nullptr) {
        delete player;
    }
    player = new Player(playerName);
    Console::printStd("Player loaded correctly");
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

    Console::printStd("Game started, good luck!");

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

bool Skyrim::QtGame::setEnemy(Enemy* const enemy) {
    if (enemy != nullptr) {
        this->enemy = enemy;
        return true;
    } else {
        return false;
    }
}

bool Skyrim::QtGame::playerEquipItem(Item* const item) {
    return player->equipItem(item);
}
