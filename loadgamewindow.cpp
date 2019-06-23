#include "loadgamewindow.h"
#include "ui_loadgamewindow.h"

LoadGameWindow::LoadGameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadGameWindow)
{
    ui->setupUi(this);

    QStringListModel* model = new QStringListModel(this);

    QStringList list;
    foreach(QString filename, QtSupport::getFiles(QDir("."), QStringList() << "*.gamesave" << "*.GAMESAVE")) {
        list << filename.replace(".gamesave", "");
    }

    model->setStringList(list);
    ui->fileListView->setModel(model);
}

LoadGameWindow::~LoadGameWindow()
{
    delete ui;
}

void LoadGameWindow::on_fileListView_clicked(const QModelIndex &index)
{
    MatchWindow* match = new MatchWindow(QtSupport::loadJson(QString::fromStdString("./") + index.data(Qt::DisplayRole).toString() + ".gamesave"));
    match->show();
    this->close();
}
