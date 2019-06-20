#include "qtgame.h"

//
// Created by fsorge on 6/8/19.
//

Skyrim::QtGame::QtGame() { }

Skyrim::Player* Skyrim::QtGame::getPlayer() const {
    return player;
}

bool Skyrim::QtGame::newGame(const QString& playerName) {
    if (player != nullptr) {
        delete player;
    }
    player = new Player(playerName);
    Console::print("Player loaded correctly");
    return true;
}

void Skyrim::QtGame::loadGame() {

}

void Skyrim::QtGame::startMatch() {
    if (player == nullptr) {
        throw Exceptions::NoPlayerLoaded;
    }

    if (enemy != nullptr) {
        enemy = nullptr;
    }

    Console::print("Game started, good luck!");
    bool exitGame = false;
    bool endTurn;

    /*do {
        endTurn = false;

        if (enemy != nullptr) {
            if (player->getsAttacked(enemy->attack())) {
                cout << "You died. End game. You'll be luckier next time!" << endl;
                exitGame = true;
            }
        }

        player->equipItem(new Weapon("Iron Sword"));
        player->equipItem(new Shield("Wood Shield"));

        if(!exitGame) {
            if (enemy == nullptr) {
                ushort rand = FrancescoSorge::Basic::random(0, 15);

                if (rand >= 1 && rand <= 3) {
                    enemy = new Raider(FrancescoSorge::Basic::random(1, QtGame::getPlayer()->getLevel() + 1));
                } else if (rand >= 4 && rand <= 6) {
                    enemy = new Animal(FrancescoSorge::Basic::random(1, QtGame::getPlayer()->getLevel() + 1));
                } else if (rand >= 7 && rand <= 9) {
                    enemy = new Ghost(FrancescoSorge::Basic::random(1, QtGame::getPlayer()->getLevel() + 1));
                } else if (rand == 10) {
                    enemy = new RaiderBoss(QtGame::getPlayer()->getLevel());
                }

                if (rand != 0) {
                    cout << "An enemy spawned: " << enemy->getName() << " (health: " << enemy->getHealth()
                         << ", level: " << enemy->getLevel() << ")" << endl;
                }
                /*
                 * 2-3 categorie di nemico, bestia (vita=livello*50; danno 1-10), corazzato (vita=livello*80, danno 1-5), spirito (vita 20°livello, danno 2-4, ma scudo danno pari a livello)
                 * possibile trovare nemici BOSS, vita e danno * 1,5 ma quando li uccidi bonus (cura completa?) ed exp x2

            }

            cout << "+++++++++++++++++++++++++++++++" << endl;
            cout << player->getName() << "'s (health: " << player->getHealth()
                 << ", level: " << player->getLevel() << ")" << endl;

            if (enemy != nullptr) {
                cout << enemy->getName() << "'s health: " << enemy->getHealth() << endl;
            }

            cout << "+++++++++++++++++++++++++++++++" << endl;

            do {
                cout << "Your turn! Enter action [move, attack, heal (" << player->getHealPotion() << "), inventory, exit-game]: ";
                string action;
                getline(cin, action);

                if (action == "exit-game") {
                    delete enemy;
                    enemy = nullptr;
                    exitGame = true;
                    endTurn = true;
                } else if (action == "move") {
                    cout << "Player moved forward" << endl;
                    endTurn = true;
                } else if (action == "attack") {
                    endTurn = true;

                    if (enemy == nullptr) {
                        cout << "You're not in combat! Moving to next turn." << endl;
                    } else {
                        cout << "Attacking enemy" << endl;
                        if (enemy->getsAttacked(player->attack())) {
                            cout << "Enemy died" << endl;
                            player->gainExperience(10 * enemy->getLevel());
                            cout << "Enemy dropped " << enemy->getLevel() << " healing potion(s)" << endl;
                            player->addHealPotion(enemy->getLevel());

                            delete enemy;
                            enemy = nullptr;
                        }
                    }
                } else if (action == "heal") {
                    if (player->getHealPotion() > 0) {
                        player->heals();
                        cout << "Player's health: " << player->getHealth() << endl;
                    } else {
                        cout << "You don't have healing potion!" << endl;
                    }
                } else if (action == "inventory") {
                    if (player->addToInventory(new Weapon("Arma di prova " + std::to_string(FrancescoSorge::Basic::random(1, 1000))))) {
                        cout << "Arma aggiunta" << endl;
                    } else {
                        cout << "Inventario pieno" << endl;
                    }
                    cout << "Inventory " << player->getInventory()->count() << "/" << player->getMaxInventory() << endl;

                    if (player->getInventory()->count() > 0) {
                        ushort count = 0;
                        for (FrancescoSorge::QContainer<Item*>::constiterator it = player->getInventory()->begin(); it != player->getInventory()->end(); ++it) {
                            count++;
                            cout << "Select with number " << count << endl;
                            cout << "Name: " << (*it)->getName() << endl;
                            cout << "Type: " << (*it)->type << endl;
                            if (Weapon* wp = dynamic_cast<Weapon*>(*it)) {
                                cout << "Damage: " << wp->getDamage() << endl;
                            } else if (Shield* sh = dynamic_cast<Shield*>(*it)) {
                                cout << "Absorb: " << sh->getAbsorb() << endl;
                            }
                            cout << "Level: " << (*it)->getLevel() << endl;
                            cout << "Quality: "<< (*it)->getQuality() << endl;
                            cout << "++++++++++++" << endl;
                        }

                        cout << "Select an item on range [1-" << count << "] or type an invalid one to exit: ";
                        string sel_in;
                        getline(cin, sel_in);
                        try {
                            ushort selection = std::stoi(sel_in);

                            if (selection >= 1 && selection <= count) {
                                cout << "Item selected: " << player->getInventory()->getByIndex(selection-1)->getName() << endl;
                                cout << "What do you want to do?" << endl;
                                cout << "\t1. Equip" << endl;
                                cout << "\t2. Drop" << endl;
                                cout << "\t3. Cancel" << endl;

                                string sel_in2;
                                getline(cin, sel_in2);
                                try {
                                    ushort selection2 = std::stoi(sel_in2);

                                    if (selection2 >= 1 && selection <= 3) {
                                        cout << "Executing action " << selection2 << endl;
                                    }
                                } catch(...) { }
                            }
                        } catch(...) { }
                    } else {
                        cout << "Inventory is empty" << endl;
                    }

                } else {
                    cout << "Invalid action. Try again." << endl;
                }
            }while(!endTurn);
        }
    } while(!exitGame);*/
}
