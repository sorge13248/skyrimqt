#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->move(screen.center() - this->rect().center());
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
    QString playerName = QtSupport::input(this, "New game - Skyrim", "Player name:");
    if (playerName.isEmpty()) {
        QtSupport::error("Player name is mandatory!");
    } else {
        MatchWindow* game = new MatchWindow(nullptr, playerName.toStdString());
        game->setWindowModality(Qt::WindowModal);
        game->show();
        this->close();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    foreach(QString filename, QtSupport::listFiles(QDir("."), QStringList() << "*.json" << "*.JSON")) {
        Console::printQ(filename);
    }
}
