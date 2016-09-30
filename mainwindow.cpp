#include "mainwindow.h"
#include <QFont>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), logoWidget(0), classificaWidget(0), toolBar(0), newWizard(0),
  tabs(0), editor(0), squadre(new SquadreModel(this)), arbitri(new ArbitriModel(this)), fileOpen(""), xml(squadre, arbitri), modificato(false)
{
    createLogoWidget();
    createActions();
    createMenus();
    createToolBar();

    setCentralWidget(logoWidget);

    setWindowTitle("HandBall Stats by Beatrice Guerra");
    setMinimumSize(sizeHint());

}

void MainWindow::createLogoWidget(){
    logoWidget = new QWidget(this);
    QLabel* logoLabel = new QLabel(logoWidget);
    logoLabel->setPixmap(QPixmap(":/images/images/HBStats_Icon_Sfondo.png").scaled(500, 500, Qt::KeepAspectRatio));

    QWidget* topFiller = new QWidget(logoWidget);
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget* bottomFiller = new QWidget(logoWidget);
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(topFiller);
    layout->addWidget(logoLabel);
    layout->addWidget(bottomFiller);

    layout->setAlignment(logoLabel, Qt::AlignHCenter);

    logoWidget->setLayout(layout);
}

void MainWindow::createActions(){
    newAct = new QAction(QIcon(":/images/images/new.png"), tr("&Nuovo"), this);
    newAct->setShortcut(QKeySequence::New);
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/images/open.png"), tr("&Apri"), this);
    openAct->setShortcut(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/images/images/save.png"), tr("&Salva"), this);
    saveAct->setShortcut(QKeySequence::Save);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Salva &come"), this);
    saveAsAct->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exportAct = new QAction(QIcon(":/images/images/export.png"), tr("Esporta"), this);
    exportAct->setShortcut(QKeySequence(tr("Ctrl+E")));
    exportAct->setEnabled(false);

    editAct = new QAction(QIcon(":/images/images/edit.png"), tr("E&dita"), this);
    editAct->setEnabled(false);
    connect(editAct, SIGNAL(triggered()), this, SLOT(edit()));

    exitAct = new QAction(QIcon(":/images/images/quit.png"), tr("&Esci"), this);
    exitAct->setShortcut(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("Informazioni su HBStats"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));

    resetPartitaAct = new QAction(QIcon(":/images/images/reset.png"), tr("Reset Partita"), this);
    resetPartitaAct->setEnabled(false);

    closePartitaAct = new QAction(QIcon(":/images/images/termina.png"), tr("Termina Partita"), this);
    closePartitaAct->setEnabled(false);
    connect(closePartitaAct, SIGNAL(triggered()), this, SLOT(terminaPartita()));

    classificaAct = new QAction(QIcon(":/images/images/cup.png"), tr("Mostra classifica"), this);
    classificaAct->setEnabled(false);
    connect(classificaAct, SIGNAL(triggered()), this, SLOT(creaClassifica()));

    closeTabs = new QAction(QIcon(":/images/images/close_red.png"), tr("Chiudi"), this);
    connect(closeTabs, SIGNAL(triggered()), this, SLOT(chiudiTabs()));
}

void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(editAct);
    fileMenu->addAction(exportAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Finestra"));
    editMenu->addAction(resetPartitaAct);
    editMenu->addAction(closePartitaAct);
    editMenu->addAction(closeTabs);
    editMenu->addSeparator();
    editMenu->addAction(classificaAct);

    helpMenu = menuBar()->addMenu(tr("&Aiuto"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBar(){
    toolBar = addToolBar(tr("Partita"));
    toolBar->addAction(exportAct);
    toolBar->addAction(editAct);
    toolBar->addSeparator();
    toolBar->addAction(classificaAct);
    toolBar->addSeparator();
    toolBar->addAction(resetPartitaAct);
    toolBar->addAction(closePartitaAct);
    toolBar->addAction(closeTabs);
    toolBar->setMovable(false);
}

bool MainWindow::maybeSave(){
    if(modificato){
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Salvare le modfifiche?"),
                                   tr("Le modifiche non sono state salvate.\n"
                                       "Si desidera salvare prima di chiudere?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if(ret == QMessageBox::Save){
            save();
            return true;
        }
        else if(ret == QMessageBox::Discard){
            return true;
        }
        else if(ret == QMessageBox::Cancel){
            return false;
        }
    }

    return true;
}

void MainWindow::newFile(){
    newWizard = new NewWizard(squadre, arbitri, this);
    newWizard->setAttribute(Qt::WA_DeleteOnClose);
    newWizard->setModal(true);
    newWizard->show();
    connect(newWizard, SIGNAL(partitaCreata()), this, SLOT(showPartita()));
    connect(newWizard, SIGNAL(squadraCreata()), this, SLOT(creaClassifica()));
    connect(newWizard, SIGNAL(dataChanged(bool)), this, SLOT(wasModified(bool)));
    if(!editAct->isEnabled() && !squadre->isEmpty()){
        editAct->setEnabled(true);
    }
}

void MainWindow::open(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Scegli un file da aprire"), QDir::currentPath(), "*.hbs");
    if(!fileName.isNull()){
        if(squadre && !squadre->isEmpty()){
            squadre->clear();
        }
        if(arbitri && !arbitri->isEmpty()){
            arbitri->clear();
        }
        try{
            xml.readFile(fileName);
            fileOpen = fileName;
            editAct->setEnabled(true);
            classificaAct->setEnabled(true);
        }
        catch(Err_Open e){
            QMessageBox::critical(this, tr("Errore!"), tr("Si è verificato un errore nell'apertura del file"), QMessageBox::Ok);
            fileOpen = "";
        }
    }
}

void MainWindow::save(){
    if(!squadre->isEmpty() || !arbitri->isEmpty()){
        if(!fileOpen.isEmpty()){
            QFile file(fileOpen);
            if(file.open(QIODevice::WriteOnly)){
                try{
                    xml.writeFile(file);
                }
                catch(Err_Save e){
                    QMessageBox::critical(this, tr("Errore!"), tr("Si è verificato un errore nel salvataggio del file"), QMessageBox::Ok);
                }
            }
            else{
                QMessageBox::warning(this, tr("Errore!"), tr("Impossibile salvare il file (modalità solo lettura)"), QMessageBox::Ok);
            }
            file.close();
            wasModified(false);
        }
        else{
            saveAs();
        }
    }
}

void MainWindow::saveAs(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Salva come"), QDir::currentPath(), "*.hbs");
    if(!fileName.isEmpty()){
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly)){
            try{
                xml.writeFile(file);
                fileOpen = fileName;
            }
            catch(Err_Save e){
                QMessageBox::critical(this, tr("Errore!"), tr("Si è verificato un errore nel salvataggio del file"), QMessageBox::Ok);
            }
        }
        else{
            QMessageBox::warning(this, tr("Errore!"), tr("Impossibile salavre il file (modalità solo lettura)"), QMessageBox::Ok);
        }
        file.close();
        wasModified(false);
    }
}

void MainWindow::exportPng(){
    tabs->exportPng();
}


void MainWindow::edit(){
    editor = new Editor(squadre, arbitri, this);
    editor->setAttribute(Qt::WA_DeleteOnClose);
    editor->setModal(true);

    for(int i=0; i<squadre->size(); ++i){
        squadre->at(i)->sortByName();
    }

    connect(editor, SIGNAL(squadraChanged()), this, SLOT(creaClassifica()));
    connect(editor, SIGNAL(dataChanged(bool)), this, SLOT(wasModified(bool)));
    editor->setModal(true);
    editor->show();
}

void MainWindow::about(){
    QMessageBox::about(this, "HandBall Stats", tr("HandBallStats è un applicativo per la gestione "
                                                  "di partite di pallamano, che permette di mantenere traccia "
                                                  "delle statistiche individuali e di squadra per ogni partita "
                                                  "giocata.\n\n"
                                                  "Creato da Beatrice Guerra"));
}

void MainWindow::aboutQt(){
    QMessageBox::aboutQt(this, "About Qt");
}

void MainWindow::showPartita(){
    Squadra* home = newWizard->getHomeTeam();
    Squadra* guest = newWizard->getGuestTeam();
    Arbitro* a1 = 0; /*newWizard->getArbitro1();*/
    Arbitro* a2 = 0; /*newWizard->getArbitro2();*/
    Arbitro::Categoria cat= newWizard->getCategoria();

    tabs = new Tabs(home, guest, a1, a2, cat, this);

    classificaAct->setEnabled(false);
    exportAct->setEnabled(true);
    resetPartitaAct->setEnabled(true);
    closePartitaAct->setEnabled(true);
    closeTabs->setEnabled(false);

    connect(exportAct, SIGNAL(triggered()), tabs, SLOT(exportPng()));
    connect(resetPartitaAct, SIGNAL(triggered()), tabs, SLOT(reset()));

    setCentralWidget(tabs);
}

void MainWindow::creaClassifica(){

    exportAct->setEnabled(false);
    resetPartitaAct->setEnabled(false);
    closePartitaAct->setEnabled(false);

    classificaWidget = new QWidget(this);

    QFont font;
    font.setBold(true);
    font.setPointSize(16);

    QLabel* header[8];
    header[0] = new QLabel("N°", classificaWidget);
    header[1] = new QLabel(tr("Nome"), classificaWidget);
    header[2] = new QLabel(tr("Punti"), classificaWidget);
    header[3] = new QLabel(tr("V"), classificaWidget); //Vittorie
    header[4] = new QLabel(tr("P"), classificaWidget); //Pareggi
    header[5] = new QLabel(tr("S"), classificaWidget); //Sconfitte
    header[6] = new QLabel(tr("Pen"), classificaWidget); //Penalità
    header[7] = new QLabel(tr("DR"), classificaWidget); //Differenza Reti

    squadre->sort();

    QLabel* teamsLabel[squadre->size()][8];

    for(int i=0; i<squadre->size(); ++i){
        teamsLabel[i][0] = new QLabel(QString::number(i+1), classificaWidget);
        teamsLabel[i][1] = new QLabel(squadre->at(i)->getNome(), classificaWidget);
        teamsLabel[i][2] = new QLabel(QString::number(squadre->at(i)->getPunti()), classificaWidget);
        teamsLabel[i][3] = new QLabel(QString::number(squadre->at(i)->getVittorie()), classificaWidget);
        teamsLabel[i][4] = new QLabel(QString::number(squadre->at(i)->getPareggi()), classificaWidget);
        teamsLabel[i][5] = new QLabel(QString::number(squadre->at(i)->getSconfitte()), classificaWidget);
        teamsLabel[i][6] = new QLabel(QString::number(squadre->at(i)->getPenalita()), classificaWidget);
        teamsLabel[i][7] = new QLabel(QString::number(squadre->at(i)->getDifferenzaReti()), classificaWidget);
    }

    QGridLayout* classifica = new QGridLayout;
    for(int i=0; i<8; ++i){
        header[i]->setFont(font);
        header[i]->setAlignment(Qt::AlignHCenter);
        classifica->addWidget(header[i], 1, i+1);
    }


    font.setBold(false);
    for(int i=0; i<squadre->size(); ++i){
        for(int j=0; j<8; ++j){
            teamsLabel[i][j]->setFont(font);
            teamsLabel[i][j]->setAlignment(Qt::AlignHCenter);
            classifica->addWidget(teamsLabel[i][j], i+2, j+1);
        }
    }

    QWidget* topFiller = new QWidget(classificaWidget);
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget* bottomFiller = new QWidget(classificaWidget);
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout* classificaLayout = new QHBoxLayout;
    classificaLayout->addStretch(20);
    classificaLayout->addLayout(classifica);
    classificaLayout->addStretch(20);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(topFiller);
    layout->addLayout(classificaLayout);
    layout->addWidget(bottomFiller);

    classifica->setAlignment(layout, Qt::AlignHCenter);

    classificaWidget->setLayout(layout);

    setCentralWidget(classificaWidget);

}

void MainWindow::terminaPartita(){
    classificaAct->setEnabled(true);
    resetPartitaAct->setEnabled(false);
    closePartitaAct->setEnabled(false);
    closeTabs->setEnabled(true);
    tabs->termina();
    modificato = true;

}

void MainWindow::chiudiTabs(){
    createLogoWidget();
    setCentralWidget(logoWidget);
    exportAct->setEnabled(false);
    resetPartitaAct->setEnabled(false);
    closePartitaAct->setEnabled(false);
    classificaAct->setEnabled(true);
}

void MainWindow::wasModified(bool mod){
    modificato = mod;
}

void MainWindow::closeEvent(QCloseEvent *event){
    if(maybeSave()){
        save();
        event->accept();
    }
    else{
        event->ignore();
    }
}
