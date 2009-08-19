#ifndef __Q_ABOUT_DIALOG_H_
#define __Q_ABOUT_DIALOG_H_

#include <QDialog>

#include "ui_aboutdialog.h"

class QAboutDialog: public QDialog, private Ui::AboutDialogBase
{
    Q_OBJECT

    QString m_strHardwareId;

public:
        QAboutDialog( QWidget *parent );
	~QAboutDialog(void);
};

#endif
