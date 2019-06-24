#include "qtsupport.h"

void FrancescoSorge::QtSupport::error(const QString& message, const QString& title, ushort width, ushort height) {
    QMessageBox* messageBox = new QMessageBox();
    messageBox->critical(0, title, message);
    messageBox->setFixedSize(width, height);
}

void FrancescoSorge::QtSupport::info(const QString& message, const QString& title, ushort width, ushort height) {
    QMessageBox* messageBox = new QMessageBox();
    messageBox->information(0, title, message);
    messageBox->setFixedSize(width, height);
}


void FrancescoSorge::QtSupport::warning(const QString& message, const QString& title, ushort width, ushort height) {
    QMessageBox* messageBox = new QMessageBox();
    messageBox->warning(0, title, message);
    messageBox->setFixedSize(width, height);
}

QString FrancescoSorge::QtSupport::input(QWidget* parent, QString title, QString content, QString placeholder) {
    return QInputDialog::getText(parent, title, content, QLineEdit::Normal, placeholder);
}

int FrancescoSorge::QtSupport::dialog(QString title, QString content, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton button) {
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(content);
    msgBox.setStandardButtons(buttons);
    msgBox.setDefaultButton(button);
    return msgBox.exec();
}

QJsonDocument FrancescoSorge::QtSupport::loadJson(QString fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}

void FrancescoSorge::QtSupport::saveJson(QString fileName, QJsonObject object) {
    QJsonDocument document;
    document.setObject(object);
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
}

QStringList FrancescoSorge::QtSupport::getFiles(QDir directory, QStringList filter) {
    return directory.entryList(filter, QDir::Files);
}
