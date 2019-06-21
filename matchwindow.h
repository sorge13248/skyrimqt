#ifndef MATCHWINDOW_H
#define MATCHWINDOW_H

#include <QWidget>
#include "qtgame.h"
#include "qtsupport.h"

namespace Ui {
class MatchWindow;
}

class MatchWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MatchWindow(QWidget *parent = 0, const QString& playerName="New player");
    ~MatchWindow();
    void generateEnemy();

private slots:
    void on_dyamicButton_clicked();

private:
    Ui::MatchWindow *ui;
    Skyrim::QtGame* game;
};

#endif // MATCHWINDOW_H
