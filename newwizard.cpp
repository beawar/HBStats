#include "newwizard.h"
#include <QMessageBox>


NewWizard::NewWizard(SquadreModel *sm, QWidget *parent) :
    QWizard(parent), squadre(sm)
{
    if(!squadre){
        squadre = new SquadreModel;
    }


    introP = new IntroPage(sm, this);
    personaP = new PersonaPage(sm, this);
    squadraP = new SquadraPage(sm, this);
    partitaP = new PartitaPage(sm, this);

    setPage(Page_Intro, introP);
    setPage(Page_Persona, personaP);
    setPage(Page_Squadra, squadraP);
    setPage(Page_Partita, partitaP);

    setStartId(Page_Intro);
    setWindowTitle(tr("Nuovo"));

    connect(personaP, SIGNAL(personaCreata()), this, SLOT(nuovaPersona()));
    connect(squadraP, SIGNAL(squadraCreata()), this, SLOT(nuovaSquadra()));

}

Squadra* NewWizard::getHomeTeam() const{
    return squadre->at(field("partita.homeTeam").toInt());
}

Squadra* NewWizard::getGuestTeam() const{
    return squadre->at(field("partita.guestTeam").toInt());
}

void NewWizard::accept(){
    if(currentId() == Page_Partita){
        if(partitaP->validatePage()){
            emit partitaCreata();
            close();
        }
        else{
            QMessageBox::warning(this, tr("Informazioni invalide"),
                                 tr("Impossibile creare la partita. Ricontrollare le "
                                 "informazioni immesse:\n"
                                 " - la squadra in casa e quella ospite devono essere distinte;\n"
                                 " - devono essere specificati due arbitri distinti;\n"
                                 " - devono essere selezionati minimo 7 giocatori e massimo "
                                 " 14 giocatori e 2 allenatori per squadra."),
                                 QMessageBox::Ok);
        }
    }
    else{
        close();
    }
}

void NewWizard::nuovaSquadra(){
    emit squadraCreata();
    emit dataChanged(true);
}

void NewWizard::nuovaPersona(){
    emit dataChanged(true);
}

