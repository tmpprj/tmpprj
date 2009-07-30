#ifndef QROLLFRAME_H
#define QROLLFRAME_H

#include <QFrame>
#include <QPushButton>

class QRollFrame : public QFrame
{
    Q_OBJECT
    QPushButton m_button;

public:
    QRollFrame( QWidget* parent = 0 );

};

#endif
