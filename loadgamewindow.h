#ifndef LOADGAMEWINDOW_H
#define LOADGAMEWINDOW_H

#include <QDialog>
#include <QDir>
#include <QStringList>
#include <QStringListModel>
#include "core.h"
#include "qtsupport.h"
#include "console.h"

#include "matchwindow.h"

namespace Ui {
class LoadGameWindow;
}

class LoadGameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoadGameWindow(QWidget *parent = 0);
    ~LoadGameWindow();

private slots:
    void on_fileListView_clicked(const QModelIndex &index);

private:
    Ui::LoadGameWindow *ui;
};

#endif // LOADGAMEWINDOW_H
