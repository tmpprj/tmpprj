#ifndef WINDOW_H
#define WINDOW_H

#include <searchfacade.h>
#include <QDialog>

class QComboBox;
class QDir;
class QLabel;
class QPushButton;
class QFilesTable;

class QSearchWindow : public QDialog
{
    Q_OBJECT

    CSearchFacade m_search;

public:
    QSearchWindow(QWidget *parent = 0);

private Q_SLOTS:
    void browse();
    void find();

private:
    void FileMatched( const std::string& strFilename, bool bMatchOk );
    void FileProcessed( const std::string& strFileName, const QString& strFileData );
    void FileFound( const std::string& strFilename );

    QPushButton *createButton(const QString &text, const char *member);
    QComboBox *createComboBox(const QString &text = QString());
    void createFilesTable();

    QComboBox *fileComboBox;
    QComboBox *textComboBox;
    QComboBox *directoryComboBox;
    QLabel *fileLabel;
    QLabel *textLabel;
    QLabel *directoryLabel;
    QLabel *filesFoundLabel;
    QPushButton *browseButton;
    QPushButton *findButton;
    QFilesTable *filesTable;
};

#endif

