#ifndef MATCHWINDOW_H
#define MATCHWINDOW_H

#include <QWidget>
#include <QDesktopWidget>
#include <QStringListModel>
#include <QJsonObject>
#include <QPainter>
#include "qtgame.h"
#include "qtsupport.h"
#include "Item/weapon.h"
#include "Item/shield.h"

#include "mainwindow.h"
#include "inventoryitemwindow.h"

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
    void on_lineEdit_textChanged(const QString&);
    void on_cleanButton_clicked();

private:
    Ui::MatchWindow *ui;
    Skyrim::QtGame* game;
    bool editedFromLastSave;
    QString scene;

    void initialize();
    void generateEnemy();
    void updatePlayerInfo();
    void nextTurn();
    void setEnemyVisibility(bool);
    ushort getValueForHealth(ushort, ushort);
    void updateInventory(const QString& s="");
    void showMainWindow();
    void nextScene(string s="");
};

#endif // MATCHWINDOW_H
