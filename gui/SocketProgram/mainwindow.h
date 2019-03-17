#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include "global.h"
#include "server.h"
#include "validator.h"
#include "client.h"
//#include "tests/tests.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void do_UpdateClientText(QString message);

    void do_UpdateServerText(QString message);

    void do_UpdateProgressBar(int value);

private slots:
    void on_DefaultRadioButton_Server_clicked();

    void on_DefaultRadioButton_Client_clicked();

    void on_CustomRadioButton_Server_clicked();

    void on_CustomRadioButton_Client_clicked();

    void on_BrowseXMLButton_clicked();

    void on_StartServerButton_clicked();

    void on_StartClientButton_clicked();

    void on_UnitTestStartButton_clicked();

    void on_UnitTestStopButton_clicked();


private:
    Ui::MainWindow *ui;
    Server server;
    Validator validator;
    //Tests tests;

    void HideCustomBoxes();
    bool CheckCustomFields(QString type);

};

#endif // MAINWINDOW_H
