#ifndef _GUICOMMON_H_
#define _GUICOMMON_H_

#include <QtGui>

QStringList GetComboStringList( const QComboBox* pComboBox );
bool TextExistInCombo( const QComboBox* pComboBox, const QString& str );
void ComboInsertCurrentToTop( QComboBox* pComboBox );

#endif
