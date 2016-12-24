#ifndef CMDLINE_H
#define CMDLINE_H

#include <QString>
#include <QStringList>

#define COMMAND_NUM 4

class CommandLineInterPreter
{
private:
    void (*commandsFunctions[COMMAND_NUM])(char *);
    char *commands[COMMAND_NUM];

    CommandLineInterPreter();
    void del(QStringList params);
    void add(QStringList params);
    void list(QStringList params);
    void search(QStringList params);

public:
    static CommandLineInterPreter &getInstance();
    void interpreteCommand(QString cmd);
};


#endif // CMDLINE_H
