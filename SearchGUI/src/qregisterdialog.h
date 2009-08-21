#ifndef QREGISTERDIALOG_H
#define QREGISTERDIALOG_H

#include <QtGui/QDialog>

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
};

#endif // QREGISTERDIALOG_H
