#ifndef QCOMBOBOXEXT_H
#define QCOMBOBOXEXT_H

#include <QComboBox>

class QComboBoxExt : public QComboBox
{
    Q_OBJECT

    QPalette m_palDefault, m_palTooltip;
    QString m_strDefault;
    QString m_strHiddenText;

    void CheckEmptyText();
    void focusInEvent( QFocusEvent * event );
    void focusOutEvent( QFocusEvent * event );

public:
    QComboBoxExt( QWidget* parent = 0 );
    void PushTextToList( const QString& str );
    void PushCurrentToList();
    QStringList GetElements();
    QStringList GetFullElements();
    void SetFullElements( const QStringList& list );
    void SetDefaultElement( const QString& strDefault );

    QString GetCurrentText();

public Q_SLOTS:
    void setDisabled( bool disable );

private Q_SLOTS:
    void textChanged();
};

#endif
