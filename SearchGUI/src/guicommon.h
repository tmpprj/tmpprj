#ifndef _GUICOMMON_H_
#define _GUICOMMON_H_

#include <QtGui>

QStringList GetComboStringList( const QComboBox* pComboBox, bool bPutCurrentToTop = false );
void LoadStringListToCombo( QComboBox* pComboBox, const QStringList& list, const QString& strDefault = "" );
QString FormatExtension( const QString& strExt );
void MoveCurrentToTop( QComboBox* pComboBox );
void ParsePatterns( const QString& strText, QStringList& listPatterns );
void ParseMasks( const QString& strMasks, QStringList& listMasks );

#endif
