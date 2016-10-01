#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QString>
#include <QToolBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedWidget>
#include "newwizard.h"
#include "squadremodel.h"
#include "arbitrimodel.h"
#include "xmlhandler.h"
#include "tabs.h"
#include "editor.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT
private:
    void createLogoWidget();
    void createActions();
    void createMenus();
    void createToolBar();
    bool maybeSave();

    QStackedWidget stackedWidget;
    QWidget* logoWidget;
    QWidget* classificaWidget;

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* helpMenu;

    QToolBar* toolBar;

    NewWizard* newWizard;
    Tabs* tabs;
    Editor* editor;

    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;
    QAction* saveAsAct;
    QAction* exportAct;
    QAction* exitAct;
    QAction* editAct;
    QAction* aboutAct;
    QAction* aboutQtAct;
    QAction* resetPartitaAct;
    QAction* closePartitaAct;
    QAction* classificaAct;
    QAction* closeTabs;

    SquadreModel* squadre;
    ArbitriModel* arbitri;

    QString fileOpen;
    XmlHandler xml;

    bool modificato;


private slots:
    void newFile();
    void open();
    void save();
    void saveAs();
    void exportPng();
    void edit();
    void about();
    void aboutQt();

    void showPartita();
    void creaClassifica();
    void terminaPartita();
    void chiudiTabs();
    void enable_closeTabs(bool);

    void wasModified(bool);
protected:
    void closeEvent(QCloseEvent *event);

public:
  explicit MainWindow(QWidget *parent = 0);

signals:

public slots:

};

#endif // MAINWINDOW_H
