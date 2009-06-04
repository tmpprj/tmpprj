#ifndef _QSEARCHWINDOW_H
#define _QSEARCHWINDOW_H

#include <searchfacade.h>
#include <QDialog>

#include "ui_searchwindow.h"

class QSearchWindow : public QDialog, private Ui::SearchWindowBase
{
    Q_OBJECT

    CSearchFacade m_search;

public:
    QSearchWindow(QWidget *parent = 0);
    ~QSearchWindow();

private Q_SLOTS:
    void browse();
    void find();
    void stop();
    void showSettings();
    void showJournal();
    void reloadExtensions();
    void reloadSettings();

private:
    void PutCurrentTextsInCombo();
    void SaveSettingsTextCombo();
    void SaveSettingsFoldersCombo();
    
    void FileMatched( const CPatternMatcher::structFindData& );
    void FileProcessed( const CPlainTextExtractor::structFileData& );
    void FileFound( const QString& strFilename );
};

#endif

