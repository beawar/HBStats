#include "partita.h"
#include <QFont>
#include <QRadioButton>
#include <QMessageBox>

Partita::Partita(Squadra *home, Squadra *guest, int numPlS1, int numAllS1, int numPlS2, int numAllS2, Arbitro *a1, Arbitro *a2, Arbitro::Categoria cat, QWidget *parent) :
    QWidget(parent), homeTeam(home), guestTeam(guest), arbitro1(a1), arbitro2(a2), categoria(cat),
    goalHome(0), goalGuest(0), currentPortiereHome(0), currentPortiereGuest(0)
{
    mainLayout = new QVBoxLayout;
    this->numPlS1 = numPlS1;
    this->numAllS1 = numAllS1;
    this->numPlS2 = numPlS2;
    this->numAllS2 = numAllS2;

    QLabel* homeName = new QLabel(homeTeam->getNome(), this);
    homeName->setAlignment(Qt::AlignHCenter);
    QLabel* guestName = new QLabel(guestTeam->getNome(), this);
    guestName->setAlignment(Qt::AlignHCenter);

    QFont font;
    font.setBold(true);
    font.setPointSize(30);
    homeName->setFont(font);
    guestName->setFont(font);

    punteggio = new QLabel("0 : 0", this);
    punteggio->setAlignment(Qt::AlignHCenter);
    punteggio->setFont(font);
    punteggio->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

/*
*    QLabel* arbitriLabel = new QLabel(tr("Arbitri:"), this);
*    QFont corsivo;
*    corsivo.setPointSize(20);
*    corsivo.setItalic(true);
*    corsivo.setBold(true);
*    arbitriLabel->setFont(corsivo);
*
*    QFont arbitriFont;
*    arbitriFont.setPointSize(15);
*
*    QString arb1str = arbitro1->getCognome() + " " + arbitro1->getNome();
*    QLabel* arbitro1Label = new QLabel(arb1str, this);
*    arbitro1Label->setFont(arbitriFont);
*
*    QString arb2str = arbitro2->getCognome() + " " + arbitro2->getNome();
*    QLabel* arbitro2Label = new QLabel(arb2str, this);
*    arbitro2Label->setFont(arbitriFont);
*/

    createHomeLayout();
    createGuestLayout();

    QHBoxLayout* goalsLayout = new QHBoxLayout;
    goalsLayout->addWidget(homeName);
    goalsLayout->addWidget(punteggio);
    goalsLayout->addWidget(guestName);

    QGroupBox* goalsGroup = new QGroupBox(this);
    goalsGroup->setLayout(goalsLayout);
    goalsGroup->setObjectName("goalsGroup");
    goalsGroup->setMaximumHeight(goalsGroup->sizeHint().height());
    setStyleSheet("QGroupBox#goalsGroup {border: 2px solid black } ");

    QHBoxLayout* teams = new QHBoxLayout;
    teams->addWidget(homeGroup);
    teams->addWidget(guestGroup);

/*
*    QHBoxLayout* arbitriLayout = new QHBoxLayout;
*    arbitriLayout->addWidget(arbitriLabel);
*    arbitriLayout->addWidget(arbitro1Label);
*    arbitriLayout->addWidget(arbitro2Label);
*/

    mainLayout->addWidget(goalsGroup);
    mainLayout->addLayout(teams);
//    mainLayout->addLayout(arbitriLayout);

    setLayout(mainLayout);
}

