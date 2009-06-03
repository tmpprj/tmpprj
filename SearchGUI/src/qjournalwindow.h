#ifndef _QJOURNALWINDOW_H
#define _QJOURNALWINDOW_H

#include <QDialog>

#include "ui_journalwindow.h"

class QJournalWindow: public QDialog, private Ui::JournalWindowBase
{
    Q_OBJECT

public:
    QJournalWindow(QWidget *parent = 0);
};

#endif

