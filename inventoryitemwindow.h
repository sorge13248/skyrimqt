#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <QDialog>
#include "core.h"
#include "qtsupport.h"
#include "qtgame.h"
#include "Item/item.h"
#include "Item/weapon.h"
#include "Item/shield.h"

namespace Ui {
class InventoryItem;
}

class InventoryItemWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InventoryItemWindow(Skyrim::QtGame*, Skyrim::Item*, ushort, QWidget *parent = 0);
    ~InventoryItemWindow();

private slots:
    void on_equipButton_clicked();
    void on_dropButton_clicked();
    void on_renameButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::InventoryItem *ui;
    Skyrim::QtGame* game;
    Skyrim::Item* item;
    ushort index;
    bool isEquipped;

    void setEquipped(bool);
};

#endif // INVENTORYITEM_H
