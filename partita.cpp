#include "partita.h"
#include <QFont>
#include <QRadioButton>
#include <QMessageBox>

Partita::Partita(Squadra *home, Squadra *guest, QWidget *parent) :
    QWidget(parent), homeTeam(home), guestTeam(guest),
    goalHome(0), goalGuest(0), currentPortiereHome(0), currentPortiereGuest(0)
{
    mainLayout = new QVBoxLayout;

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

    mainLayout->addWidget(goalsGroup);
    mainLayout->addLayout(teams);

    setLayout(mainLayout);
}

void Partita::createHomeLayout(){
    homeGroup = new QGroupBox(this);
    homePortiere = new QButtonGroup(this);
    QVBoxLayout* homeLayout = new QVBoxLayout;
    QHBoxLayout* lineLayout[maxGiocatori];
    QRadioButton* homeRadio[maxGiocatori];

    int giocatoriCount = 0;
    int j = 0;
    bool portiereTrovato = false;

    for(int i=0; i<homeTeam->size() && j<maxGiocatori+maxAllenatori; ++i){
        if(homeTeam->at(i)->isChecked()){
            homeLines[j] = new LinePartita(homeTeam->at(i), this);
            homeLines[j]->setObjectName(QString::number(i));
            if(dynamic_cast<Giocatore*>(homeTeam->at(i)) && giocatoriCount<maxGiocatori){
                homeRadio[giocatoriCount] = new QRadioButton(this);
                homeRadio[giocatoriCount]->setMinimumSize(15, 15);
                homeRadio[giocatoriCount]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
                lineLayout[giocatoriCount] = new QHBoxLayout;
                lineLayout[giocatoriCount]->addWidget(homeRadio[giocatoriCount], 0, Qt::AlignRight);
                lineLayout[giocatoriCount]->addWidget(homeLines[j], 0, Qt::AlignRight);

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
                homeLayout->addWidget(homeLines[j], 0, Qt::AlignRight);

            }

            connect(homeLines[j], SIGNAL(tiro(int, bool)), this, SLOT(tiroHome(int,bool)));
            connect(homeLines[j], SIGNAL(rigore(int,bool)), this, SLOT(rigoreHome(int,bool)));
            connect(homeLines[j], SIGNAL(dataChanged()), this, SLOT(dataSlot()));
            j++;
        }
    }

    if(!portiereTrovato){
        QMessageBox::warning(this, tr("Nessun portiere disponibile"),
                             tr("In lista non è presente nessun portiere. "
                                "Verrà selezionato il primo giocatore disponibile."), QMessageBox::Ok);
        for(int i = 0; i<homeTeam->size() && !portiereTrovato; ++i){
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
    int j = 0;
    bool portiereTrovato = false;

    for(int i=0; i<guestTeam->size() && j<maxGiocatori+maxAllenatori; ++i){
        if(guestTeam->at(i)->isChecked()){
            guestLines[j] = new LinePartita(guestTeam->at(i), this);
            guestLines[j]->setObjectName(QString::number(i));
            if(dynamic_cast<Giocatore*>(guestTeam->at(i)) && giocatoriCount<maxGiocatori){
                guestRadio[giocatoriCount] = new QRadioButton(this);
                guestRadio[giocatoriCount]->setMinimumSize(15, 15);
                guestRadio[giocatoriCount]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
                lineLayout[giocatoriCount] = new QHBoxLayout;
                lineLayout[giocatoriCount]->addWidget(guestRadio[giocatoriCount], 0, Qt::AlignRight);
                lineLayout[giocatoriCount]->addWidget(guestLines[j], 0, Qt::AlignRight);

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
                guestLayout->addWidget(guestLines[j], 0, Qt::AlignRight);

            }

            connect(guestLines[j], SIGNAL(tiro(int, bool)), this, SLOT(tiroGuest(int,bool)));
            connect(guestLines[j], SIGNAL(rigore(int,bool)), this, SLOT(rigoreGuest(int,bool)));
            connect(guestLines[j], SIGNAL(dataChanged()), this, SLOT(dataSlot()));
            j++;
        }
    }

    if(!portiereTrovato){
        QMessageBox::warning(this, tr("Nessun portiere disponibile"),
                             tr("In lista non è presente nessun portiere. "
                                "Verrà selezionato il primo giocatore disponibile."), QMessageBox::Ok);
        for(int i = 0; i<guestTeam->size() && !portiereTrovato; ++i){
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
                                       tr("Il giocatore selezionato non è memorizzato come portire."
                                          "Per renderlo il portiere corrente è necessaria una conversione.\n"
                                          "Continuare?"),
                                       QMessageBox::Ok | QMessageBox::Cancel);
        if(ret == QMessageBox::Ok){
            Giocatore* gioc = dynamic_cast<Giocatore*>(homeTeam->at(homePortiere->checkedId()));
            Portiere* portiere = new Portiere(*gioc);
            homeTeam->sostituisciTesserato(homePortiere->checkedId(), portiere);
            currentPortiereHome = homePortiere->checkedId();
            for(int i = 0; i<maxGiocatori+maxAllenatori; ++i){
                if(homeLines[i]->objectName().toInt() == currentPortiereHome){
                    delete homeLines[i];
                    homeLines[i] = new LinePartita(portiere, this);
                }
            }
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
            for(int i = 0; i<maxGiocatori+maxAllenatori; ++i){
                if(guestLines[i]->objectName().toInt() == currentPortiereGuest){
                    delete guestLines[i];
                    guestLines[i] = new LinePartita(portiere, this);
                }
            }
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
}

void Partita::reset(){
    goalHome = 0;
    goalGuest = 0;

    for(int i = 0; i<homeTeam->size(); ++i){
        homeLines[i]->reset();
    }
    for(int i = 0; i<guestTeam->size(); ++i){
        guestLines[i]->reset();
    }
    updatePunteggio();
}
