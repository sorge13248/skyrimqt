#include "qtsupport.h"

void QtSupport::error(const QString& message, const QString& title, ushort width, ushort height) {
    QMessageBox* messageBox = new QMessageBox();
    messageBox->critical(0, title, message);
    messageBox->setFixedSize(width, height);
}

void QtSupport::info(const QString& message, const QString& title, ushort width, ushort height) {
    QMessageBox* messageBox = new QMessageBox();
    messageBox->information(0, title, message);
    messageBox->setFixedSize(width, height);
}


void QtSupport::warning(const QString& message, const QString& title, ushort width, ushort height) {
    QMessageBox* messageBox = new QMessageBox();
    messageBox->warning(0, title, message);
    messageBox->setFixedSize(width, height);
}

QString QtSupport::input(QWidget* parent, QString title, QString content, QString placeholder) {
    return QInputDialog::getText(parent, title, content, QLineEdit::Normal, placeholder);
}

int QtSupport::dialog(QString title, QString content, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton button) {
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(content);
    msgBox.setStandardButtons(buttons);
    msgBox.setDefaultButton(button);
    return msgBox.exec();
}

QJsonDocument QtSupport::loadJson(QString fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}

void QtSupport::saveJson(QString fileName, QJsonObject object) {
    QJsonDocument document;
    document.setObject(object);
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
}

QStringList QtSupport::getFiles(QDir directory, QStringList filter) {
    return directory.entryList(filter, QDir::Files);
}
