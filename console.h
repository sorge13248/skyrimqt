#ifndef CONSOLE_H
#define CONSOLE_H

#include <QTextStream>

class Console
{
public:
    static void printQ(const QString&, const bool b=true);
    static void printStd(const std::string, const bool b=true);
};

#endif // CONSOLE_H
