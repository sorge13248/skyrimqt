#include "inventoryitemwindow.h"
#include "ui_inventoryitem.h"

InventoryItemWindow::InventoryItemWindow(Skyrim::QtGame* g, Skyrim::Item* it, ushort i, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InventoryItem),
    game(g),
    item(it),
    index(i),
    isEquipped(!(g->getPlayer()->equipItem(item, true)))
{
    ui->setupUi(this);

    setWindowTitle(QString::fromStdString(item->getName()));
    ui->nameLabel->setText(QString::fromStdString(item->getName()));
    ui->typeLabel->setText(QString::fromStdString(item->getType()));
    ui->levelLabel->setText(QString::fromStdString("Level: " + std::to_string(item->getLevel())));

    if (auto q = dynamic_cast<Skyrim::Weapon*>(item)) {
        ui->damageShieldLabel->setText(QString::fromStdString("Damage: " + std::to_string(q->getDamage()) + " points"));
    } else if (auto q = dynamic_cast<Skyrim::Shield*>(item)) {
        ui->damageShieldLabel->setText(QString::fromStdString("Absorb: " + std::to_string(q->getAbsorb()) + " points"));
    }

    setEquipped(isEquipped);
}

InventoryItemWindow::~InventoryItemWindow()
{
    delete ui;
}

void InventoryItemWindow::setEquipped(bool b) {
    if (game->getPlayer()->getLevel() < item->getLevel()) {
        FrancescoSorge::QtSupport::error("This gear is too much powerful for your character's level, perhaps you cheated?", "High level gear");
        item->setLevel(game->getPlayer()->getLevel());
    }
    if (b) game->getPlayer()->equipItem(item);
    ui->isEquipped->setVisible(b);
    ui->equipButton->setEnabled(!b);
    ui->dropButton->setEnabled(!b);
}

void InventoryItemWindow::on_equipButton_clicked()
{
    setEquipped(true);
}

void InventoryItemWindow::on_dropButton_clicked()
{
    if (!isEquipped) {
        game->getPlayer()->removeFromInventory(index);
        close();
    }
    else FrancescoSorge::QtSupport::warning("You cannot drop an item that's equipped");
}

void InventoryItemWindow::on_renameButton_clicked()
{
    QString itemName = FrancescoSorge::QtSupport::input(this, "Renaming " + QString::fromStdString(item->getName()), "New item name:");
    if (itemName.isEmpty()) {
        FrancescoSorge::QtSupport::error("Item name is mandatory!");
    } else {
        setWindowTitle(itemName);
        ui->nameLabel->setText(itemName);
        item->setName(itemName.toStdString());
    }
}

void InventoryItemWindow::on_closeButton_clicked()
{
    close();
}
