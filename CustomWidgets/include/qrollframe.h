#ifndef QROLLFRAME_H
#define QROLLFRAME_H

#include <QPushButton>
#include <QComboBox>
#include <QStackedWidget>
#include <QVBoxLayout>

class QRollFrame : public QWidget
{
    Q_OBJECT
    Q_PROPERTY( QString ButtonText READ ButtonText WRITE setButtonText )
    Q_PROPERTY( bool Opened READ isOpened WRITE setOpened )

    QStackedWidget m_stack;
    QPushButton m_button;

public:

    QRollFrame( QWidget* parent = 0 );

    QWidget* widget( int index );

    QString ButtonText()
    {
        return m_button.text(); 
    }

    void setButtonText( QString strText )
    { 
        m_button.setText( strText );
    }

    bool isOpened()
    {
        return m_stack.isVisible();
    }

    void setOpened( bool bOpened )
    {
        m_stack.setVisible( bOpened );
    }

public Q_SLOTS:
    
   void addPage(QWidget *page);

private Q_SLOTS:

    void buttonPushed();
};

#endif
