#ifndef _QSEARCHWINDOW_H
#define _QSEARCHWINDOW_H

#include <qsearchfacade.h>
#include <QDialog>
#include <QMovie>

#include "ui_searchwindow.h"

class QMovie;

class QSearchWindow : public QDialog, private Ui::SearchWindowBase
{
    Q_OBJECT

    QSearchFacade m_search;
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
    void saveSettings();
    void closing();

    void fileMatched( const QString& strFilename, bool bFound ); 
    void searchDone();

private:
    void setupProgressAnimation();
    void setupControls();
    void connectSearcher();
    void connectWidgets();
    void saveCurrentUIItems();
};

#endif

