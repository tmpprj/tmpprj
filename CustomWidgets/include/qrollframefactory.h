#ifndef ROLLFRAMEFACTORY_H
#define ROLLFRAMEFACTORY_H

#include <QtDesigner/QExtensionFactory>

QT_BEGIN_NAMESPACE
class QExtensionManager;
QT_END_NAMESPACE

//! [0]
class QRollFrameFactory: public QExtensionFactory
{
    Q_OBJECT

public:
    QRollFrameFactory(QExtensionManager *parent = 0);

protected:
    QObject *createExtension(QObject *object, const QString &iid, QObject *parent) const;
};
//! [0]

#endif
