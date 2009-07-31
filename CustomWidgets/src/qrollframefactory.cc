#include "include/qrollframefactory.h"
#include "include/qrollframeextension.h"
#include "include/qrollframe.h"

QRollFrameFactory::QRollFrameFactory(QExtensionManager *parent)
    : QExtensionFactory(parent)
{}

QObject *QRollFrameFactory::createExtension(QObject *object, const QString &iid, QObject *parent) const
{
    QRollFrame *widget = qobject_cast<QRollFrame*>(object);

    if (widget && (iid == Q_TYPEID(QDesignerContainerExtension))) {
        return new QRollFrameExtension(widget, parent);
    } else {
         return 0;
    }
}
