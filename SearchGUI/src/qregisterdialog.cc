#include "qregisterdialog.h"
#include "ui_qregisterdialog.h"
#include <QMessageBox>

QRegisterDialog::QRegisterDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowContextHelpButtonHint | Qt::Dialog),
    m_ui(new Ui::QRegisterDialog)
{
    m_ui->setupUi(this);

    m_ui->hwidEdit->setText( m_Aspr.GetHwId() );

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
    if( m_Aspr.TryRegiter( m_ui->keyEdit->text(), m_ui->nameEdit->text() ) )
    {
        done( QDialog::Accepted );
        QMessageBox::information( this, "Success", "Your product is now registered" );
    }
    else
    {
        done( QDialog::Rejected );
        QMessageBox::warning( this, "Error", "Incorrect key or name" );
    }
}
