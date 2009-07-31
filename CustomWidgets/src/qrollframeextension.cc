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
//    QMessageBox::warning( NULL, "test", "count" );
    return 1;// myWidget->count();
}

int QRollFrameExtension::currentIndex() const
{
//    QMessageBox::warning( NULL, "test", "currentindex" );
    return 0;//myWidget->currentIndex();
}

void QRollFrameExtension::insertWidget(int index, QWidget *widget)
{
//    QMessageBox::warning( NULL, "test", "insertw" );
    //myWidget->insertPage(index, widget);
}

void QRollFrameExtension::remove(int index)
{
//    QMessageBox::warning( NULL, "test", "remove" );
    //myWidget->removePage(index);
}

void QRollFrameExtension::setCurrentIndex(int index)
{
//    QMessageBox::warning( NULL, "test", "setindex" );
    //myWidget->setCurrentIndex(index);
}

QWidget* QRollFrameExtension::widget(int index) const
{
//    QMessageBox::warning( NULL, "test", "widget" );
    return myWidget->widget(index);
}
