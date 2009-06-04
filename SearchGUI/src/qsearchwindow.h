#ifndef _QSEARCHWINDOW_H
#define _QSEARCHWINDOW_H

#include <searchfacade.h>
#include <QDialog>
#include <QMovie>

#include "ui_searchwindow.h"

class QMovie;

class QSearchWindow : public QDialog, private Ui::SearchWindowBase
{
    Q_OBJECT

    CSearchFacade m_search;
    QMovie m_progressMovie;

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
    void closing();

private:
    void PutCurrentTextsInCombo();
    void SaveSettingsTextCombo();
    void SaveSettingsFoldersCombo();
    
    void OnFileMatched( const CPatternMatcher::structFindData& );
    void OnFileProcessed( const CPlainTextExtractor::structFileData& );
    void OnFileFound( const QString& strFilename );
    void OnSearchDone();
};

#endif

