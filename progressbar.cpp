#include "progressbar.h"

ProgressBar::ProgressBar()
{

}

ProgressBar &ProgressBar::getInstance()
{
    static ProgressBar instance;

    return instance;
}

void ProgressBar::setProgressBarWidget(QProgressBar *widget)
{
    this->progressbarWidget = widget;
}

void ProgressBar::setCommandLineWidget(QLineEdit *widget)
{
    this->cmdLindWidget = widget;
}

void ProgressBar::toggleToProgressBar()
{
    cmdLindWidget->setVisible(false);
    progressbarWidget->setVisible(true);
}

void ProgressBar::toggleToCMDLine()
{
    cmdLindWidget->setVisible(true);
    progressbarWidget->setVisible(false);
}
