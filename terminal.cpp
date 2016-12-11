#include "terminal.h"

Terminal::Terminal()
{

}

Terminal& Terminal::getInstance()
{
    static Terminal instance;

    return instance;
}


void Terminal::writeLine(QString line)
{
    terminalOutput->appendPlainText(line);
}

void Terminal::setObject(QPlainTextEdit *terminalOutput)
{
    this->terminalOutput = terminalOutput;
    setTheme();
}

void Terminal::writeError(QString line)
{
    writeLine(line);
}

void Terminal::setTheme()
{
    QPalette pal;
    QColor bgColor("black");
    QColor fgColor("white");

    pal.setColor(QPalette::Base, bgColor);
    pal.setColor(QPalette::Text, fgColor);

    terminalOutput->setPalette(pal);
}
