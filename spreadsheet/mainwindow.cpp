#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QFileInfo>
#include "finddialog.h"
#include "gotocelldialog.h"
#include "sortdialog.h"
#include <QSettings>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    createActions();
    createMenus();
    createContextMenu();
    createStatusBar();
    readSettings();
    findDialog = 0;
    setCurrentFile("");
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

void MainWindow::createContextMenu()
{
#if 0
    spreadsheet->addAction(cutAction);
    spreadsheet->addAction(copyAction);
    spreadsheet->addAction(pasteAction);
    spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
  #endif
    ui->tableWidget->addAction(ui->actionCut);
    ui->tableWidget->addAction(ui->actionCopy);
    ui->tableWidget->addAction(ui->actionPaste);
    ui->tableWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
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

void MainWindow::on_actionSort_triggered()
{
    qDebug("sort....");

    SortDialog dialog(this);
    //QTableWidgetSelectionRange range = spreadsheet->selectedRange();
    //dialog.setColumnRange('A' + range.leftColumn(),  'A' + range.rightColumn());
    if (dialog.exec()) {
#if 0
        SpreadsheetCompare compare;
        compare.keys[0] =
                dialog.primaryColumnCombo->currentIndex();
        compare.keys[1] =
                dialog.secondaryColumnCombo->currentIndex() - 1;
        compare.keys[2] =
                dialog.tertiaryColumnCombo->currentIndex() - 1;
        compare.ascending[0] =
                (dialog.primaryOrderCombo->currentIndex() == 0);
        compare.ascending[1] =
                (dialog.secondaryOrderCombo->currentIndex() == 0);
        compare.ascending[2] =
                (dialog.tertiaryOrderCombo->currentIndex() == 0);
        spreadsheet->sort(compare);
#endif
    }

}

void MainWindow::on_action_about_triggered()
{
    QMessageBox::about(this, tr("About Spreadsheet"),
                tr("<h2>Spreadsheet 1.1</h2>"
                   "<p>Copyright &copy; 2006 Software Inc."
                   "<p>Spreadsheet is a small application that "
                   "demonstrates QAction, QMainWindow, QMenuBar, "
                   "QStatusBar, QTableWidget, QToolBar, and many other "
                   "Qt classes."));

}


void MainWindow::writeSettings()
{
    QSettings settings("Software Inc.", "Spreadsheet");
    settings.setValue("geometry", geometry());
    //settings.setValue("recentFiles", recentFiles);
    settings.setValue("showGrid", ui->actionShowGrid->isChecked());
    settings.setValue("autoRecalc", ui->action_Auto_recalculate->isChecked());
}

void MainWindow::readSettings()
{
    QSettings settings("Software Inc.", "Spreadsheet");
    QRect rect = settings.value("geometry",  QRect(200, 200, 400, 400)).toRect();
    move(rect.topLeft());
    resize(rect.size());
    //recentFiles = settings.value("recentFiles").toStringList();
    //updateRecentFileActions();
    bool showGrid = settings.value("showGrid", true).toBool();
    ui->actionShowGrid->setChecked(showGrid);

    bool autoRecalc = settings.value("autoRecalc", true).toBool();
    ui->action_Auto_recalculate->setChecked(autoRecalc);
}



