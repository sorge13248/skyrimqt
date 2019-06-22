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
