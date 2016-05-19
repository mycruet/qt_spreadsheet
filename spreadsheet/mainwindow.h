#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
namespace Ui {
class MainWindow;
}
class FindDialog;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    /*
     *The closeEvent() function is a virtual function
     *in QWidget that is automatically called when the
     * user closes the window. It is reimplemented in MainWindow
     *so that we can ask the user the standard question "Do you want to save your changes?"
     *and to save user preferences to disk.
    */
protected:
    void closeEvent(QCloseEvent *event);

private slots:

    void on_actionNew_triggered();

//set up static ui
    void on_actionOpen_triggered();
    bool on_actionSave_triggered();
    bool on_actionSave_as_triggered();

    void on_actionFind_triggered();

    void on_actionDelete_triggered();

    void on_actionGo_to_cell_triggered();

private:
    void createActions();
    void createMenus();
    void createStatusBar();
 //
 private:
    bool  okToContinue();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
//can not be setted up by designer
private:
    QLabel *locationLabel;
    QLabel *formulaLabel;
  //
private:
    QString curFile;
    QStringList recentFiles;
    enum { MaxRecentFiles = 5 };
    QAction *recentFileActions[MaxRecentFiles];
 //other ui
 private:
    FindDialog *findDialog;
};

#endif // MAINWINDOW_H
