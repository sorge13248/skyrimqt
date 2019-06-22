#include "console.h"

void Console::printQ(const QString & s, const bool b) {
    QTextStream out(stdout);
    out << s;
    if (b) out << endl;
}

void Console::printStd(const std::string s, const bool b) {
    Console::printQ(QString::fromStdString(s), b);
}
