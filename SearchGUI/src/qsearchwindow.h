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

private Q_SLOTS:
    void browse();
    void find();
    void stop();
    void settings();

    void searchTextChanged();
    void searchDirChanged();

private:
    void LoadSettingsToUi();
    void SaveSettingsCombo( QComboBox* pComboBox, QString paramName );
    void SaveSettingsTextCombo();
    void SaveSettingsFoldersCombo();
    
    void FileMatched( const std::string& strFilename, bool bMatchOk );
    void FileProcessed( const std::string& strFileName, const QString& );
    void FileFound( const std::string& strFilename );
};

#endif

