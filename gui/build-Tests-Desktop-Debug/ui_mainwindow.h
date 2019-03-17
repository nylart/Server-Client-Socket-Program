/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *Tabs;
    QWidget *ServerTab;
    QGroupBox *DesiredConnectionBox;
    QRadioButton *DefaultRadioButton_Server;
    QRadioButton *CustomRadioButton_Server;
    QLineEdit *IPAddressBox_Server;
    QLineEdit *PortBox_Server;
    QPushButton *StartServerButton;
    QScrollArea *ScrollArea_Server;
    QWidget *scrollAreaWidgetContents_2;
    QTextEdit *TextArea_Server;
    QWidget *ClientTab;
    QGroupBox *DesiredConnection_Client;
    QRadioButton *DefaultRadioButton_Client;
    QRadioButton *CustomRadioButton_Client;
    QLineEdit *IPAddressBox_Client;
    QLineEdit *PortBox_Client;
    QPushButton *StartClientButton;
    QScrollArea *ScrollArea_Client;
    QWidget *scrollAreaWidgetContents_3;
    QTextEdit *TextArea_Client;
    QGroupBox *SendXMLArea;
    QPushButton *BrowseXMLButton;
    QLineEdit *xmlFileNameBox;
    QWidget *tab;
    QPushButton *UnitTestStartButton;
    QPushButton *UnitTestStopButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QTextEdit *UnitTestTextArea;
    QProgressBar *UnitTestProgressBar;
    QMenuBar *menuBar;
    QMenu *menuKonami_Socket_Program;
    QMenu *menuv1;
    QMenu *menu_Tralyn_Le;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(740, 465);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Tabs = new QTabWidget(centralWidget);
        Tabs->setObjectName(QStringLiteral("Tabs"));
        Tabs->setGeometry(QRect(10, 10, 721, 401));
        ServerTab = new QWidget();
        ServerTab->setObjectName(QStringLiteral("ServerTab"));
        DesiredConnectionBox = new QGroupBox(ServerTab);
        DesiredConnectionBox->setObjectName(QStringLiteral("DesiredConnectionBox"));
        DesiredConnectionBox->setGeometry(QRect(10, 10, 181, 151));
        DefaultRadioButton_Server = new QRadioButton(DesiredConnectionBox);
        DefaultRadioButton_Server->setObjectName(QStringLiteral("DefaultRadioButton_Server"));
        DefaultRadioButton_Server->setGeometry(QRect(10, 30, 161, 23));
        DefaultRadioButton_Server->setChecked(true);
        CustomRadioButton_Server = new QRadioButton(DesiredConnectionBox);
        CustomRadioButton_Server->setObjectName(QStringLiteral("CustomRadioButton_Server"));
        CustomRadioButton_Server->setGeometry(QRect(10, 60, 112, 23));
        IPAddressBox_Server = new QLineEdit(DesiredConnectionBox);
        IPAddressBox_Server->setObjectName(QStringLiteral("IPAddressBox_Server"));
        IPAddressBox_Server->setEnabled(true);
        IPAddressBox_Server->setGeometry(QRect(10, 90, 161, 25));
        PortBox_Server = new QLineEdit(DesiredConnectionBox);
        PortBox_Server->setObjectName(QStringLiteral("PortBox_Server"));
        PortBox_Server->setEnabled(true);
        PortBox_Server->setGeometry(QRect(10, 120, 161, 25));
        StartServerButton = new QPushButton(ServerTab);
        StartServerButton->setObjectName(QStringLiteral("StartServerButton"));
        StartServerButton->setGeometry(QRect(10, 330, 89, 25));
        ScrollArea_Server = new QScrollArea(ServerTab);
        ScrollArea_Server->setObjectName(QStringLiteral("ScrollArea_Server"));
        ScrollArea_Server->setGeometry(QRect(200, 10, 511, 351));
        ScrollArea_Server->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 509, 349));
        TextArea_Server = new QTextEdit(scrollAreaWidgetContents_2);
        TextArea_Server->setObjectName(QStringLiteral("TextArea_Server"));
        TextArea_Server->setGeometry(QRect(0, -1, 511, 351));
        TextArea_Server->setReadOnly(false);
        TextArea_Server->setTextInteractionFlags(Qt::TextEditorInteraction);
        ScrollArea_Server->setWidget(scrollAreaWidgetContents_2);
        Tabs->addTab(ServerTab, QString());
        ClientTab = new QWidget();
        ClientTab->setObjectName(QStringLiteral("ClientTab"));
        DesiredConnection_Client = new QGroupBox(ClientTab);
        DesiredConnection_Client->setObjectName(QStringLiteral("DesiredConnection_Client"));
        DesiredConnection_Client->setGeometry(QRect(10, 10, 181, 151));
        DefaultRadioButton_Client = new QRadioButton(DesiredConnection_Client);
        DefaultRadioButton_Client->setObjectName(QStringLiteral("DefaultRadioButton_Client"));
        DefaultRadioButton_Client->setGeometry(QRect(10, 30, 161, 23));
        DefaultRadioButton_Client->setChecked(true);
        CustomRadioButton_Client = new QRadioButton(DesiredConnection_Client);
        CustomRadioButton_Client->setObjectName(QStringLiteral("CustomRadioButton_Client"));
        CustomRadioButton_Client->setGeometry(QRect(10, 60, 112, 23));
        IPAddressBox_Client = new QLineEdit(DesiredConnection_Client);
        IPAddressBox_Client->setObjectName(QStringLiteral("IPAddressBox_Client"));
        IPAddressBox_Client->setEnabled(true);
        IPAddressBox_Client->setGeometry(QRect(10, 90, 161, 25));
        PortBox_Client = new QLineEdit(DesiredConnection_Client);
        PortBox_Client->setObjectName(QStringLiteral("PortBox_Client"));
        PortBox_Client->setEnabled(true);
        PortBox_Client->setGeometry(QRect(10, 120, 161, 25));
        StartClientButton = new QPushButton(ClientTab);
        StartClientButton->setObjectName(QStringLiteral("StartClientButton"));
        StartClientButton->setGeometry(QRect(10, 330, 89, 25));
        ScrollArea_Client = new QScrollArea(ClientTab);
        ScrollArea_Client->setObjectName(QStringLiteral("ScrollArea_Client"));
        ScrollArea_Client->setGeometry(QRect(200, 10, 511, 351));
        ScrollArea_Client->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 509, 349));
        TextArea_Client = new QTextEdit(scrollAreaWidgetContents_3);
        TextArea_Client->setObjectName(QStringLiteral("TextArea_Client"));
        TextArea_Client->setGeometry(QRect(0, -1, 511, 351));
        ScrollArea_Client->setWidget(scrollAreaWidgetContents_3);
        SendXMLArea = new QGroupBox(ClientTab);
        SendXMLArea->setObjectName(QStringLiteral("SendXMLArea"));
        SendXMLArea->setGeometry(QRect(9, 169, 181, 91));
        BrowseXMLButton = new QPushButton(SendXMLArea);
        BrowseXMLButton->setObjectName(QStringLiteral("BrowseXMLButton"));
        BrowseXMLButton->setGeometry(QRect(10, 60, 161, 25));
        xmlFileNameBox = new QLineEdit(SendXMLArea);
        xmlFileNameBox->setObjectName(QStringLiteral("xmlFileNameBox"));
        xmlFileNameBox->setGeometry(QRect(10, 30, 161, 25));
        xmlFileNameBox->setReadOnly(true);
        Tabs->addTab(ClientTab, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        UnitTestStartButton = new QPushButton(tab);
        UnitTestStartButton->setObjectName(QStringLiteral("UnitTestStartButton"));
        UnitTestStartButton->setGeometry(QRect(10, 10, 89, 25));
        UnitTestStopButton = new QPushButton(tab);
        UnitTestStopButton->setObjectName(QStringLiteral("UnitTestStopButton"));
        UnitTestStopButton->setGeometry(QRect(120, 10, 89, 25));
        scrollArea = new QScrollArea(tab);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(10, 50, 701, 311));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 699, 309));
        UnitTestTextArea = new QTextEdit(scrollAreaWidgetContents);
        UnitTestTextArea->setObjectName(QStringLiteral("UnitTestTextArea"));
        UnitTestTextArea->setGeometry(QRect(0, 0, 701, 311));
        scrollArea->setWidget(scrollAreaWidgetContents);
        UnitTestProgressBar = new QProgressBar(tab);
        UnitTestProgressBar->setObjectName(QStringLiteral("UnitTestProgressBar"));
        UnitTestProgressBar->setGeometry(QRect(427, 10, 281, 23));
        UnitTestProgressBar->setValue(0);
        UnitTestProgressBar->setTextVisible(true);
        Tabs->addTab(tab, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 740, 22));
        menuKonami_Socket_Program = new QMenu(menuBar);
        menuKonami_Socket_Program->setObjectName(QStringLiteral("menuKonami_Socket_Program"));
        menuv1 = new QMenu(menuBar);
        menuv1->setObjectName(QStringLiteral("menuv1"));
        menu_Tralyn_Le = new QMenu(menuBar);
        menu_Tralyn_Le->setObjectName(QStringLiteral("menu_Tralyn_Le"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuKonami_Socket_Program->menuAction());
        menuBar->addAction(menuv1->menuAction());
        menuBar->addAction(menu_Tralyn_Le->menuAction());

        retranslateUi(MainWindow);

        Tabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Konami Socket Program", Q_NULLPTR));
        DesiredConnectionBox->setTitle(QApplication::translate("MainWindow", "Desired Connection", Q_NULLPTR));
        DefaultRadioButton_Server->setText(QApplication::translate("MainWindow", "Default", Q_NULLPTR));
        CustomRadioButton_Server->setText(QApplication::translate("MainWindow", "Custom", Q_NULLPTR));
        IPAddressBox_Server->setText(QApplication::translate("MainWindow", "Enter IP Address", Q_NULLPTR));
        PortBox_Server->setText(QApplication::translate("MainWindow", "Enter Port", Q_NULLPTR));
        StartServerButton->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        Tabs->setTabText(Tabs->indexOf(ServerTab), QApplication::translate("MainWindow", "Server", Q_NULLPTR));
        DesiredConnection_Client->setTitle(QApplication::translate("MainWindow", "Desired Connection", Q_NULLPTR));
        DefaultRadioButton_Client->setText(QApplication::translate("MainWindow", "Default", Q_NULLPTR));
        CustomRadioButton_Client->setText(QApplication::translate("MainWindow", "Custom", Q_NULLPTR));
        IPAddressBox_Client->setText(QApplication::translate("MainWindow", "Enter IP Address", Q_NULLPTR));
        PortBox_Client->setText(QApplication::translate("MainWindow", "Enter Port", Q_NULLPTR));
        StartClientButton->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        SendXMLArea->setTitle(QApplication::translate("MainWindow", "Send XML File", Q_NULLPTR));
        BrowseXMLButton->setText(QApplication::translate("MainWindow", "Browse XML", Q_NULLPTR));
        xmlFileNameBox->setText(QString());
        Tabs->setTabText(Tabs->indexOf(ClientTab), QApplication::translate("MainWindow", "Client", Q_NULLPTR));
        UnitTestStartButton->setText(QApplication::translate("MainWindow", "Start Tests", Q_NULLPTR));
        UnitTestStopButton->setText(QApplication::translate("MainWindow", "Stop Tests", Q_NULLPTR));
        Tabs->setTabText(Tabs->indexOf(tab), QApplication::translate("MainWindow", "Unit Test", Q_NULLPTR));
        menuKonami_Socket_Program->setTitle(QApplication::translate("MainWindow", "Konami Socket Program", Q_NULLPTR));
        menuv1->setTitle(QApplication::translate("MainWindow", "v1", Q_NULLPTR));
        menu_Tralyn_Le->setTitle(QApplication::translate("MainWindow", "- Tralyn Le", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
