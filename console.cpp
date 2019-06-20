#include "console.h"

void Console::print(const QString & s) {
    QTextStream out(stdout);
    out << s << endl;
}
