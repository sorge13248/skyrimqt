#include "qtsupport.h"

void QtSupport::error(const QString& message, const QString& title, ushort width, ushort height) {
    QMessageBox* messageBox = new QMessageBox();
    messageBox->critical(0, title, message);
    messageBox->setFixedSize(width, height);
}
