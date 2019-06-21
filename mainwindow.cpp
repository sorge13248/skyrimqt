#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_exitButton_clicked()
{
    QCoreApplication::quit(); // Termina l'app
    //this->close(); // Chiude il form
}

void MainWindow::on_newGameButton_clicked()
{
    QString playerName = QInputDialog::getText(this, tr("New game - Skyrim"),
                                             tr("Player name:"), QLineEdit::Normal,
                                             "");
    if (playerName.isEmpty()) {
        QtSupport::error("Player name is mandatory!");
    } else {
        Console::printQ(playerName);
        MatchWindow* game = new MatchWindow(nullptr, playerName);
        game->show();
        this->close();
    }
}
