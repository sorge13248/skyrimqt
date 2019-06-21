#ifndef MATCHWINDOW_H
#define MATCHWINDOW_H

#include <QWidget>
#include <QDesktopWidget>
#include <QStringListModel>
#include "qtgame.h"
#include "qtsupport.h"
#include "mainwindow.h"
#include "Item/weapon.h"
#include "Item/shield.h"

namespace Ui {
class MatchWindow;
}

class MatchWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MatchWindow(QWidget *parent = 0, string playerName="New player");
    ~MatchWindow();

private slots:
    void on_dyamicButton_clicked();

    void on_inventoryList_clicked(const QModelIndex &index);

    void on_healButton_clicked();

private:
    Ui::MatchWindow *ui;
    Skyrim::QtGame* game;

    void generateEnemy();
    void updatePlayerInfo();
    void nextTurn();
    void setEnemyVisibility(bool);
    ushort getValueForHealth(ushort health, ushort maxHealth);
    void updateInventory();
};

#endif // MATCHWINDOW_H
