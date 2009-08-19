#include <QtDesigner/QExtensionFactory>
#include <QtDesigner/QExtensionManager>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QDesignerFormWindowInterface>
#include <QtDesigner/QDesignerContainerExtension>
#include <QtDesigner/QDesignerPropertySheetExtension>

#include <QIcon>
#include <QtPlugin>

#include "qrollframefactory.h"
#include "qrollframeplugin.h"
#include "qrollframe.h"

QRollFramePlugin::QRollFramePlugin()
{
    m_bInitialized = false;
}

bool QRollFramePlugin::isContainer() const
{
    return true;
}

bool QRollFramePlugin::isInitialized() const
{
    return m_bInitialized;
}

QIcon QRollFramePlugin::icon() const
{
    return QIcon();
}

QString QRollFramePlugin::domXml() const
{
     return "<ui language=\"c++\">\n"
            " <widget class=\"QRollFrame\" name=\"rollFrame\">\n"
            "  <widget class=\"QWidget\" name=\"page\" />\n"
            " </widget>\n"
            " <customwidgets>\n"
            "   <customwidget>\n"
            "   <class>QRollFrame</class>\n"
            "   <extends>QWidget</extends>\n"
            "   <addpagemethod>addPage</addpagemethod>\n"
            "  </customwidget>\n"
            " </customwidgets>\n"
            "</ui>\n";
}

QString QRollFramePlugin::group() const
{
    return "Containers";
}

QString QRollFramePlugin::includeFile() const
{
    return "qrollframe.h";
}

QString QRollFramePlugin::name() const
{
    return "QRollFrame";
}

QString QRollFramePlugin::toolTip() const
{
    return "";
}

QString QRollFramePlugin::whatsThis() const
{
    return "";
}

QWidget *QRollFramePlugin::createWidget(QWidget *parent)
{
    return new QRollFrame( parent );
}

void QRollFramePlugin::initialize(QDesignerFormEditorInterface *formEditor)
{
    if( m_bInitialized )
        return;

    QExtensionManager *manager = formEditor->extensionManager();
    QExtensionFactory *factory = new QRollFrameFactory(manager);

    Q_ASSERT(manager != 0);
    manager->registerExtensions( factory, Q_TYPEID(QDesignerContainerExtension) );

    m_bInitialized = true;
}

Q_EXPORT_PLUGIN2(RollFrame_1, QRollFramePlugin)
