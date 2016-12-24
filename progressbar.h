#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H
#include <QProgressBar>
#include <QLineEdit>

class ProgressBar
{
    QProgressBar *progressbarWidget;
    QLineEdit *cmdLindWidget;

    ProgressBar();


public:
    static ProgressBar &getInstance();
    void setProgressBarWidget(QProgressBar *widget);
    void setCommandLineWidget(QLineEdit *widget);
    void toggleToProgressBar();
    void toggleToCMDLine();
};

#endif // PROGRESSBAR_H
