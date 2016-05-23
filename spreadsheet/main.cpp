#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QtTest/QTest>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
#if 0
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/images/splash.png"));
    splash->show();
    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::tr("Setting up the main window..."),
                        topRight, Qt::red);
    QTest::qSleep(3000);
    MainWindow mainWin;
    splash->showMessage(QObject::tr("Loading modules..."),
                        topRight, Qt::red);
    QTest::qSleep(3000);
    //loadModules();
    splash->showMessage(QObject::tr("Establishing connections..."),
                        topRight, Qt::red);
   // establishConnections();
   mainWin.show();
   splash->finish(&mainWin);
   delete splash;
#endif
  // MainWindow mainWin;
   //mainWin.show();
   MainWindow *mainWin = new MainWindow;
   mainWin->show();
   return app.exec();

}
