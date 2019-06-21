#ifndef MATCHWINDOW_H
#define MATCHWINDOW_H

#include <QWidget>
#include "qtgame.h"
#include "qtsupport.h"
#include "mainwindow.h"

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

private:
    Ui::MatchWindow *ui;
    Skyrim::QtGame* game;

    void generateEnemy();
    void nextTurn();
    void setEnemyVisibility(bool);
    ushort getValueForHealth(ushort health, ushort maxHealth);
};

#endif // MATCHWINDOW_H
