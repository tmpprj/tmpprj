#ifndef _QSETTINGSWINDOW_H
#define _QSETTINGSWINDOW_H

#include <QDialog>

#include "ui_settingswindow.h"

class QSettingsWindow : public QDialog, private Ui::SettingsWindowBase
{
    Q_OBJECT

public:
    QSettingsWindow(QWidget *parent = 0);
};

#endif

