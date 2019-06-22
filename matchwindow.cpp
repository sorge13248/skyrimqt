#include "matchwindow.h"
#include "ui_matchwindow.h"

MatchWindow::MatchWindow(QWidget *parent, const string playerName) :
    QWidget(parent),
    ui(new Ui::MatchWindow),
    game(new Skyrim::QtGame())
{
    ui->setupUi(this);

    const QRect screen = QApplication::desktop()->screenGeometry();
    this->move(screen.center() - this->rect().center());

    game->newGame(playerName);
    setWindowTitle(QString::fromStdString(playerName + " - Skyrim"));

    try {
        game->startMatch();
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
        //bool isEquipped = !(game->getPlayer()->equipItem(*it, true));
        list << QString::fromStdString((*it)->getName() + " (Level " + std::to_string((*it)->getLevel()) + ")");
    }

    model->setStringList(list);
    model->setData(model->index(0,0), QPixmap(":/icons/images/tick.png"), Qt::DecorationRole);
    ui->inventoryList->setModel(model);
}

void MatchWindow::updatePlayerInfo() {
    ui->playerLabel->setText(QString::fromStdString(game->getPlayer()->getName()) + " - Level " + QString::number(game->getPlayer()->getLevel()));
    ui->playerHealth->setText(QString::number(game->getPlayer()->getHealth()) + "/" + QString::number(game->getPlayer()->getMaxHealth()));
    ui->playerHealthBar->setValue(getValueForHealth(game->getPlayer()->getHealth(), game->getPlayer()->getMaxHealth()));

    ui->healButton->setText("Use healing potion (" + QString::number(game->getPlayer()->getHealPotion()) + ")");
}

void MatchWindow::nextTurn() {
    updatePlayerInfo();

    if (!game->isEnemySpawned()) {
        setEnemyVisibility(false);
        generateEnemy();
    }
    if (game->isEnemySpawned()) {
        ui->enemyName->setText(QString::fromStdString(game->getEnemy()->getName()) + " - Level " + QString::number(game->getEnemy()->getLevel()));
        ui->enemyHealth->setText(QString::number(game->getEnemy()->getHealth()) + "/" + QString::number(game->getEnemy()->getMaxHealth()));
        ui->enemyHealthBar->setValue(getValueForHealth(game->getEnemy()->getHealth(), game->getEnemy()->getMaxHealth()));
    }

    updateInventory();
}

void MatchWindow::on_dyamicButton_clicked() {
    if (game->isEnemySpawned()) {
        if (game->getEnemy()->getsAttacked(game->getPlayer()->attack())) {
            game->enemyDie();

            ushort rand = FrancescoSorge::Basic::random(1, 3);
            if (rand == 1 || rand == 2) {
                Skyrim::Item* item;
                if (FrancescoSorge::Basic::random(1, 2) == 1) {
                    item = new Skyrim::Weapon("God Slayer", 10, 20);
                } else {
                    item = new Skyrim::Shield("God S.H.I.E.L.D.", 10, 20);
                }
                if (game->getPlayer()->addToInventory(item) == nullptr) {
                    QtSupport::warning("Your inventory is full. Drop something to free up space. Anyway, you lost the dropped item...");
                }
                updateInventory();
            }
        } else {
            if (game->getPlayer()->getsAttacked(game->getEnemy()->attack())) {
                QtSupport::info("You died!\n\nStats:\n - Level: " + QString::number(game->getPlayer()->getLevel()) +"\n - Experience: " + QString::number(game->getPlayer()->getExperience()));
                MainWindow* main = new MainWindow(nullptr);
                main->show();
                this->close();
            }
        }
    }

    nextTurn();
}

void MatchWindow::on_inventoryList_clicked(const QModelIndex &index)
{
    ushort row = index.row();
    Skyrim::Item* item = game->getPlayer()->getInventory()->getByIndex(row);
    if (item) {
        InventoryItem* inventoryWindow = new InventoryItem(game, item, row, this);
        inventoryWindow->setWindowModality(Qt::WindowModal);
        inventoryWindow->exec();
        updateInventory();
    } else {
        QtSupport::error("Something went wrong and I cannot find the item you're looking for.");
    }
}

void MatchWindow::on_healButton_clicked()
{
    if (game->getPlayer()->getHealPotion() > 0) {
        game->getPlayer()->heals();
        updatePlayerInfo();
    } else {
        QtSupport::warning("You don't have any healing potion.. you're screwed HEHEHEHE");
    }
}
