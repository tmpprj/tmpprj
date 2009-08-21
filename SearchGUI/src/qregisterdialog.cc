#include "qregisterdialog.h"
#include "ui_qregisterdialog.h"
#include <QMessageBox>

#ifdef WIN32
#include "windows.h"
#include "aspr_api.h"
#include "asprotect.h"
#endif

QRegisterDialog::QRegisterDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::QRegisterDialog)
{
    m_ui->setupUi(this);

    connect( m_ui->buttonBox, SIGNAL( accepted() ), this, SLOT( OnAccept() ) );
}

QRegisterDialog::~QRegisterDialog()
{
    delete m_ui;
}

void QRegisterDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void QRegisterDialog::OnAccept()
{
#ifdef WIN32
 if( CheckKeyAndDecrypt( m_ui->keyEdit->text().toLatin1().data(), m_ui->nameEdit->text().toLatin1().data(), TRUE ) )
     QMessageBox::information( this, "Succes", "Your product is now registered" );
 else
     QMessageBox::warning( this, "Error", "Incorrect key or name" );
#endif
}
