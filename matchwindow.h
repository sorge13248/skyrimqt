#ifndef MATCHWINDOW_H
#define MATCHWINDOW_H

#include <QWidget>
#include <QDesktopWidget>
#include <QStringListModel>
#include <QJsonObject>
#include "qtgame.h"
#include "qtsupport.h"
#include "Item/weapon.h"
#include "Item/shield.h"

#include "mainwindow.h"
#include "inventoryitem.h"

namespace Ui {
class MatchWindow;
}

class MatchWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MatchWindow(string, QWidget *parent = 0);
    explicit MatchWindow(QJsonDocument, QWidget *parent = 0);
    ~MatchWindow();

private slots:
    void on_dyamicButton_clicked();
    void on_inventoryList_clicked(const QModelIndex&);
    void on_healButton_clicked();

    void on_exitButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::MatchWindow *ui;
    Skyrim::QtGame* game;
    bool editedFromLastSave;

    void initialize();
    void generateEnemy();
    void updatePlayerInfo();
    void nextTurn();
    void setEnemyVisibility(bool);
    ushort getValueForHealth(ushort, ushort);
    void updateInventory();
    void showMainWindow();
};

#endif // MATCHWINDOW_H
