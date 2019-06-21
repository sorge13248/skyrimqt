#include "matchwindow.h"
#include "ui_matchwindow.h"

MatchWindow::MatchWindow(QWidget *parent, const QString& playerName) :
    QWidget(parent),
    ui(new Ui::MatchWindow),
    game(new Skyrim::QtGame())
{
    ui->setupUi(this);
    game->newGame(playerName);
    ui->playerLabel->setText("Player: " + playerName);

    bool started = false;
    try {
        started = game->startMatch();
    } catch(Skyrim::NoPlayerLoaded) {
        QtSupport::error("No player loaded. Something went wrong.");
    }

    game->playerEquipItem(new Skyrim::Weapon("Iron Sword"));
    game->playerEquipItem(new Skyrim::Shield("Wood Shield"));
}

MatchWindow::~MatchWindow()
{
    delete ui;
}

void MatchWindow::generateEnemy() {
    if (!game->isEnemySpawned()) {
        ushort rand = FrancescoSorge::Basic::random(0, 15);
        Skyrim::Enemy* enemy = nullptr;

        if (rand >= 1 && rand <= 3) {
            enemy = new Skyrim::Raider(FrancescoSorge::Basic::random(1, game->getPlayer()->getLevel() + 1));
        } else if (rand >= 4 && rand <= 6) {
            enemy = new Skyrim::Animal(FrancescoSorge::Basic::random(1, game->getPlayer()->getLevel() + 1));
        } else if (rand >= 7 && rand <= 9) {
            enemy = new Skyrim::Ghost(FrancescoSorge::Basic::random(1, game->getPlayer()->getLevel() + 1));
        } else if (rand == 10) {
            enemy = new Skyrim::RaiderBoss(game->getPlayer()->getLevel());
        }

        game->setEnemy(enemy);

        if (game->isEnemySpawned()) {
            cout << "An enemy spawned: " << enemy->getName() << " (health: " << enemy->getHealth()
                 << ", level: " << enemy->getLevel() << ")" << endl;

            ui->dyamicButton->setText("Attack!");
        } else {
            ui->dyamicButton->setText("Move on");
        }
        /*
         * 2-3 categorie di nemico, bestia (vita=livello*50; danno 1-10), corazzato (vita=livello*80, danno 1-5), spirito (vita 20°livello, danno 2-4, ma scudo danno pari a livello)
         * possibile trovare nemici BOSS, vita e danno * 1,5 ma quando li uccidi bonus (cura completa?) ed exp x2
         */
    }
}
void MatchWindow::on_dyamicButton_clicked()
{
    if (game->isEnemySpawned()) {
        Console::printStd("Attacking");
        if (game->getEnemy()->getsAttacked(game->getPlayer()->attack())) {

        } else {

        }
    } else {
        Console::printStd("Moving on");
        generateEnemy();
    }
}
