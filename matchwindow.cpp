#include "matchwindow.h"
#include "ui_matchwindow.h"

MatchWindow::MatchWindow(const string playerName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatchWindow),
    game(new Skyrim::QtGame()),
    editedFromLastSave(true)
{
    game->newGame(playerName);
    initialize();

    Skyrim::Weapon* sword = new Skyrim::Weapon("Iron Sword");
    Skyrim::Shield* shield = new Skyrim::Shield("Iron Shield");

    game->playerEquipItem(sword);
    game->playerEquipItem(shield);

    game->getPlayer()->addToInventory(sword);
    game->getPlayer()->addToInventory(shield);

    nextTurn();
}

MatchWindow::MatchWindow(QJsonDocument json, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatchWindow),
    game(new Skyrim::QtGame()),
    editedFromLastSave(false)
{
    QVariantMap map = json.object().toVariantMap();

    game->loadGame(map.value("name").toString().toStdString(), map.value("health").toUInt(), map.value("experience").toUInt(), map.value("level").toUInt(), map.value("healPotion").toUInt());
    initialize();

    if (map.contains("enemy")) {
        auto enemy = map.value("enemy").toMap();
        string enemyType = enemy.value("name").toString().toStdString();
        Skyrim::Enemy* enemyPtr;

        if (enemyType == "Raider [BOSS]") {
            enemyPtr = new Skyrim::RaiderBoss(enemy.value("level").toUInt());
        } else if (enemyType == "Raider") {
            enemyPtr = new Skyrim::Raider(enemy.value("level").toUInt());
        } else if (enemyType == "Ghost") {
            enemyPtr = new Skyrim::Ghost(enemy.value("level").toUInt());
        } else {
            enemyPtr = new Skyrim::Animal(enemy.value("level").toUInt());
        }

        game->setEnemy(enemyPtr);
        game->getEnemy()->setMaxHealth(enemy.value("maxHealth").toUInt());
        game->getEnemy()->setHealth(enemy.value("health").toUInt());
        generateEnemy();
    }

    auto inventory = map.value("inventory").toMap();
    for (auto it = inventory.constBegin(); it != inventory.constEnd(); ++it) {
        Skyrim::Item* item = 0;
        auto itemMap = it.value().toMap();

        if (itemMap.value("type") == "Weapon") {
            item = new Skyrim::Weapon(itemMap.value("name").toString().toStdString(), itemMap.value("level").toUInt(), itemMap.value("points").toUInt());
        } else if (itemMap.value("type") == "Shield") {
            item = new Skyrim::Shield(itemMap.value("name").toString().toStdString(), itemMap.value("level").toUInt(), itemMap.value("points").toUInt());
        }

        if(itemMap.value("equipped").toBool()) game->getPlayer()->equipItem(item);
        game->getPlayer()->addToInventory(item);
    }

    nextTurn();
    nextScene(map.value("scene").toString().toStdString());
}

void MatchWindow::initialize() {
    ui->setupUi(this);

    const QRect screen = QApplication::desktop()->screenGeometry();
    this->move(screen.center() - this->rect().center());

    setWindowTitle(QString::fromStdString(game->getPlayer()->getName() + " - Skyrim"));

    try {
        game->startMatch();
    } catch(Skyrim::NoPlayerLoaded) {
        FrancescoSorge::QtSupport::error("No player loaded. Something went wrong.");
        showMainWindow();
        this->close();
    }
}

MatchWindow::~MatchWindow()
{
    delete ui;
}

