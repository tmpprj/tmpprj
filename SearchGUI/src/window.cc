#include <QtGui>
#include <QtCore>
#include "window.h"

Window::Window(QWidget *parent)
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

    m_search.SigFileMatched().connect( boost::bind( &Window::FileMatched, this, _1, _2 ) );
    m_search.SigFileProcessed().connect( boost::bind( &Window::FileProcessed, this, _1, _2 ) );
    m_search.SigFileFound().connect( boost::bind( &Window::FileFound, this, _1 ) );
}

void Window::AddFile( const QString& filename, size_t nFileSize )
{
    QTableWidgetItem *fileNameItem = new QTableWidgetItem( filename );
    fileNameItem->setFlags(Qt::ItemIsEnabled);
    QTableWidgetItem *sizeItem = new QTableWidgetItem( tr( "%1 KB" )
                              .arg( int( ( nFileSize + 1023) / 1024) ) );
    sizeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    sizeItem->setFlags(Qt::ItemIsEnabled);

    int row = filesTable->rowCount();
    filesTable->insertRow(row);
    filesTable->setItem( row, 0, fileNameItem );
    filesTable->setItem( row, 1, sizeItem );
}

void Window::ClearList()
{
    filesTable->clearContents();
    filesTable->setRowCount( 0 );
}

void Window::FileMatched( const std::string& strFilename, bool bMatchOk )
{
    if( bMatchOk )
        AddFile( strFilename.c_str(), 0 );
}

void Window::FileProcessed( const std::string& strFilename, const QString& strFileData )
{
}

void Window::FileFound( const std::string& strFilename )
{
}

void Window::browse()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                            tr("Find Files"), QDir::currentPath());
    if (!directory.isEmpty()) 
    {
        directoryComboBox->addItem(directory);
        directoryComboBox->setCurrentIndex(directoryComboBox->currentIndex() + 1);
    }
}

void Window::find()
{
    m_search.Stop();
    ClearList();

    QString fileName = fileComboBox->currentText();
    QString text = textComboBox->currentText();
    QString path = directoryComboBox->currentText();

    PatternsContainer patterns;
    QStringList list = text.split( " ", QString::SkipEmptyParts );
    QTextCodec* pTextCodec = QTextCodec::codecForLocale();

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

QPushButton *Window::createButton(const QString &text, const char *member)
{
    QPushButton *button = new QPushButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

QComboBox *Window::createComboBox(const QString &text)
{
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->addItem(text);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return comboBox;
}

void Window::createFilesTable()
{
    filesTable = new QTableWidget(0, 2);
    QStringList labels;
    labels << tr("File Name") << tr("Size");
    filesTable->setHorizontalHeaderLabels(labels);
    filesTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    filesTable->verticalHeader()->hide();
    filesTable->setShowGrid( true );
}

