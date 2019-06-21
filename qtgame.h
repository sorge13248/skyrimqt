#ifndef QTGAME_H
#define QTGAME_H

#include "console.h"
#include "exceptions.h"
#include "player.h"
#include "Item/item.h"
#include "Enemy/enemy.h"
#include "Enemy/raider.h"
#include "Enemy/animal.h"
#include "Enemy/ghost.h"
#include "Enemy/raiderboss.h"

namespace Skyrim {

    // GAME
    class QtGame {
    private:
        bool isMatchRunning;
        Player* player;
        Enemy* enemy;

    public:
        explicit QtGame();

        Player* getPlayer() const;
        Enemy* getEnemy() const;
        bool isEnemySpawned() const;

        bool setPlayer(Player* const);
        void setEnemy(Enemy* const);

        bool newGame(string);
        void loadGame();
        bool startMatch();
        bool playerEquipItem(Item* const);
        void enemyDie();

    };
}

#endif // QTGAME_H
