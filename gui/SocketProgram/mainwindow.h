#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include "logoutput.h"
#include "global.h"
#include "server.h"
#include "validator.h"
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_DefaultRadioButton_Server_clicked();

    void on_DefaultRadioButton_Client_clicked();

    void on_CustomRadioButton_Server_clicked();

    void on_CustomRadioButton_Client_clicked();

    void on_BrowseXMLButton_clicked();

    void on_StartServerButton_clicked();

    void on_StartClientButton_clicked();

    void on_WriteToClient(QString message);

    void on_WriteToServer(QString message);

private:
    Ui::MainWindow *ui;
    LogOutput logger;
    Server server;
    Validator validator;

    void HideCustomBoxes();
    bool CheckCustomFields(QString type);

};

#endif // MAINWINDOW_H
