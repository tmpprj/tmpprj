#ifndef _QSEARCHWINDOW_H
#define _QSEARCHWINDOW_H

#include <qsearchfacade.h>
#include <QMainWindow>
#include <QMovie>

#include "ui_searchwindow.h"

class QMovie;

class QSearchWindow : public QMainWindow, private Ui::SearchWindowBase
{
    Q_OBJECT

    QSearchFacade m_search;
    QMovie m_progressMovie;
    QString m_strCurrentFile;
    QTime m_SearchTimerStart;
    time_t m_tTimeElapsed;
    size_t m_stFilesProcessed, m_stFilesMatched;

public:
    QSearchWindow(QWidget *parent = 0);
    ~QSearchWindow();

private Q_SLOTS:
    void browse();
    void find();
    void stop();
    void showSettings();
    void reloadExtensions();
    void reloadSettings();
    void saveSettings();
    void updateTimer();

    void fileProcessing( const QString& strFilename );
    void fileMatched( const QString& strFilename ); 
    void searchStart();
    void searchDone();
    void searchError( const QString& strFilename, const QString& strError );
private:
    void setupProgressAnimation();
    void setupControls();
    void connectSearcher();
    void connectWidgets();
    void startStatusUpdateTimer();
    void showDefaultStatus();
    void showSearchStatus( const QString& strFilename );
    void saveCurrentUIItems();
    void closeEvent( QCloseEvent* );
};

#endif

