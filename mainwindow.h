#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDesktopWidget>
#include "qtsupport.h"
#include "console.h"
#include "qtgame.h"
#include "matchwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_exitButton_clicked();
    void on_newGameButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
