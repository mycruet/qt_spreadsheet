#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QFileInfo>
#include "finddialog.h"
#include "gotocelldialog.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();
    createStatusBar();

    findDialog = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug("close event");

    if (okToContinue()) {
            //writeSettings();
            event->accept();
        } else {
            event->ignore();
        }
}

bool MainWindow::okToContinue()
{
    //if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("Spreadsheet"),
                        tr("The document has been modified.\n"
                           "Do you want to save your changes?"),
                        QMessageBox::Yes | QMessageBox::Default,
                        QMessageBox::No,
                        QMessageBox::Cancel | QMessageBox::Escape);
        if (r == QMessageBox::Yes) {
            return on_actionSave_triggered();
        } else if (r == QMessageBox::Cancel) {
            return false;
        }
   // }
   return true;
}


void MainWindow::on_actionNew_triggered()
{
    qDebug("new file");
    if (okToContinue()) {
           //spreadsheet->clear();
           //setCurrentFile("");
       }

}
void MainWindow::createActions()
{

    //this can not be set up using designer

    /*
    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()),
                this, SLOT(openRecentFile()));
    }
    */

     connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
     connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_triggered()));
     connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(on_actionSave_as_triggered()));
}

void MainWindow::createMenus()
{

    ui->menu_select->addAction(ui->actionRow);
    ui->menu_select->addAction(ui->actionColum);
    ui->menu_select->addAction(ui->actionAll);
}
void MainWindow::createStatusBar()
{

    locationLabel = new QLabel(" W999 ");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());
    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);
    ui->statusBar->addWidget(locationLabel);
    ui->statusBar->addWidget(formulaLabel, 1);
/*
    connect(spreadsheet, SIGNAL(currentCellChanged(int, int, int, int)),
               this, SLOT(updateStatusBar()));
       connect(spreadsheet, SIGNAL(modified()),
               this, SLOT(spreadsheetModified()));
       updateStatusBar();
    */



}


bool MainWindow::loadFile(const QString &fileName)
{
#if 0
    if (!spreadsheet->readFile(fileName)) {
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
    }
    setCurrentFile(fileName);
 #endif
    ui->statusBar->showMessage(tr("File loaded"), 2000);
    return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
#if 0
    if (!spreadsheet->writeFile(fileName)) {
        statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
    }
    setCurrentFile(fileName);
#endif
    ui->statusBar->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);
    QString shownName = "Untitled";
    if (!curFile.isEmpty()) {
           shownName = QFileInfo(curFile).fileName();
        //recentFiles.removeAll(curFile);
       // recentFiles.prepend(curFile);
        //updateRecentFileActions();
    }
    setWindowTitle(tr("%1[*] - %2").arg(shownName)
                   .arg(tr("Spreadsheet")));
}


void MainWindow::on_actionOpen_triggered()
{
     qDebug("open file");
     if (okToContinue()) {
             QString fileName = QFileDialog::getOpenFileName(this,
                                        tr("Open Spreadsheet"), ".",
                                                             tr("Spreadsheet files (*.sp)\n"
                                                                "Comma-separated values files (*.csv)\n"
                                                                "Lotus 1-2-3 files (*.wk1 *.wks)")

                                      );
             if (!fileName.isEmpty())
             {
                loadFile(fileName);
             }
         }

}


bool MainWindow::on_actionSave_triggered()
{
    if (curFile.isEmpty()) {
        return on_actionSave_as_triggered();
    } else {
        return saveFile(curFile);
    }

}

bool  MainWindow::on_actionSave_as_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Spreadsheet"), ".",
                                                    tr("Spreadsheet files (*.sp)"));
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);

}

void MainWindow::on_actionFind_triggered()
{
    if (!findDialog) {
            findDialog = new FindDialog(this);
#if 0
            connect(findDialog, SIGNAL (findNext(const QString &,
                                                Qt::CaseSensitivity)),
                    spreadsheet, SLOT (findNext(const QString &,
                                                Qt::CaseSensitivity)));
            connect(findDialog, SIGNAL(findPrevious(const QString &,
                                                    Qt::CaseSensitivity)),
                     spreadsheet, SLOT(findPrevious(const QString &,
                                                    Qt::CaseSensitivity)));

  #endif
    }
    findDialog->show();
    findDialog->activateWindow();

}

void MainWindow::on_actionDelete_triggered()
{
    qDebug("delet file");
}

void MainWindow::on_actionGo_to_cell_triggered()
{
    GoToCellDialog dialog(this);

    if (dialog.exec()) {

        QString str = dialog.getlineEdit().toUpper();
        qDebug("go to cell [%d,%d]", str.mid(1).toInt() - 1, str[0].unicode() - 'A');
        //spreadsheet->setCurrentCell(str.mid(1).toInt() - 1,  str[0].unicode() - 'A');
    }

}
