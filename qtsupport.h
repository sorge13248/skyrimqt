#ifndef QTSUPPORT_H
#define QTSUPPORT_H

#include <QMessageBox>
#include <QFile>
#include <QInputDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QStringList>
#include "basic.h"

namespace FrancescoSorge {
    class QtSupport
    {
    public:
        static void error(const QString&, const QString& title="Error", ushort width=400, ushort height=200);
        static void info(const QString&, const QString& title="Info", ushort width=400, ushort height=200);
        static void warning(const QString&, const QString& title="Warning", ushort width=400, ushort height=200);
        static QString input(QWidget*, QString, QString, QString p="");
        static int dialog(QString, QString, QMessageBox::StandardButtons, QMessageBox::StandardButton);
        static QJsonDocument loadJson(QString);
        static void saveJson(QString, QJsonObject);
        static QStringList getFiles(QDir, QStringList);
    };
}

#endif // QTSUPPORT_H
