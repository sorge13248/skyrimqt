#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    game(new Skyrim::QtGame())
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
        QMessageBox* messageBox = new QMessageBox();
        messageBox->critical(0, "Error", "Player name is mandatory");
        messageBox->setFixedSize(500, 200);
    } else {
        Console::print(playerName);
        game->newGame(playerName);
        game->startMatch();
    }
}
