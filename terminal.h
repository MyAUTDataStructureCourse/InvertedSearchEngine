#ifndef TERMINAL_H
#define TERMINAL_H

#include <QPlainTextEdit>

class Terminal
{
private:
    Terminal();
    QPlainTextEdit *terminalOutput;
    void setTheme();

public:
    static Terminal &getInstance();

    void writeLine(QString line);
    void writeError(QString line);

    void setObject(QPlainTextEdit *terminalOutput);
};

#endif // TERMINAL_H
