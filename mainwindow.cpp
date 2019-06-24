#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->move(screen.center() - this->rect().center());

    QPixmap logo(":/icons/images/logo.png");
    ui->logoLabel->setPixmap(logo);
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
    QString playerName = FrancescoSorge::QtSupport::input(this, "New game - Skyrim", "Player name:");
    if (playerName.isEmpty()) {
        FrancescoSorge::QtSupport::error("Player name is mandatory!");
    } else {
        MatchWindow* game = new MatchWindow(playerName.toStdString());
        game->setWindowModality(Qt::WindowModal);
        game->show();
        this->close();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    bool atLeastOne = false;
    foreach(QString filename, FrancescoSorge::QtSupport::getFiles(QDir("."), QStringList() << "*.gamesave" << "*.GAMESAVE")) {
        atLeastOne = true;
        break;
    }

    if (!atLeastOne) {
        FrancescoSorge::QtSupport::warning("No savegame file found. Files must be in format JSON, with extension .gamesave and they need to be in the same directory as the game.");
    } else {
        LoadGameWindow* loadGameWindow = new LoadGameWindow(nullptr);
        loadGameWindow->show();
        this->close();
    }
}
