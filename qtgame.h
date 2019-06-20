#ifndef QTGAME_H
#define QTGAME_H

#include "console.h"
#include "exceptions.h"
#include "player.h"
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

        bool newGame(const QString&);

        void loadGame();

        void startMatch();
    };
}

#endif // QTGAME_H
