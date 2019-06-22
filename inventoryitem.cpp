#include "inventoryitem.h"
#include "ui_inventoryitem.h"

InventoryItem::InventoryItem(Skyrim::QtGame* g, Skyrim::Item* it, ushort i, QWidget *parent) :
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

InventoryItem::~InventoryItem()
{
    delete ui;
}

void InventoryItem::setEquipped(bool b) {
    if (b) game->getPlayer()->equipItem(item);
    ui->isEquipped->setVisible(b);
    ui->equipButton->setEnabled(!b);
    ui->dropButton->setEnabled(!b);
}

void InventoryItem::on_equipButton_clicked()
{
    setEquipped(true);
}

void InventoryItem::on_dropButton_clicked()
{
    if (!isEquipped) {
        game->getPlayer()->removeFromInventory(index);
        close();
    }
    else QtSupport::warning("You cannot drop an item that's equipped");
}

void InventoryItem::on_renameButton_clicked()
{
    QString itemName = QtSupport::input(this, "Renaming " + QString::fromStdString(item->getName()), "New item name:");
    if (itemName.isEmpty()) {
        QtSupport::error("Item name is mandatory!");
    } else {
        setWindowTitle(itemName);
        ui->nameLabel->setText(itemName);
        item->setName(itemName.toStdString());
    }
}

void InventoryItem::on_closeButton_clicked()
{
    close();
}