void Partita::createHomeLayout(){
    homeGroup = new QGroupBox(this);
    homePortiere = new QButtonGroup(this);
    QVBoxLayout* homeLayout = new QVBoxLayout;
    QHBoxLayout* lineLayout[maxGiocatori];
    QRadioButton* homeRadio[maxGiocatori];

    int giocatoriCount = 0;
    bool portiereTrovato = false;

    for(unsigned int i=0; i<homeTeam->size(); ++i){
        if(homeTeam->at(i)->isChecked()){
            homeLines.push_back(new LinePartita(homeTeam->at(i), this));
            if(dynamic_cast<Giocatore*>(homeTeam->at(i)) && giocatoriCount<numPlS1){
                homeRadio[giocatoriCount] = new QRadioButton(this);
                homeRadio[giocatoriCount]->setMinimumSize(15, 15);
                homeRadio[giocatoriCount]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
                lineLayout[giocatoriCount] = new QHBoxLayout;
                lineLayout[giocatoriCount]->addWidget(homeRadio[giocatoriCount], 0, Qt::AlignRight);
                lineLayout[giocatoriCount]->addWidget(homeLines[homeLines.size()-1], 0, Qt::AlignRight);

                homePortiere->addButton(homeRadio[giocatoriCount], i);
                connect(homePortiere->button(i), SIGNAL(clicked()), this, SLOT(cambiaPortiereHome()));

                if(!portiereTrovato && dynamic_cast<Portiere*>(homeTeam->at(i))){
                    homeRadio[giocatoriCount]->setChecked(true);
                    currentPortiereHome = i;
                    portiereTrovato = true;
                }

                homeLayout->addLayout(lineLayout[giocatoriCount]);
                giocatoriCount++;
            }
            else{
                homeLayout->addWidget(homeLines[homeLines.size()-1], 0, Qt::AlignRight);

            }

            connect(homeLines[homeLines.size()-1], SIGNAL(tiro(int, bool)), this, SLOT(tiroHome(int,bool)));
            connect(homeLines[homeLines.size()-1], SIGNAL(rigore(int,bool)), this, SLOT(rigoreHome(int,bool)));
            connect(homeLines[homeLines.size()-1], SIGNAL(dataChanged()), this, SLOT(dataSlot()));
        }
    }

    if(!portiereTrovato){
        QMessageBox::warning(this, tr("Nessun portiere disponibile"),
                             tr("In lista non è presente nessun portiere. "
                                "Verrà selezionato il primo giocatore disponibile."), QMessageBox::Ok);
        for(unsigned int i = 0; i<homeTeam->size() && !portiereTrovato; ++i){
            if(homeTeam->at(i)->isChecked() && dynamic_cast<Giocatore*>(homeTeam->at(i))){
                homePortiere->button(i)->setChecked(true);
                cambiaPortiereHome();
                portiereTrovato = true;
            }
        }
    }

    homeGroup->setLayout(homeLayout);

}

void Partita::createGuestLayout(){
    guestGroup = new QGroupBox(this);
    guestPortiere = new QButtonGroup(this);
    QVBoxLayout* guestLayout = new QVBoxLayout;
    QHBoxLayout* lineLayout[maxGiocatori];
    QRadioButton* guestRadio[maxGiocatori];

    int giocatoriCount = 0;
    bool portiereTrovato = false;

    for(unsigned int i=0; i<guestTeam->size(); ++i){
        if(guestTeam->at(i)->isChecked()){
            guestLines.push_back(new LinePartita(guestTeam->at(i), this));
            if(dynamic_cast<Giocatore*>(guestTeam->at(i)) && giocatoriCount<numPlS2){
                guestRadio[giocatoriCount] = new QRadioButton(this);
                guestRadio[giocatoriCount]->setMinimumSize(15, 15);
                guestRadio[giocatoriCount]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
                lineLayout[giocatoriCount] = new QHBoxLayout;
                lineLayout[giocatoriCount]->addWidget(guestRadio[giocatoriCount], 0, Qt::AlignRight);
                lineLayout[giocatoriCount]->addWidget(guestLines[guestLines.size()-1], 0, Qt::AlignRight);

                guestPortiere->addButton(guestRadio[giocatoriCount], i);
                connect(guestPortiere->button(i), SIGNAL(clicked()), this, SLOT(cambiaPortiereGuest()));

                if(!portiereTrovato && dynamic_cast<Portiere*>(guestTeam->at(i))){
                    guestRadio[giocatoriCount]->setChecked(true);
                    currentPortiereGuest = i;
                    portiereTrovato = true;
                }

                guestLayout->addLayout(lineLayout[giocatoriCount]);
                giocatoriCount++;
            }
            else{
                guestLayout->addWidget(guestLines[guestLines.size()-1], 0, Qt::AlignRight);

            }

            connect(guestLines[guestLines.size()-1], SIGNAL(tiro(int, bool)), this, SLOT(tiroGuest(int,bool)));
            connect(guestLines[guestLines.size()-1], SIGNAL(rigore(int,bool)), this, SLOT(rigoreGuest(int,bool)));
            connect(guestLines[guestLines.size()-1], SIGNAL(dataChanged()), this, SLOT(dataSlot()));
        }
    }

    if(!portiereTrovato){
        QMessageBox::warning(this, tr("Nessun portiere disponibile"),
                             tr("In lista non è presente nessun portiere. "
                                "Verrà selezionato il primo giocatore disponibile."), QMessageBox::Ok);
        for(unsigned int i = 0; i<guestTeam->size() && !portiereTrovato; ++i){
            if(guestTeam->at(i)->isChecked() && dynamic_cast<Giocatore*>(guestTeam->at(i))){
                guestPortiere->button(i)->setChecked(true);
                cambiaPortiereGuest();
                portiereTrovato = true;
            }
        }
    }

    guestGroup->setLayout(guestLayout);
}

void Partita::updatePunteggio(){
    punteggio->setText(tr("%1 : %2").arg(QString::number(homeTeam->getTiriSegnati()),
                                         QString::number(guestTeam->getTiriSegnati())));
    update();
}

void Partita::tiroHome(int val, bool segnato){
    Portiere* p = dynamic_cast<Portiere*>(guestTeam->at(currentPortiereGuest));
    if(p){
        bool parato = !segnato;
        p->addTiroRicevuto(val, parato);
    }
    updatePunteggio();
    emit dataChanged();

}

