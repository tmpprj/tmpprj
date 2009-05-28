#include <QtGui>
#include <QtCore>

#include "window.h"
#include "filestable.h"

QSearchWindow::QSearchWindow(QWidget *parent)
    : QDialog(parent)
{
    browseButton = createButton(tr("&Browse..."), SLOT(browse()));
    findButton = createButton(tr("&Find"), SLOT(find()));

    fileComboBox = createComboBox(tr("*"));
    textComboBox = createComboBox();
    directoryComboBox = createComboBox(QDir::currentPath());

    fileLabel = new QLabel(tr("Named:"));
    textLabel = new QLabel(tr("Containing text:"));
    directoryLabel = new QLabel(tr("In directory:"));
    filesFoundLabel = new QLabel;

    createFilesTable();

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(findButton);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(fileLabel, 0, 0);
    mainLayout->addWidget(fileComboBox, 0, 1, 1, 2);
    mainLayout->addWidget(textLabel, 1, 0);
    mainLayout->addWidget(textComboBox, 1, 1, 1, 2);
    mainLayout->addWidget(directoryLabel, 2, 0);
    mainLayout->addWidget(directoryComboBox, 2, 1);
    mainLayout->addWidget(browseButton, 2, 2);
    mainLayout->addWidget(filesTable, 3, 0, 1, 3);
    mainLayout->addWidget(filesFoundLabel, 4, 0);
    mainLayout->addLayout(buttonsLayout, 5, 0, 1, 3);
    setLayout(mainLayout);

    setWindowTitle(tr("Find Files"));
    resize(700, 300);

    m_search.SigFileMatched().connect( boost::bind( &QSearchWindow::FileMatched, this, _1, _2 ) );
    m_search.SigFileProcessed().connect( boost::bind( &QSearchWindow::FileProcessed, this, _1, _2 ) );
    m_search.SigFileFound().connect( boost::bind( &QSearchWindow::FileFound, this, _1 ) );
}

void QSearchWindow::FileMatched( const std::string& strFilename, bool bMatchOk )
{
    if( bMatchOk )
        filesTable->AddFile( strFilename.c_str() );
}

void QSearchWindow::FileProcessed( const std::string& strFilename, const QString& strFileData )
{
}

void QSearchWindow::FileFound( const std::string& strFilename )
{
}

void QSearchWindow::browse()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                            tr("Find Files"), QDir::currentPath());
    if (!directory.isEmpty()) 
    {
        directoryComboBox->addItem(directory);
        directoryComboBox->setCurrentIndex(directoryComboBox->currentIndex() + 1);
    }
}

void QSearchWindow::find()
{
    m_search.Stop();
    filesTable->ClearList();

    QString fileName = fileComboBox->currentText();
    QString text = textComboBox->currentText();
    QString path = directoryComboBox->currentText();

    PatternsContainer patterns;
    QStringList list = text.split( " ", QString::SkipEmptyParts );

    for( int i = 0; i < list.size(); i++ )
    {
        QString strPattern = list[ i ].trimmed();
        if( strPattern.size() > 0 )
            patterns.push_back( std::string( ( const char* )strPattern.unicode(), strPattern.size() * sizeof( QChar ) ) );
    }

    Masks_t masks;
    QStringList listMasks = fileName.split( ";", QString::SkipEmptyParts );

    for( int i = 0; i < listMasks.size(); i++ )
        masks.push_back( qPrintable( listMasks[ i ].trimmed() ) );

    m_search.Start( qPrintable( path ), patterns, masks );
}

QPushButton *QSearchWindow::createButton(const QString &text, const char *member)
{
    QPushButton *button = new QPushButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

QComboBox *QSearchWindow::createComboBox(const QString &text)
{
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->addItem(text);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return comboBox;
}

void QSearchWindow::createFilesTable()
{
    filesTable = new QFilesTable;
    QStringList labels;
    labels << tr("File Name") << tr("Size");
    filesTable->setHorizontalHeaderLabels(labels);
    filesTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    filesTable->verticalHeader()->hide();
    filesTable->setShowGrid( true );
}

