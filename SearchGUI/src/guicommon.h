#ifndef _GUICOMMON_H_
#define _GUICOMMON_H_

#include <QtGui>

QString FormatExtension( const QString& strExt );
void ParsePatterns( const QString& strText, QStringList& listPatterns );
void ParseMasks( const QString& strMasks, QStringList& listMasks );

#endif
