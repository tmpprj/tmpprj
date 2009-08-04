#include "include/qrollframeextension.h"
#include "include/qrollframe.h"
#include <QMessageBox>

QRollFrameExtension::QRollFrameExtension( QRollFrame *widget, QObject *parent)
    :QObject(parent)
{
    myWidget = widget;
}

void QRollFrameExtension::addWidget(QWidget *widget)
{
   myWidget->addPage(widget);
}

int QRollFrameExtension::count() const
{
    return 1;
}

int QRollFrameExtension::currentIndex() const
{
    return 0;
}

void QRollFrameExtension::insertWidget(int index, QWidget *widget)
{
}

void QRollFrameExtension::remove(int index)
{
}

void QRollFrameExtension::setCurrentIndex(int index)
{
}

QWidget* QRollFrameExtension::widget(int index) const
{
    return myWidget->widget(index);
}
