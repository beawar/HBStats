#include "linepartita.h"
#include <QMessageBox>
#include <QIcon>

LinePartita::LinePartita(Tesserato* t, QWidget *parent) :
    QWidget(parent), tesserato(t)
{
    setStyleSheet("font-size: 10pt;");

    numeroLabel = new QLabel(this);
    numeroLabel->setMinimumSize(15, 15);
    numeroLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    nomeLabel = new QLabel(t->getCognome() + " " + t->getNome(), this);
    nomeLabel->setMinimumSize(200, 15);
    nomeLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    goalLabel = new QLabel(this);
    goalLabel->setMinimumSize(15, 15);
    goalLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    createButtons();

    createLayout();
    setLayout(layout);

}

void LinePartita::createButtons(){

    ammoButton = new PushButton(QIcon(":/images/images/giallo.png"), "", this);
    ammoButton->setMinimumSize(15, 15);
    ammoButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    connect(ammoButton, SIGNAL(clicked()), this, SLOT(leftclickAmmo()));
    connect(ammoButton, SIGNAL(rightClicked()), this, SLOT(rightclickAmmo()));

    dueMinButton = new PushButton(QIcon(":/images/images/two_fingers.png"),"", this);
    dueMinButton->setMinimumSize(15, 15);
    dueMinButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    connect(dueMinButton, SIGNAL(clicked()), this, SLOT(leftclickdueMin()));
    connect(dueMinButton, SIGNAL(rightClicked()), this, SLOT(rightclickdueMin()));

    esclButton = new PushButton(QIcon(":/images/images/rosso.png"), "", this);
    esclButton->setMinimumSize(15, 15);
    esclButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    connect(esclButton, SIGNAL(clicked()), this, SLOT(leftclickEscl()));
    connect(esclButton, SIGNAL(rightClicked()), this, SLOT(rightclickEscl()));

    tiroButton = new PushButton(QIcon(":/images/images/footbal.png"), "", this);
    tiroButton->setMinimumSize(15, 15);
    tiroButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    connect(tiroButton, SIGNAL(clicked()), this, SLOT(leftclickTiro()));
    connect(tiroButton, SIGNAL(leftDoubleClicked()), this, SLOT(leftdoubleclickTiro()));
    connect(tiroButton, SIGNAL(rightClicked()), this, SLOT(rightclickTiro()));
    connect(tiroButton, SIGNAL(rightDoubleClicked()), this, SLOT(rightdoubleclickTiro()));

    rigoreButton = new PushButton("7m", this);
    rigoreButton->setMinimumSize(15, 15);
    rigoreButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    connect(rigoreButton, SIGNAL(clicked()), this, SLOT(leftclickRigore()));
    connect(rigoreButton, SIGNAL(leftDoubleClicked()), this, SLOT(leftdoubleclickRigore()));
    connect(rigoreButton, SIGNAL(rightClicked()), this, SLOT(rightclickRigore()));
    connect(rigoreButton, SIGNAL(rightDoubleClicked()), this, SLOT(rightdoubleclickRigore()));

}

void LinePartita::createLayout(){

    layout = new QHBoxLayout;
    layout->addWidget(numeroLabel);
    layout->addWidget(nomeLabel);
    layout->addWidget(goalLabel);
    layout->addWidget(tiroButton);
    layout->addWidget(rigoreButton);
    layout->addWidget(ammoButton);
    layout->addWidget(dueMinButton);
    layout->addWidget(esclButton);
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(g){
        numeroLabel->setText(QString::number(g->getNumero()));
        goalLabel->setText(QString::number(g->getTiriSegnati()));
    }
    else{
        numeroLabel->setText(tr("All"));
        tiroButton->setEnabled(false);
        rigoreButton->setEnabled(false);
    }
}

void LinePartita::rightclickAmmo(){
    ammoButton->setStyleSheet("/**/");
    tesserato->ammonito(false);
    emit dataChanged();
    update();
}

void LinePartita::leftclickAmmo(){
    ammoButton->setStyleSheet("background-color: yellow");
    try{
        tesserato->ammonito(true);
        emit dataChanged();
    }
    catch(Err_Ammonizione e){
        QMessageBox::warning(this, tr("Errore"),
                             tr("Persna già ammonita"),
                             QMessageBox::Cancel);
    }
    update();
}

void LinePartita::rightclickdueMin(){
    tesserato->add2Minuti(-1);
    emit dataChanged();
    update();
}

void LinePartita::leftclickdueMin(){
    try{
        tesserato->add2Minuti();
        emit dataChanged();
    }
    catch(Err_DueMinuti e){
        QMessageBox::warning(this, tr("Errore"),
                             tr("Raggiunte le esclusioni temporanee massime"),
                             QMessageBox::Cancel);
    }
    update();
}

void LinePartita::rightclickEscl(){
    esclButton->setStyleSheet("/**/");
    tesserato->escluso(false);
    emit dataChanged();
    update();
}

void LinePartita::leftclickEscl(){
    esclButton->setStyleSheet("background-color: red");
    try{
     tesserato->escluso();
     emit dataChanged();
     }
     catch(Err_Esclusione e){
     QMessageBox::warning(this, tr("Errore"),
                          tr("Giocatore già espulso"),
                          QMessageBox::Cancel);
    }
    update();
}

//Rimuove segnato
void LinePartita::rightclickTiro(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    g->addTiro(-1, true);
    emit tiro(-1, true);
    updateGoals();
}

//Rimuove sbagliato
void LinePartita::rightdoubleclickTiro(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    g->addTiro(1, true); //aggiunge un tiro segnato rimosso con l'evento single click che avviene con il double-click
    emit tiro(1, true);
    g->addTiro(-1, false);
    emit tiro(-1, false);
    updateGoals();
    QMessageBox::warning(this, tr("Tiro rimosso"), tr("E' stato rimosso un tiro sbagliato"), QMessageBox::Ok);
}

//Aggiunge segnato
void LinePartita::leftclickTiro(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    g->addTiro(1, true);
    emit tiro(1, true);
    updateGoals();
}

//Aggiunge sbagliato
void LinePartita::leftdoubleclickTiro(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    g->addTiro(-1, true); //rimuove un tiro segnato aggiunto con l'evento single click che avviene con il double-click
    g->addTiro(1, false);
    emit tiro(-1, true);
    emit tiro(1, false);
    updateGoals();
}

//Rimuove segnato
void LinePartita::rightclickRigore(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    g->addRigore(-1, true);
    emit rigore(-1, true);
    updateGoals();
}

//Rimuove sbagliato
void LinePartita::rightdoubleclickRigore(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    g->addRigore(1, true); //aggiunge un rigore segnato rimosso con il single-click dovuto al double-click
    emit rigore(1, true);
    g->addRigore(-1, false);
    emit rigore(-1, false);
    updateGoals();
}

//Aggiunge segnato
void LinePartita::leftclickRigore(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    g->addRigore(1, true);
    emit rigore(1, true);
    updateGoals();
}

//Aggiunge sbagliato
void LinePartita::leftdoubleclickRigore(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    g->addRigore(-1, true); //rimuove un rigore segnato aggiunto con l'evento single click che avviene con il double-click
    g->addRigore(1, false);
    emit rigore(-1, true);
    emit rigore(1, false);
    updateGoals();
}

void LinePartita::updateGoals(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(g){
        goalLabel->setText(QString::number(g->getTiriSegnati()));
    }
    update();
}

void LinePartita::updateTesserato(Tesserato *t){
    tesserato = t;
}

void LinePartita::reset(){
    tesserato->reset();
    updateGoals();
    emit rightclickAmmo();
    emit rightclickEscl();
}
