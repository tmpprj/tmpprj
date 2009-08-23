#ifndef QREGISTERDIALOG_H
#define QREGISTERDIALOG_H

#include <QtGui/QDialog>
#include "asprwrapper.h"

namespace Ui {
    class QRegisterDialog;
}

class QRegisterDialog : public QDialog {
    Q_OBJECT
public:
    QRegisterDialog(QWidget *parent = 0);
    ~QRegisterDialog();

private Q_SLOTS:
    void OnAccept();

protected:
    void changeEvent(QEvent *e);

private:

    Ui::QRegisterDialog *m_ui;
    CAsprWrapper m_Aspr;
};

#endif // QREGISTERDIALOG_H