void Partita::rigoreHome(int val, bool segnato){
    Portiere* p = dynamic_cast<Portiere*>(guestTeam->at(currentPortiereGuest));
    if(p){
        bool parato = !segnato;
        p->addRigoreRicevuto(val, parato);
    }
    updatePunteggio();
    emit dataChanged();
}

void Partita::tiroGuest(int val, bool segnato){
    Portiere* p = dynamic_cast<Portiere*>(homeTeam->at(currentPortiereHome));
    if(p){
        bool parato = !segnato;
        p->addTiroRicevuto(val, parato);
    }
    updatePunteggio();
    emit dataChanged();
}

void Partita::rigoreGuest(int val, bool segnato){
    Portiere* p = dynamic_cast<Portiere*>(homeTeam->at(currentPortiereHome));
    if(p){
        bool parato = !segnato;
        p->addRigoreRicevuto(val, parato);
    }
    updatePunteggio();
    emit dataChanged();
}

void Partita::cambiaPortiereHome(){
    Portiere* p = dynamic_cast<Portiere*>(homeTeam->at(homePortiere->checkedId()));
    if(p){
        currentPortiereHome = homePortiere->checkedId();
    }
    else{
        int ret = QMessageBox::warning(this, tr("Conversione necessaria"),
                                       tr("Il giocatore selezionato non è memorizzato come portiere."
                                          "Per renderlo il portiere corrente è necessaria una conversione.\n"
                                          "Continuare?"),
                                       QMessageBox::Ok | QMessageBox::Cancel);
        if(ret == QMessageBox::Ok){
            Giocatore* gioc = dynamic_cast<Giocatore*>(homeTeam->at(homePortiere->checkedId()));
            Portiere* portiere = new Portiere(*gioc);
            homeTeam->sostituisciTesserato(homePortiere->checkedId(), portiere);
            currentPortiereHome = homePortiere->checkedId();
            homeLines[currentPortiereHome]->updateTesserato(portiere);
        }
        else{
            homePortiere->button(currentPortiereHome)->setChecked(true);
        }
    }
}

void Partita::cambiaPortiereGuest(){
    Portiere* p = dynamic_cast<Portiere*>(guestTeam->at(guestPortiere->checkedId()));
    if(p){
        currentPortiereGuest = guestPortiere->checkedId();
    }
    else{
        int ret = QMessageBox::warning(this, tr("Conversione necessaria"),
                                       tr("Il giocatore selezionato non è memorizzato come portire."
                                          "Per renderlo il portiere corrente è necessaria una conversione.\n"
                                          "Continuare?"),
                                       QMessageBox::Ok | QMessageBox::Cancel);
        if(ret == QMessageBox::Ok){
            Giocatore* gioc = dynamic_cast<Giocatore*>(guestTeam->at(guestPortiere->checkedId()));
            Portiere* portiere = new Portiere(*gioc);
            guestTeam->sostituisciTesserato(guestPortiere->checkedId(), portiere);
            currentPortiereGuest = guestPortiere->checkedId();
            guestLines[currentPortiereGuest]->updateTesserato(portiere);
        }
        else{
            guestPortiere->button(currentPortiereGuest)->setChecked(true);
        }
    }

}

void Partita::dataSlot(){
    emit dataChanged();
}

void Partita::termina(){
    goalHome = homeTeam->getTiriSegnati();
    goalGuest = guestTeam->getTiriSegnati();
    if(goalHome > goalGuest){
        homeTeam->addVittoria(1, goalHome, goalGuest);
        guestTeam->addSconfitta(1, goalGuest, goalHome);
    }
    else if(goalHome == goalGuest){
        homeTeam->addPareggio(1, goalHome);
        guestTeam->addPareggio(1, goalGuest);
    }
    else{
        homeTeam->addSconfitta(1, goalHome, goalGuest);
        guestTeam->addVittoria(1, goalGuest, goalHome);
    }
//    arbitro1->addPartita(categoria);
//    arbitro2->addPartita(categoria);
}

void Partita::reset(){
    goalHome = 0;
    goalGuest = 0;
    /*
    int count = 0;
    for(int i = 0; i<homeTeam->size(); ++i){
        if(homeTeam->at(i)->isChecked()){
            homeLines[count]->reset();
            count++;
        }
    }
    count = 0;
    for(int i = 0; i<guestTeam->size(); ++i){
        if(homeTeam->at(i)->isChecked()){
            guestLines[count]->reset();
            count++;
        }
    }*/

    for(unsigned int i=0; i<homeLines.size(); ++i){
        homeLines[i]->reset();
    }
    for(unsigned int i = 0; i<guestLines.size(); ++i){
        guestLines[i]->reset();
    }
    updatePunteggio();
}
