#ifndef _QSETTINGSWINDOW_H
#define _QSETTINGSWINDOW_H

#include <QDialog>

#include "ui_settingswindow.h"

class QComboBox;

class QSettingsWindow : public QDialog, private Ui::SettingsWindowBase
{
    Q_OBJECT

    void LoadSettings();
    void SaveSettings();

    void AddExtension( const QString& strExt, const QString& strParser );
    void InitParserCombo( QComboBox* pParserCombo );

Q_SIGNALS:
    void settingsChanged();

private Q_SLOTS:
    void addextension();
    void savesettings();
    void removecurrent();

public:
    QSettingsWindow(QWidget *parent = 0);
};

#endif

