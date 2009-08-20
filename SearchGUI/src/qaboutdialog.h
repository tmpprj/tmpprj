#ifndef __Q_ABOUT_DIALOG_H_
#define __Q_ABOUT_DIALOG_H_

#include <QDialog>

#include "ui_aboutdialog.h"

class QAboutDialog: public QDialog, private Ui::AboutDialogBase
{
    Q_OBJECT

    QString m_strHardwareId;
    QString m_strRegName;
    bool m_bRegistered;
    size_t m_stDaysTotal, m_stDaysLeft, m_stExTotal, m_stExLeft;

    void SetupRegisteredControls();
    void SetupTrialControls();
    void LoadData();

public:

    QAboutDialog( QWidget *parent );
    ~QAboutDialog(void);

private Q_SLOTS:

    void Register();
};

#endif