void MatchWindow::generateEnemy() {
    if (!game->isEnemySpawned()) {
        ushort rand = FrancescoSorge::Basic::random(0, 15);
        Skyrim::Enemy* enemy = 0;

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
    }

    if (game->isEnemySpawned()) {
        ui->dyamicButton->setText("Attack!");
        setEnemyVisibility(true);
    } else {
        ui->dyamicButton->setText("Move on");
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

void MatchWindow::updateInventory(const QString& text) {
    editedFromLastSave = true;

    ui->inventoryLabel->setText("Inventory (" + QString::number(game->getPlayer()->getInventory()->getCount()) + "/" + QString::number(game->getPlayer()->getMaxInventory()) + "):");

    QStringListModel* model = new QStringListModel(this);

    QStringList list;
    for (FrancescoSorge::QContainer<Skyrim::Item*>::constiterator it = game->getPlayer()->getInventory()->begin(); it != game->getPlayer()->getInventory()->end(); ++it) {
        if (text.isEmpty() || ((!text.isEmpty() && QString::fromStdString((*it)->getName()).contains(text, Qt::CaseInsensitive)) || (!text.isEmpty() && QString::fromStdString("Level " + std::to_string((*it)->getLevel())).contains(text, Qt::CaseInsensitive)))) {
            list << QString::fromStdString((*it)->getName() + " (Level " + std::to_string((*it)->getLevel()) + ")");
        }
    }

    model->setStringList(list);
    ui->inventoryList->setModel(model);

    ui->weaponImage->setPixmap(QPixmap(QString::fromStdString(game->getPlayer()->getWeapon()->getImage())));
    ui->shieldImage->setPixmap(QPixmap(QString::fromStdString(game->getPlayer()->getShield()->getImage())));
}

void MatchWindow::updatePlayerInfo() {
    ui->playerLabel->setText(QString::fromStdString(game->getPlayer()->getName()) + " - Level " + QString::number(game->getPlayer()->getLevel()));
    ui->playerHealth->setText(QString::number(game->getPlayer()->getHealth()) + "/" + QString::number(game->getPlayer()->getMaxHealth()));
    ui->playerHealthBar->setValue(getValueForHealth(game->getPlayer()->getHealth(), game->getPlayer()->getMaxHealth()));

    ui->healButton->setText("Use healing potion (" + QString::number(game->getPlayer()->getHealPotion()) + ")");
}

void MatchWindow::nextScene(string scene) {
    QString selectedScene = scene.empty() ? game->scenes.at(FrancescoSorge::Basic::random(0, game->scenes.size() - 1)) : QString::fromStdString(scene);
    QPixmap *pixmap = new QPixmap(600, 300);
    pixmap->fill(Qt::transparent);
    QPainter *painter = new QPainter(pixmap);
    painter->drawPixmap(0, 0, 600, 300, QPixmap(selectedScene));
    if (game->isEnemySpawned()) {
        painter->drawPixmap(350, 120, 220, 160, QPixmap(QString::fromStdString(game->getEnemy()->getImage())));
    }
    painter->end();

    ui->sceneLabel->setPixmap(*pixmap);
    this->scene = selectedScene;
    delete painter;
}

void MatchWindow::nextTurn() {
    updatePlayerInfo();

    if (!game->isEnemySpawned()) {
        setEnemyVisibility(false);
        generateEnemy();
        nextScene();
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
            if (rand == 1) {
                Skyrim::Item* item;
                if (FrancescoSorge::Basic::random(1, 2) == 1) {
                    item = new Skyrim::Weapon(game->weapons.at(FrancescoSorge::Basic::random(0, game->weapons.size()-1)).toStdString(), FrancescoSorge::Basic::random(1, game->getPlayer()->getLevel()), FrancescoSorge::Basic::random(5, 50));
                } else {
                    item = new Skyrim::Shield(game->shields.at(FrancescoSorge::Basic::random(0, game->shields.size()-1)).toStdString(), FrancescoSorge::Basic::random(1, game->getPlayer()->getLevel()), FrancescoSorge::Basic::random(5, 30));
                }

                string damageAbsorb = "";
                if (auto q = dynamic_cast<Skyrim::Weapon*>(item)) {
                    damageAbsorb = "Damage: " + std::to_string(q->getDamage()) + " points";
                } else if (auto q = dynamic_cast<Skyrim::Shield*>(item)) {
                    damageAbsorb = "Absorb: " + std::to_string(q->getAbsorb()) + " points";
                }

                if (FrancescoSorge::QtSupport::dialog("Item dropped by enemy", QString::fromStdString(item->getName() + " (Level " + std::to_string(item->getLevel()) + ")\nType: " + item->getType() + "\n" + damageAbsorb) + "\n\nWould you like to keep it?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
                    if (game->getPlayer()->addToInventory(item) == 0) {
                        FrancescoSorge::QtSupport::warning("Your inventory is full. Drop something to free up space. Anyway, you lost the dropped item...");
                    } else {
                        updateInventory();
                    }
                }
            }
        } else {
            if (game->getPlayer()->getsAttacked(game->getEnemy()->attack())) {
                FrancescoSorge::QtSupport::info("You died!\n\nStats:\n - Level: " + QString::number(game->getPlayer()->getLevel()) +"\n - Experience: " + QString::number(game->getPlayer()->getExperience()));
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
        InventoryItemWindow* inventoryWindow = new InventoryItemWindow(game, item, row, this);
        inventoryWindow->setWindowModality(Qt::WindowModal);
        inventoryWindow->exec();
        updateInventory();
    } else {
        FrancescoSorge::QtSupport::error("Something went wrong and I cannot find the item you're looking for.");
    }
}

void MatchWindow::on_healButton_clicked()
{
    if (game->getPlayer()->getHealPotion() > 0) {
        game->getPlayer()->heals();
        updatePlayerInfo();
    } else {
        FrancescoSorge::QtSupport::warning("You don't have any healing potion.. you're screwed HEHEHEHE");
    }
}

void MatchWindow::on_exitButton_clicked()
{
    bool close = true;
    if (editedFromLastSave) {
        switch (FrancescoSorge::QtSupport::dialog("Game not saved", "Would you like to save the game before exiting?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save)) {
            case QMessageBox::Save:
                on_saveButton_clicked();
                break;
            case QMessageBox::Cancel:
                close = false;
                break;
        }
    }

    if (close) {
        showMainWindow();
        this->close();
    }
}

void MatchWindow::showMainWindow() {
    MainWindow* main = new MainWindow(0);
    main->show();
}

void MatchWindow::on_saveButton_clicked()
{
    editedFromLastSave = false;

    QVariantMap map;
    map.insert("name", QString::fromStdString(game->getPlayer()->getName()));
    map.insert("level", game->getPlayer()->getLevel());
    map.insert("health", game->getPlayer()->getHealth());
    map.insert("experience", game->getPlayer()->getExperience());
    map.insert("healPotion", game->getPlayer()->getHealPotion());
    map.insert("scene", this->scene);
    if (game->isEnemySpawned()) {
        QVariantMap enemy;
        enemy.insert("name", QString::fromStdString(game->getEnemy()->getName()));
        enemy.insert("level", game->getEnemy()->getLevel());
        enemy.insert("health", game->getEnemy()->getHealth());
        enemy.insert("maxHealth", game->getEnemy()->getMaxHealth() / game->getEnemy()->getLevel());

        map.insert("enemy", enemy);
    }
    QVariantMap inventory;
    ushort i = 0;
    for(auto it = game->getPlayer()->getInventory()->begin(); it != game->getPlayer()->getInventory()->end(); ++it) {
        if (*it != 0) {
            QVariantMap item;
            item.insert("name", QString::fromStdString((*it)->getName()));
            item.insert("type", QString::fromStdString((*it)->getType()));
            item.insert("level", (*it)->getLevel());
            if (auto q = dynamic_cast<Skyrim::Weapon*>(*it)) {
                item.insert("points", q->getDamage());
            } else if (auto q = dynamic_cast<Skyrim::Shield*>(*it)) {
                item.insert("points", q->getAbsorb());
            }
            item.insert("equipped", !(game->getPlayer()->equipItem(*it, true)));
            inventory.insert(QString::number(i++), item);
        }
    }
    map.insert("inventory", inventory);
    QJsonObject object = QJsonObject::fromVariantMap(map);

    FrancescoSorge::QtSupport::saveJson("./" + QString::fromStdString(game->getPlayer()->getName()) + ".gamesave", object);
}

void MatchWindow::on_lineEdit_textChanged(const QString &text)
{
    if (text.isEmpty()) {
        updateInventory();
    } else {
        updateInventory(text);
    }
}

void MatchWindow::on_cleanButton_clicked()
{
    if (FrancescoSorge::QtSupport::dialog("Clean inventory", "This action will remove every item below your level (except those equipped). Would you like to continue?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes) {

            ushort index = 0;
            QStringList indexesToRemove;
            for (auto it = game->getPlayer()->getInventory()->begin(); it != game->getPlayer()->getInventory()->end(); ++it) {
                if (game->getPlayer()->equipItem(*it, true) && (*it)->getLevel() < game->getPlayer()->getLevel()) {
                    editedFromLastSave = true;
                    indexesToRemove << QString::number(index);
                }
                index++;
            }
            for (QString index : indexesToRemove) {
                game->getPlayer()->getInventory()->remove(index.toUInt());
            }
            if (editedFromLastSave) updateInventory(ui->lineEdit->text());
        }
}
