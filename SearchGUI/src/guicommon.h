#ifndef _GUICOMMON_H_
#define _GUICOMMON_H_

#include <QtGui>

QStringList GetComboStringList( const QComboBox* pComboBox, bool bPutCurrentToTop = false );
void LoadStringListToCombo( QComboBox* pComboBox, const QStringList& list );
void MoveCurrentToTop( QComboBox* pComboBox );
void ParsePatterns( const QString& text, QStringList& listPatterns );

#endif
