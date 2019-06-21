#include "matchwindow.h"
#include "ui_matchwindow.h"

MatchWindow::MatchWindow(QWidget *parent, string playerName) :
    QWidget(parent),
    ui(new Ui::MatchWindow),
    game(new Skyrim::QtGame())
{
    ui->setupUi(this);

    const QRect screen = QApplication::desktop()->screenGeometry();
    this->move(screen.center() - this->rect().center());

    game->newGame(playerName);

    bool started = false;
    try {
        started = game->startMatch();
    } catch(Skyrim::NoPlayerLoaded) {
        QtSupport::error("No player loaded. Something went wrong.");
    }

    Skyrim::Weapon* sword = new Skyrim::Weapon("Iron Sword");
    Skyrim::Shield* shield = new Skyrim::Shield("Wood Shield");

    game->playerEquipItem(sword);
    game->playerEquipItem(shield);

    game->getPlayer()->addToInventory(sword);
    game->getPlayer()->addToInventory(shield);

    nextTurn();
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
            setEnemyVisibility(true);
        } else {
            ui->dyamicButton->setText("Move on");
        }
    }
}

void MatchWindow::setEnemyVisibility(bool b) {
    ui->enemyName->setVisible(b);
    ui->enemyHealthBar->setVisible(b);
    ui->enemyHealth->setVisible(b);
}

ushort MatchWindow::getValueForHealth(ushort health, ushort maxHealth) {
    return health * 100 / maxHealth;
}

void MatchWindow::updateInventory() {
    ui->inventoryLabel->setText("Inventory (" + QString::number(game->getPlayer()->getInventory()->getCount()) + "/" + QString::number(game->getPlayer()->getMaxInventory()) + "):");

    QStringListModel* model = new QStringListModel(this);

    QStringList list;
    for (FrancescoSorge::QContainer<Skyrim::Item*>::constiterator it = game->getPlayer()->getInventory()->begin(); it != game->getPlayer()->getInventory()->end(); ++it) {
        list << QString::fromStdString((*it)->getName() + " (Level " + std::to_string((*it)->getLevel()) + ")");
    }

    model->setStringList(list);
    ui->inventoryList->setModel(model);
}

void MatchWindow::nextTurn() {
    ui->playerLabel->setText(QString::fromStdString(game->getPlayer()->getName()) + " - Level " + QString::number(game->getPlayer()->getLevel()));
    ui->playerHealth->setText(QString::number(game->getPlayer()->getHealth()) + "/" + QString::number(game->getPlayer()->getMaxHealth()));
    ui->playerHealthBar->setValue(getValueForHealth(game->getPlayer()->getHealth(), game->getPlayer()->getMaxHealth()));

    if (!game->isEnemySpawned()) {
        setEnemyVisibility(false);
        generateEnemy();
    }
    if (game->isEnemySpawned()) {
        ui->enemyName->setText(QString::fromStdString(game->getEnemy()->getName()) + " - Level " + QString::number(game->getEnemy()->getLevel()));
        ui->enemyHealth->setText(QString::number(game->getEnemy()->getHealth()) + "/" + QString::number(game->getEnemy()->getMaxHealth()));
        ui->enemyHealthBar->setValue(getValueForHealth(game->getEnemy()->getHealth(), game->getEnemy()->getMaxHealth()));
    }

    ui->healButton->setText("Use healing potion (" + QString::number(game->getPlayer()->getHealPotion()) + ")");

    updateInventory();
}

void MatchWindow::on_dyamicButton_clicked() {
    if (game->isEnemySpawned()) {
        Console::printStd("Attacking");
        if (game->getEnemy()->getsAttacked(game->getPlayer()->attack())) {
            game->enemyDie();
        } else {
            if (game->getPlayer()->getsAttacked(game->getEnemy()->attack())) {
                QtSupport::info("You died!\n\nStats:\n - Level: " + QString::number(game->getPlayer()->getLevel()) +"\n - Experience: " + QString::number(game->getPlayer()->getExperience()));
                MainWindow* main = new MainWindow(nullptr);
                main->show();
                this->close();
            }
        }
    } else {
        Console::printStd("Moving on");
    }

    nextTurn();
}

void MatchWindow::on_inventoryList_clicked(const QModelIndex &index)
{
    ushort row = index.row();
}
