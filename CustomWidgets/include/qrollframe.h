#ifndef QROLLFRAME_H
#define QROLLFRAME_H

#include <QPushButton>
#include <QComboBox>
#include <QStackedWidget>
#include <QVBoxLayout>

class QRollFrame : public QWidget
{
    Q_OBJECT

    QStackedWidget m_stack;
    QPushButton m_button;

public:
    QRollFrame( QWidget* parent = 0 );

    QWidget* widget( int index );

public Q_SLOTS:
    
   void addPage(QWidget *page);

private Q_SLOTS:

    void buttonPushed();
};

#endif
