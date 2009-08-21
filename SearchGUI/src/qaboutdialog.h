#ifndef __Q_ABOUT_DIALOG_H_
#define __Q_ABOUT_DIALOG_H_

#include <QDialog>

#include "ui_aboutdialog.h"
#include "qregisterdialog.h"
#include "asprwrapper.h"

class QAboutDialog: public QDialog, private Ui::AboutDialogBase
{
    Q_OBJECT

    CAsprWrapper m_Aspr;

    void SetupRegisteredControls();
    void SetupTrialControls();
    void LoadData();
    void RefreshData();
public:

    QAboutDialog( QWidget *parent );
    ~QAboutDialog(void);

private Q_SLOTS:

    void Register();
};

#endif
